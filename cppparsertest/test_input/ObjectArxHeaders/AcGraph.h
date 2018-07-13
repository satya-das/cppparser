//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// CREATED BY: Pei Zhan                                 March 2011
//
//////////////////////////////////////////////////////////////////////////////
#pragma once
#pragma pack (push, 8)

#include "AcGraphNode.h"
#include <map>

class AcImpGraph;
class AcDbObject;

typedef std::map<AcGraphNode::Id, AcGraphNode*> NodeIdToPtrMap;

/// <summary>
/// This class represents a graph which manages a set of AcGraphNode with a unique id.
/// </summary>
///
class ACDBCORE2D_PORT AcGraph : public AcRxObject
{
public:

    ACRX_DECLARE_MEMBERS(AcGraph);

    enum PartialUndoCode
    {
        /// <summary>
        /// Event of adding a node to the graph.
        /// </summary>
        ///
        kAddNodePartialUndoCode = 0,

        /// <summary>
        /// Event of removing a node from the graph.
        /// </summary>
        ///
        kRemoveNodePartialUndoCode,

        /// <summary>
        /// Event of modifying a node in the graph.
        /// </summary>
        ///
        kModifyNodePartialUndoCode,

        /// <summary>
        /// Event of changing the value of node Id for the next new node.
        /// </summary>
        ///
        kModifyNextNewNodeIdPartialUndoCode,
    };

typedef NodeIdToPtrMap::iterator iterator;
typedef NodeIdToPtrMap::const_iterator const_iterator;

    /// <summary> Default constructor. </summary>
    ///
    explicit AcGraph(bool bCreateImp = true);

    /// <summary> Default destructor. </summary>
    ///
    virtual ~AcGraph();

    /// <summary> 
    /// This function returns the owning object of the graph
    /// </summary>
    /// <returns> AcDbObject*. </returns>
    AcDbObject* owningObject() const;

    /// <summary> 
    /// This function set the owning object of the graph. Client code needs to
    /// ensure the validity of AcDbObject* throughout the whole lifetime of AcGraph. In the 
    /// AcGraph class the owning object is mainly used for partial undo purpose
    /// </summary>
    /// <returns> None. </returns>
    void setOwningObject(AcDbObject* pObj);

    /// <summary> 
    /// This function restores state of AcGraph during partial undo. Normally it is called
    /// from the applyPartialUndo method in owning object. In AcGraph, partial undo information
    /// is automatically recorded when a change is made to an AcGraph, the partial undo info
    /// that is written out includes (with order): address of class descriptor object of owingObject(), undo code
    /// and corresponding data for each specific undo operation. In client's code, applyPartialUndo needs to
    /// be implement for owningObject, which has to read the data in the same order, and then call 
    /// AcGraph::applyPartialUndo with the PartialUndoCode info
    /// </summary>
    /// <param name="pUndoFiler">   Input undo filer, normally from the object that owns this graph. </param>
    /// <param name="code">   code for undo operation. </param>
    /// <param name="nodeId">   the id of the AcGraphNode that was affected during the undo operation, 
    /// For following undo codes: 
    /// kAddNodePartialUndoCode: the id of the node that was added, note the returned nodeId is no longer valid as it has been removed from the graph. 
    /// kRemoveNodePartialUndoCode: the id of the node that was removed
    /// kModifyNodePartialUndoCode: the id of the node that was modified
    /// kModifyNextNewNodeIdPartialUndoCode: the new node id that was generated
    /// </param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus applyPartialUndo(AcDbDwgFiler* pUndoFiler,
                                               PartialUndoCode code,
                                               AcGraphNode::Id &nodeId); 

    /// <summary> 
    /// This function adds a node to the graph, a new node id is automatically assigned to the new node.
    /// It returns an error if the new node already has an owner graph that is different from this one,
    /// or the new node already has a non-null node Id in the same graph
    /// </summary>
    /// <param name="pNewNode"> new node to be added to this graph. </param>
    /// <returns> Acad::ErrorStatus </returns>
    Acad::ErrorStatus addGraphNode(AcGraphNode* pNewNode);

    /// <summary> 
    /// This function adds a node to the graph, it uses input nodeId for the new node. 
    /// It's caller's responsibility to ensure the nodeId is unused, other wise an error will
    /// be returned.
    /// It returns an error if the new node already has an owner graph that is different from this one,
    /// or nodeId has already been used in the this AcGraph
    /// </summary>
    /// <param name="pNewNode"> new node to be added to this graph. </param>
    /// <param name="nodeId"> nodeId to be assigned to the new node. </param>
    /// <returns> Acad::ErrorStatus </returns>
    Acad::ErrorStatus addGraphNode(AcGraphNode* pNewNode, AcGraphNode::Id nodeId);

    /// <summary> 
    /// This function removes a node from the graph, it returns an error if the node is still connected
    /// to other nodes. This function will also delete the node pointer if bDelete is true.
    /// </summary>
    /// <param name="pNode"> node to be removed from this graph. </param>
    /// <param name="bDelete"> if the node is to be deleted. </param>
    /// <returns> Acad::ErrorStatus </returns>

    Acad::ErrorStatus removeGraphNode(AcGraphNode* pNode, bool bDelete = true);

    /// <summary> 
    /// Given a node id, this function returns a pointer to the AcGraphNode. 
    /// Returns NULL if no match is found for the id
    /// </summary>
    /// <param name="nodeId"> the id of the returned node pointer. </param>
    /// <returns> pointer to the AcGraphNode  </returns>
    AcGraphNode* getGraphNodePtr(AcGraphNode::Id nodeId) const;

    /// <summary> 
    /// Disconnect an array of AcGraphNodes from their original owning graph and move them to this graph. 
    /// All other nodes that are directly or indirectly connected to these nodes will be
    /// moved as well. A new node id will be assigned to each of the node after it is moved.
    /// During the process, when each of the nodes is moved, method AcGraphNode::nodeToBeMovedNotification
    /// will be called to notify this event, which can be overriden to customize the behavior
    /// (see AcGraphNode::nodeToBeMoved for more details)
    /// </summary>
    /// <param name="nodesToMove">  input array of nodes to be moved to this graph. </param>
    /// <returns> Acad::ErrorStatus </returns>
    Acad::ErrorStatus moveAndMerge(const AcArray<AcGraphNode*> & nodesToMove);

    /// <summary> 
    /// Merge a graph into this graph, all the nodes will be unconditionally moved to this graph.  
    /// A new node id will be assigned to each of the node after it is moved.
    /// </summary>
    /// <param name="graph">  input graph that is to be merged to this graph. </param>
    /// <returns> Acad::ErrorStatus </returns>
    Acad::ErrorStatus merge(const AcGraph &graph);

    /// <summary> 
    /// Given an array of nodes, return all the related nodes that are directly or indirectly connected
    /// to them.
    /// </summary>
    /// <param name="nodes">  input nodes. </param>
    /// <param name="nodes">  output related nodes. </param>
    /// <returns> Acad::ErrorStatus </returns>
    Acad::ErrorStatus getRelatedNodes(const AcArray<AcGraphNode *> &nodes, AcArray<AcGraphNode *> &relatedNodes) const;

    /// <summary> 
    /// This function returns an iterator at the beginning of the iterated range
    /// </summary>
    /// <returns> AcGraph::iterator </returns>
    iterator begin();  

    /// <summary> 
    /// This function returns a cons_iterator at the beginning of the iterated range
    /// </summary>
    /// <returns> AcGraph::const_iterator </returns>
    const_iterator begin() const;

    /// <summary> 
    /// This function returns an iterator at the end of the iterated range
    /// </summary>
    /// <returns> AcGraph::iterator </returns>
    iterator end();

    /// <summary> 
    /// This function returns a cons_iterator at the end of the iterated range
    /// </summary>
    /// <returns> AcGraph::const_iterator </returns>
    const_iterator end() const;

    /// <summary> 
    /// This function returns the size(number) of nodes in the graph
    /// </summary>
    /// <returns> size_t </returns>
    size_t size() const;

    /// <summary> 
    /// This function removes all the nodes in the graph, it also optionally deletes the pointer 
    /// of each AcGraphNode in the AcGraph
    /// <param name="bDelete"> if the nodes are to be deleted. </param>
    /// </summary>
    /// <returns> none </returns>
    void clear(bool bDelete);

    /// <summary> 
    /// This function is called by dwgOut(). Its purpose is to allow the object to write out its data.
    /// </summary>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler *pFiler) const;     

    /// <summary> 
    /// This function is called by dwgIn(). Its purpose is to allow the object to read in its data.
    /// </summary>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler);    

    /// <summary> 
    /// This function is called by dxfOut(). Its purpose is to allow the object to write out its data.
    /// </summary>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler *pFiler) const;   

    /// <summary> 
    /// This function is called by dxfIn(). Its purpose is to allow the object to read in its data.
    /// </summary>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler *pFiler);  
 
    /// <summary> 
    /// Returns id of the graph, by default it is 0 if setGraphId was not called to assign an id previously
    /// </summary>
    /// <returns> Acad::UInt32 </returns>
    virtual Adesk::UInt32     graphId() const;

    /// <summary> 
    /// Sets id of the graph. When the owningObject has more than one graphs, it is important to assign a 
    /// unique id to each of the graphs
    /// </summary>
    /// <returns> none </returns>
    virtual void              setGraphId(Adesk::UInt32 id);

protected:

    AcImpGraph* mpImpGraph;

private:
    /// <summary> 
    /// Disabled copy constructor
    /// </summary>
    AcGraph(const AcGraph &graph);

    /// <summary> 
    /// Disabled assignment operator
    /// </summary>
    AcGraph &operator = (const AcGraph &graph);

friend class AcGraphNode;
friend class AcImpGraphNode;
friend class AcImpGraph;
};

#pragma pack (pop)

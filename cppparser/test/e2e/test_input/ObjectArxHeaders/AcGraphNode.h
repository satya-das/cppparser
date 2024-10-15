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

class AcImpGraphNode;
class AcGraph;

class ACDBCORE2D_PORT AcGraphNode : public AcRxObject, 
                              public AcHeapOperators
{
public:
    ACRX_DECLARE_MEMBERS(AcGraphNode);

    /// <summary> Default destructor. </summary>
    ///
    virtual ~AcGraphNode();

    typedef Adesk::UInt32 Id;

    /// <summary> Null node id </summary>
    ///
    enum {
		kNullId = 0
	};
	
    /// <summary> 
    /// Returns id of the Id object. Each AcGraphNode object has a unique id 
    /// </summary>
    /// <returns> Id. </returns>
    ///
    Id nodeId() const;

    /// <summary> 
    /// This function returns the pointer of its owning graph
    /// Returns NULL if no owning graph is defined
    /// </summary>
    /// <returns> pointer to the owning graph. </returns>
    AcGraph* owningGraph() const;

    /// <summary> 
    /// This function connects this node to a node in an AcGraph, and call nodeToBeConnectedNotification
    /// on each node in the same AcGraph to notify about this event . 
    /// Both the nodes must belong to the same graph otherwise it will return an error of eInvalidInput
    /// </summary>
    /// <returns> Acad::ErrorStatus </returns>
    Acad::ErrorStatus connectNode (AcGraphNode* pNode);

    /// <summary> 
    /// This function disconnects this node from an adjacent node in an AcGraph, and call 
    /// nodeToBeConnectedNotification on each node in the same AcGraph to notify about this event 
    /// </summary>
    /// <returns> Acad::ErrorStatus </returns>
    Acad::ErrorStatus disconnectNode(AcGraphNode* pNode);

    /// <summary> 
    /// This function disconnects this node from all its adjacent nodes in an AcGraph
    /// </summary>
    /// <returns> Acad::ErrorStatus </returns>
    Acad::ErrorStatus disconnectAllNodes();

    /// <summary> 
    /// This function gets all its adjacent nodes in an AcGraph
    /// </summary>
    /// <returns> Acad::ErrorStatus </returns>
    Acad::ErrorStatus getAdjacentNodes(AcArray<AcGraphNode*>& adjacentNodes) const;

    /// <summary> 
    /// This function backups all its data for a partial undo when a node is modified (for kModifyNodePartialUndoCode event).
    /// Derived class should call this method when its data is modified to ensure a successful undo operation
    /// </summary>
    /// <returns> none </returns>
    virtual void backup();

    /// <summary> 
    /// This function checks if a node (pNode) is adjacent to this node
    /// </summary>
    /// <returns> true if it is an adjacent node</returns>
    bool isAdjacentTo(AcGraphNode *pNode) const;

    /// <summary> 
    /// When a node is being connected to this node, this function gets called to notify
    /// about this event. Derived class can override this method and veto the new connection 
    /// by returning Acad::eVetoed. In the base class, it simply returns Acad::eOk
    /// </summary>
    /// <param name="pNode">  Pointer of the node that is connecting to this node. </param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus nodeToBeConnectedNotification(AcGraphNode *pNode); 

    /// <summary> 
    /// When a node is being disconnected from this node , this function gets called to notify 
    /// about this event. Derived class can override this method and veto the action by 
    /// returning Acad::eVetoed. In the base class, it simply returns Acad::eOk
    /// </summary>
    /// <param name="pNode">  Pointer of the node that is being disconnected from this node. </param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus nodeToBeDisconnectedNotification(AcGraphNode* pNode); 

    /// <summary> 
    /// When a node is being moved from one graph to another, this function gets called to notify 
    /// about this event. Derived class can override this method and veto the action by 
    /// returning Acad::eVetoed, also an array of nodes can be returned to indicate to move this node 
    /// what other nodes need to be moved as well. 
    /// In the base class, the default implementation simply returns Acad::eOk.
    /// </summary>
    /// <param name="pGraph">  input graph that this node is to be moved to. </param>
    /// <param name="otherNodesToMove"> output array of nodes that should also be moved. </param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus nodeToBeMovedNotification(AcGraph *pGraph, AcArray<AcGraphNode *> & otherNodesToMove);

    /// <summary> 
    /// This function is called by dwgOut(). Its purpose is to allow the object to write out its data.
    /// </summary>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const;     

    /// <summary> 
    /// This function is called by dwgIn(). Its purpose is to allow the object to read in its data.
    /// </summary>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler*);      

    /// <summary> 
    /// This function is called by dxfOut(). Its purpose is to allow the object to write out its data.
    /// </summary>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const;     

    /// <summary> 
    /// This function is called by dxfIn(). Its purpose is to allow the object to read in its data.
    /// </summary>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler*);  

protected:

    /// <summary> Protected default constructor. </summary>
    ///
    explicit AcGraphNode(bool bCreateImp = true);

    AcImpGraphNode* mpImpGraphNode;

private:
    /// <summary> 
    /// Disabled copy constructor
    /// </summary>
    AcGraphNode(const AcGraphNode &node);

    /// <summary> 
    /// Disabled assignment operator
    /// </summary>
    AcGraphNode &operator = (const AcGraphNode &node);

friend class AcGraph;
friend class AcImpGraph;
};

#pragma pack (pop)

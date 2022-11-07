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
//  dbeval.h
//    
//     AcRxObject
//       AcDbObject
//         AcDbEvalGraph
//         AcDbEvalExpr
//           AcDbEvalConnectable
//
//       AcDbEvalContext
//       AcDbEvalContextPair
//       AcDbEvalContextIterator
//       AcDbEvalVariant
//         
//
//  DESCRIPTION:
//
//  The classes in this file provide a framework for managing and evaluating a
//  collection of operations in a specfic order. The framework consists of a
//  collection of nodes, organized in a graph. By establishing edges between
//  nodes in the graph and directions on each edge, the graph can sort the
//  nodes topologically and traverse the nodes in a specific order. 
//
//  The nodes themselves (AcDbEvalExpr) implement an evaluate() method that is
//  called by the graph (AcDbEvalGraph) in the order that the nodes are
//  traversed. 
//
//  Applications typically make use of this framework by implementing custom
//  objects derived from AcDbEvalExpr and implementing the
//  AcDbEvalExpr::evaluate() method. Applications instantiate custom nodes, add
//  them to a graph, add edges between the nodes, and call
//  AcDbEvalGraph::evaluate() to perform a traversal of the nodes.
//

#pragma once

#include "dbmain.h"
#include "dbents.h"
#include "acstring.h"
#include "adscodes.h"
#include "adsdef.h"

#pragma pack(push, 8)

// Forward class declarations

class AcDbEvalGraph;
class AcDbEvalEdgeInfo;
class AcDbEvalExpr;
class AcDbEvalConnectable;
class AcDbEvalContext;
class AcDbEvalContextPair;
class AcDbEvalContextIterator;
class AcDbEvalVariant;
class AcDbImpEvalContext;
class AcDbImpEvalContextIterator;
class AcRxValue;
class AcRxValueType;

// Type declarations

// Unique (within an AcDbEvalGraph) identifier assigned to
// a node (AcDbEvalExpr) in the graph.
typedef Adesk::UInt32 AcDbEvalNodeId;

typedef AcArray<AcDbEvalNodeId>             AcDbEvalNodeIdArray;
typedef AcArray<AcDbEvalEdgeInfo*>          AcDbEvalEdgeInfoArray;
typedef AcArray<AcDbEvalExpr*>              AcDbEvalExprPtrArray;
typedef AcArray<AcDbEvalVariant,
        AcArrayObjectCopyReallocator<AcDbEvalVariant> >   AcDbEvalVariantArray;

////////////////////////////////////////////////////////////////////////
// class AcDbEvalVariant 
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class provides a lightweight wrapper for a resbuf structure.  It
/// provides typed constructors and overloaded assignment operators to
/// facilitiate assignig values to the underlying data. AcDbEvalExpr objects
/// return instances of this class for the "result" of the expressions. 
/// </summary>
///
/// <remarks>
/// The class manages the copying of strings by calling acutNewString() to copy
/// strings. Linked lists of resbufs are not directly supported, but if an
/// AcDbEvalVariant contains a linked resbuf chain the destructor will free the
/// entire chain using acutRelRb(). 
/// </remarks>
///
class AcDbEvalVariant : public resbuf, public AcRxObject
{
public:

    ACRX_DECLARE_MEMBERS(AcDbEvalVariant);

    /// <summary>
    /// Default constructor.
    /// </summary>
    ///
    /// <remarks> Allocates the resbuf and initializes the variant type to
    /// AcDbEvalVariant::kNone.  
    /// </remarks>
    ///
    AcDbEvalVariant ();

    /// <summary>
    /// Copy contstructor.
    /// </summary>
    ///
    /// <param name="other">
    /// The object to copy from. 
    /// </param>
    ///
    AcDbEvalVariant(const AcDbEvalVariant& other); 

    /// <summary>
    /// Move contstructor.
    /// </summary>
    ///
    /// <param name="other">
    /// The object to move from. 
    /// </param>
    ///
    ACDBCORE2D_PORT AcDbEvalVariant(AcDbEvalVariant&& other); 

    /// <summary>
    /// Copy contstructor.
    /// </summary>
    ///
    /// <param name="pOther">
    /// A pointer to the object to copy from. 
    /// </param>
    ///
    AcDbEvalVariant (const AcDbEvalVariant* pOther);

    /// <summary>
    /// Destructor.
    /// </summary>
    ///
    /// <remarks>
    /// The data in the underlying resbuf is freed by this destructor. Strings
    /// are freed using acutDelString(), and linked resbuf chains are freed
    /// using acutRelRb().
    /// </remarks>
    ///
    ~AcDbEvalVariant();
    
    /// <summary>
    /// Constructs an AcDbEvalVariant wrapping a double value.
    /// </summary>
    ///
    /// <param name="dVal">
    /// The value to assign to the object.
    /// </param>
    ///
    /// <remarks>
    /// The variant type is set to AcDbEvalVariant::kDouble.
    /// </remarks>
    ///
    AcDbEvalVariant (double       dVal);

    /// <summary>
    /// Constructs an AcDbEvalVariant wrapping a short integer value.
    /// </summary>
    ///
    /// <param name="iVal">
    /// The value to assign to the object.
    /// </param>
    ///
    /// <remarks>
    /// The variant type is set to AcDbEvalVariant::kShort.
    /// </remarks>
    /// 
    AcDbEvalVariant (short        iVal);

    /// <summary>
    /// Constructs an AcDbEvalVariant wrapping a string value.
    /// </summary>
    ///
    /// <param name="szVal">
    /// The value to assign to the object.
    /// </param>
    ///
    /// <remarks>
    /// The variant type is set to AcDbEvalVariant::kString.
    /// </remarks>
    /// 
    AcDbEvalVariant (const ACHAR*  szVal);

    /// <summary>
    /// Constructs an AcDbEvalVariant wrapping a long value.
    /// </summary>
    ///
    /// <param name="lVal">
    /// The value to assign to the object.
    /// </param>
    ///
    /// <remarks>
    /// The variant type is set to AcDbEvalVariant::kLong.
    /// </remarks>
    /// 
    AcDbEvalVariant (Adesk::Int32         lVal);
    
    /// <summary>
    /// Constructs an AcDbEvalVariant wrapping an AcDbObjectId.
    /// </summary>
    ///
    /// <param name="id">
    /// The value to assign to the object.
    /// </param>
    ///
    /// <remarks>
    /// The variant type is set to AcDbEvalVariant::kOldId.
    /// </remarks>
    /// 
    AcDbEvalVariant (const AcDbObjectId& id);

    /// <summary>
    /// Constructs an AcDbEvalVariant wrapping a 2D point.
    /// </summary>
    ///
    /// <param name="pt">
    /// The value to assign to the object.
    /// </param>
    ///
    /// <remarks>
    /// The variant type is set to AcDbEvalVariant::kPoint2d
    /// </remarks>
    /// 
    AcDbEvalVariant (const AcGePoint2d&  pt);

    /// <summary>
    /// Constructs an AcDbEvalVariant wrapping a 3D point. 
    /// </summary>
    ///
    /// <param name="pt">
    /// The value to assign to the object.
    /// </param>
    ///
    /// <remarks>
    /// The variant type is set to AcDbEvalVariant::kPoint3d.
    /// </remarks>
    /// 
    AcDbEvalVariant (const AcGePoint3d&  pt);
    
    /// <summary>
    /// Constructs an AcDbEvalVariant from a resbuf.
    /// </summary>
    ///
    /// <param name="pt">
    /// The value to assign to the object.
    /// </param>
    ///
    /// <remarks>
    /// The variant type is set to rb.restype.
    /// </remarks>
    AcDbEvalVariant(const resbuf& rb);

    /// <summary>
    /// Assigns an AcDbEvalVariant to a resbuf.
    /// </summary>
    ///
    /// <param name="dVal">
    /// The value to assign to the object.
    /// </param>
    ///
    /// <returns> 
    /// A reference to the updated variant.
    /// </returns>
    ///
    /// <remarks>
    /// The variant type is set to rb.restype.
    /// </remarks>
    /// 
    AcDbEvalVariant& operator=(const resbuf& rb);

    /// <summary>
    /// Assigns an AcDbEvalVariant to a double value.
    /// </summary>
    ///
    /// <param name="dVal">
    /// The value to assign to the object.
    /// </param>
    ///
    /// <returns> 
    /// A reference to the updated variant.
    /// </returns>
    ///
    /// <remarks>
    /// The variant type is set to AcDbEvalVariant::kDouble.
    /// </remarks>
    /// 
    AcDbEvalVariant& operator=(double      dVal);

    /// <summary>
    /// Assigns an AcDbEvalVariant to a short value.
    /// </summary>
    ///
    /// <param name="iVal">
    /// The value to assign to the object.
    /// </param>
    ///
    /// <returns> 
    /// A reference to the updated variant.
    /// </returns>
    ///
    /// <remarks>
    /// The variant type is set to AcDbEvalVariant::kShort.
    /// </remarks>
    /// 
    AcDbEvalVariant& operator=(short       iVal);

    /// <summary>
    /// Assigns an AcDbEvalVariant to a long value.
    /// </summary>
    ///
    /// <param name="lVal">
    /// The value to assign to the object.
    /// </param>
    ///
    /// <returns> 
    /// A reference to the updated variant.
    /// </returns>
    ///
    /// <remarks>
    /// The variant type is set to AcDbEvalVariant::kLong.
    /// </remarks>
    /// 
    AcDbEvalVariant& operator=(Adesk::Int32  lVal);

    /// <summary>
    /// Assigns an AcDbEvalVariant to a character string.
    /// </summary>
    ///
    /// <param name="szVal">
    /// The value to assign to the object.
    /// </param>
    ///
    /// <returns> 
    /// A reference to the updated variant.
    /// </returns>
    ///
    /// <remarks>
    /// The variant type is set to AcDbEvalVariant::kString.
    /// </remarks>
    /// 
    AcDbEvalVariant& operator=(const ACHAR* szVal);
    
    /// <summary>
    /// Assigns an AcDbEvalVariant to the value stored in another
    /// AcDbEvalVariant.
    /// </summary>
    ///
    /// <param name="other">
    /// The value to assign to the object.
    /// </param>
    ///
    /// <returns> 
    /// A reference to the updated variant.
    /// </returns>
    ///
    AcDbEvalVariant& operator=(const AcDbEvalVariant& other);
    
    /// <summary>
    /// Moves an AcDbEvalVariant to the value stored in another
    /// AcDbEvalVariant.
    /// </summary>
    ///
    /// <param name="other">
    /// The value to move to the object.
    /// </param>
    ///
    /// <returns> 
    /// A reference to the updated variant.
    /// </returns>
    ///
    ACDBCORE2D_PORT AcDbEvalVariant& operator=(AcDbEvalVariant&& other);
    
    /// <summary>
    /// Assigns an AcDbEvalVariant to the value of an AcDbObjectId.
    /// </summary>
    ///
    /// <param name="id">
    /// The value to assign to the object.
    /// </param>
    ///
    /// <returns> 
    /// A reference to the updated variant.
    /// </returns>
    ///
    /// <remarks>
    /// The variant type is set to AcDbEvalVariant::kOldId.
    /// </remarks>
    /// 
    AcDbEvalVariant& operator=(const AcDbObjectId& id);

    /// <summary>
    /// Assigns an AcDbEvalVariant to a 2D point value.
    /// </summary>
    ///
    /// <param name="pt">
    /// The value to assign to the object.
    /// </param>
    ///
    /// <returns> 
    /// A reference to the updated variant.
    /// </returns>
    ///
    /// <remarks>
    /// The variant type is set to AcDbEvalVariant::kPoint2d.
    /// </remarks>
    /// 
    AcDbEvalVariant& operator=(const AcGePoint2d&  pt);

    /// <summary>
    /// Assigns an AcDbEvalVariant to a 3D point value.
    /// </summary>
    ///
    /// <param name="pt">
    /// The value to assign to the object.
    /// </param>
    ///
    /// <returns> 
    /// A reference to the updated variant.
    /// </returns>
    ///
    /// <remarks>
    /// The variant type is set to AcDbEvalVariant::kPoint3d.
    /// </remarks>
    /// 
     AcDbEvalVariant& operator=(const AcGePoint3d&  pt);

    /// <summary>
    /// Clears the contents of the AcDbEvalVariant and frees any allocated
    /// memory, including resbuf chains descending from this AcDbEvalVariant.
    /// Changed the <c>AcDbEvalVariant::restype</c> to AcDbEvalVariant::kNone.
    /// </summary>
    void clear();

    /// <summary> 
    /// Copies the value and data from a source AcDbEvalVariant object into this object.
    /// </summary>
    ///
    /// <param name="pOther">
    /// A pointer to the AcDbEvalVariant to copy from. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eWrongObjectType if
    /// <c>pObject</c> is not an AcDbEvalVariant. 
    /// </returns>
    virtual Acad::ErrorStatus copyFrom(const AcRxObject* pOther) override;
    
    /// <summary> 
    /// Tests whether this AcDbEvalVariant is less than another.
    /// This operator may only be used if both AcDbEvalVariants are of
    /// type kDouble, kShort, kLong, or kString.
    /// </summary>
    /// <param name="val">
    /// AcDbEvalVariant to compare to. 
    /// </param>
    /// <returns>
    /// True if this AcDbEvalVariant is less than val, false otherwise.
    /// If the two AcDbEvalVariants are of different types or if the
    /// data type is not kDouble, kShort, kLong, or kString then
    /// a value of false will be returned.
    /// </returns>
    bool operator < ( const AcDbEvalVariant& val ) const;
    
    /// <summary> 
    /// Tests whether this AcDbEvalVariant is greater than another.
    /// This operator may only be used if both AcDbEvalVariants are of
    /// type kDouble, kShort, kLong, or kString.
    /// </summary>
    /// <param name="val">
    /// AcDbEvalVariant to compare to. 
    /// </param>
    /// <returns>
    /// True if this AcDbEvalVariant is greater than val, false otherwise. 
    /// If the two AcDbEvalVariants are of different types or if the
    /// data type is not kDouble, kShort, kLong, or kString then
    /// a value of false will be returned.
    /// </returns>
    bool operator > ( const AcDbEvalVariant& val ) const;
    
    /// <summary> 
    /// Tests whether this AcDbEvalVariant is less than or equal to another.
    /// This operator may only be used if both AcDbEvalVariants are of
    /// type kDouble, kShort, kLong, or kString.
    /// </summary>
    /// <param name="val">
    /// AcDbEvalVariant to compare to. 
    /// </param>
    /// <returns>
    /// True if this AcDbEvalVariant is less than or equal to val,
    /// false otherwise.  If the two AcDbEvalVariants are of different types
    /// or if the data type is not kDouble, kShort, kLong, or kString then
    /// a value of false will be returned.
    /// </returns>
    bool operator <= ( const AcDbEvalVariant& val ) const;
    
    /// <summary> 
    /// Tests whether this AcDbEvalVariant is greater than or equal to another.
    /// This operator may only be used if both AcDbEvalVariants are of
    /// type kDouble, kShort, kLong, or kString.
    /// </summary>
    /// <param name="val">
    /// AcDbEvalVariant to compare to. 
    /// </param>
    /// <returns>
    /// True if this AcDbEvalVariant is greater than or equal to val,
    /// false otherwise.  If the two AcDbEvalVariants are of different types
    /// or if the data type is not kDouble, kShort, kLong, or kString then
    /// a value of false will be returned.
    /// </returns>
    bool operator >= ( const AcDbEvalVariant& val ) const;
    
    /// <summary> 
    /// Tests whether this AcDbEvalVariant is equal to another.
    /// </summary>
    /// <param name="val">
    /// AcDbEvalVariant to compare to. 
    /// </param>
    /// <returns>
    /// True if this AcDbEvalVariant is equal to val, false otherwise. 
    /// If the two AcDbEvalVariants are of different types then
    /// a value of false will be returned.
    /// </returns>
    bool operator == ( const AcDbEvalVariant& val ) const;
    
    /// <summary> 
    /// Tests whether this AcDbEvalVariant is unequal to another.
    /// </summary>
    /// <param name="val">
    /// AcDbEvalVariant to compare to. 
    /// </param>
    /// <returns>
    /// True if this AcDbEvalVariant is unequal to val, false otherwise. 
    /// If the two AcDbEvalVariants are of different types then
    /// a value of true will be returned.
    /// </returns>
    bool operator != ( const AcDbEvalVariant& val ) const;


    Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
    Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);

    Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
    Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);

    AcDb::DwgDataType getType() const;

    Acad::ErrorStatus setValue(AcDb::DxfCode groupcode, double value);
    Acad::ErrorStatus setValue(AcDb::DxfCode groupcode, short value);
    Acad::ErrorStatus setValue(AcDb::DxfCode groupcode, Adesk::Int32 value);
    Acad::ErrorStatus setValue(AcDb::DxfCode groupcode, const AcString& value);
    ACDBCORE2D_PORT Acad::ErrorStatus setValue(AcDb::DxfCode groupcode, const wchar_t * value);
    Acad::ErrorStatus setValue(AcDb::DxfCode groupcode, AcDbObjectId value);
    Acad::ErrorStatus setValue(AcDb::DxfCode groupcode, const AcGePoint3d& value);
    Acad::ErrorStatus setValue(AcDb::DxfCode groupcode, const AcGePoint2d& value);

    Acad::ErrorStatus getValue(double& value) const;
    Acad::ErrorStatus getValue(short& value) const;
    Acad::ErrorStatus getValue(Adesk::Int32& value) const;
    ACDBCORE2D_PORT Acad::ErrorStatus getValue(AcString& value) const;
    Acad::ErrorStatus getValue(AcDbObjectId& value, AcDbDatabase *pDb = NULL) const;
    ACDBCORE2D_PORT Acad::ErrorStatus getValue(AcGePoint3d& value) const;
    Acad::ErrorStatus getValue(AcGePoint2d& value) const;

    /// <summary>
    /// Converts an AcDbEvalVariant to an AcRxValue.
    /// </summary>
    /// <param name="type">
    /// The expected type of the returned AcRxValue.
    /// </param>
    /// <param name="value">
    /// The returned AcRxValue.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful, returns eInvalidInput if the
    /// conversion could not be performed. 
    /// </returns>
    Acad::ErrorStatus toAcRxValue(const AcRxValueType& type, 
                                  AcRxValue& value) const;

    /// <summary>
    /// Converts an AcRxValue to an AcDbEvalVariant. 
    /// </summary>
    /// <param name="value">
    /// The AcRxValue to convert. 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful, returns eInvalidInput if the
    /// conversion could not be performed and leaves the variant unmodified. 
    /// </returns>
    Acad::ErrorStatus fromAcRxValue(const AcRxValue& value);

protected:
    /// <summary>
    /// Initializes the contents of the AcDbEvalVariant. 
    /// </summary>
    ///
    /// <remarks>
    /// Called by constructor overloads to initialize the base resbuf memory. 
    /// </remarks>
    void init();

private:
    void takeStateFrom(AcDbEvalVariant &other); // used by move ctor and asst oper
};

class AcDbEvalEdgeInfo;

class AcDbEvalIdMap
{
public:
    virtual AcDbEvalNodeId find(const AcDbEvalNodeId& key) = 0;
    virtual void kill() = 0;
};

////////////////////////////////////////////////////////////////////////
// class AcDbEvalGraph
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class holds the network of inter-related 'elements' that implement the
/// smart behavior. Each individual 'element' (or AcDbEvalExpr) can depend on
/// zero or more other AcDbEvalExprs. So - it is the role of AcDbEvalGraph to
/// invoke the AcDbEvalExpr::evaluate() method for each of the elements it
/// contains when it is the right time to do so.  Right, in the sense, all the
/// AcDbEvalExprs that are depended on have had their evaluate() invoked. In
/// order to reprsent the inter-AcDbEvalExpr dependency - the AcDbEvalGraph
/// represents a Directed Graph. If an AcDbEvalExpr E1 depends on (requires
/// input from) an AcDbEvalExpr E2 - there is an edge from E2 to E1 represented
/// in the graph.
///
/// During evaluation, based on what AcDbEvalExpr's are 'active' (i.e. are
/// directly modified, for example, through the property palette, or grip
/// editing), is driven activation of a subset of AcDbEvalExprs reachable from
/// the activated set. The resulting subgraph is expected to be a DAG. It is
/// then topologically sorted to determine node evaluation order.
///
/// The current internal use of this graph class is for 'Enhanced Blocks' where
/// a graph of the expressions is maintained on the Block Table Record. This
/// graph is queried at graph editing time, and evaluated in order to trigger
/// the networked nodes (AcDbEvalExprs) that, through their evaluate() methods
/// being invoked, end up implementing the 'enhanced' behavior.
/// </summary>
///
/// <seealso cref="AcDbEvalExpr"/>
///
class AcDbEvalGraph : public AcDbObject
{
public:

    /// <summary>
    /// Special AcDbEvalNodeId values. 
    /// </summary>
    /// 
    enum NodeId {
        
        /// <summary>
        /// Null node Id. 
        /// </summary>
        kNullNodeId = 0
    };

    ACDB_DECLARE_MEMBERS(AcDbEvalGraph);

    /// <summary>
    /// Default constructor, constructs an empty graph.
    /// </summary>
    /// 
    AcDbEvalGraph();

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~AcDbEvalGraph();

    /* Management */

    // This set of static methods deal with managing the
    // association of an AcDbEvalGraph with an AcDbObject.

    /// <summary>
    /// Determines if a graph exists on the supplied object.  The object must 
    /// be database resident.
    /// </summary>
    ///
    /// <param name="pObj">
    /// The object from which to retrieve the graph.
    /// </param>
    /// <param name="pKey">
    /// The key at which the graph is associated. This means multiple graphs
    /// can be associated with one object.
    /// </param>
    ///
    /// <returns>
    /// Returns true if the graph exists. 
    /// </returns>
    static bool hasGraph(const AcDbObject*    pObj, 
                         const ACHAR*          pKey);

    /// <summary>
    /// Retrieves a graph, if one exists, from the supplied object with the
    /// requested open mode. The object must be database resident.
    /// </summary>
    /// 
    /// <param name="pObj">
    /// The object from which to retrieve the graph.
    /// </param>
    /// <param name="pKey">
    /// The key at which the graph is associated. This means multiple graphs
    /// can be associated with one object.
    /// </param>
    /// <param name="pGraph">
    /// Result graph. *pGraph is set to NULL if not found.
    /// </param>
    /// <param name="mode">
    /// The mode in which to open the graph.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eKeyNotFound if the
    /// graph with the specified key name does not exist.
    /// </returns>
    ///
    /// <remarks>
    /// The calling application is responsible for calling close() on the
    /// returned graph when it is no longer needed. 
    /// </remarks>
    ///
    static Acad::ErrorStatus getGraph(const AcDbObject*    pObj, 
                                      const ACHAR*          pKey,
                                      AcDbEvalGraph**      pGraph, 
                                      const AcDb::OpenMode mode);
    
    /// <summary>
    /// Creates a graph on the object at the supplied key. The object must be
    /// database resident.
    /// </summary>
    ///
    /// <param name="pObj">
    /// Object on which to create a graph.
    /// </param>
    /// <param name="pKey">
    /// Key at which to associate the new graph.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns eAlreadyInDb if the graph
    /// already exists on the object. 
    /// </returns>
    ///
    static Acad::ErrorStatus createGraph(AcDbObject* pObj,
                                         const ACHAR* pKey);

    /// <summary>
    /// Removes the graph, if one exists, at the supplied key. The object must
    /// be database resident. 
    /// </summary>
    ///
    /// <param name="pObj">
    /// Object from which to remove the graph.
    /// </param>
    /// <param name="pKey">
    /// Key at which the graph is associated on the object. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eKeyNotFound if the
    /// graph does not exist.
    /// </returns>
    ///
    static Acad::ErrorStatus removeGraph(AcDbObject* pObj,
                                         const ACHAR* pKey);
    /// <summary>
    /// Determines if a graph exists at the supplied key in the databae.
    /// </summary>
    ///
    /// <param name="pDb">
    /// The database from which to retrieve the graph.
    /// </param>
    /// <param name="pKey">
    /// The key at which the graph is registered in the database.
    /// </param>
    /// 
    /// <returns>
    /// Returns true if the graph exists.
    /// </returns>
    ///
    static bool hasGraph(AcDbDatabase*        pDb,  
                         const ACHAR*          pKey);

    /// <summary>
    /// Retrieves the graph from the database. This method
    /// provides the ability to associate a graph with a database
    /// (instead of a  specific object in the database).
    /// </summary>
    ///
    /// <param name="pDb">
    /// Database from which to retrieve the graph.
    /// </param>
    /// <param name="pKey">
    /// Key at which the graph is associated.
    /// </param>
    /// <param name="pGraph">
    /// The graph at the specified key, or NULL if the graph does not exist.
    /// </param>
    /// <param name="mode">
    /// The mode (read/write) in which to return the graph.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eKeyNotFound if the
    /// specified key could not be found. 
    /// </returns>
    ///
    /// <remarks>
    /// The calling application is responsible for calling close() on the
    /// returned graph when it is no longer needed. 
    /// </remarks>
    ///
    static Acad::ErrorStatus getGraph(AcDbDatabase*        pDb, 
                                      const ACHAR*          pKey,
                                      AcDbEvalGraph**      pGraph, 
                                      const AcDb::OpenMode mode);
    
    /// <summary>
    /// Creates a graph at the specified key for the database. This method
    /// provides the ability to associate a graph witha  database (instead of a
    /// specific object in the database).
    /// </summary>
    ///
    /// <param name="pDb">
    /// Database from which to create the graph.
    /// </param>
    /// <param name="pKey">
    /// Key at which the graph is associated.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    /// 
    static Acad::ErrorStatus createGraph(AcDbDatabase* pDb,
                                         const ACHAR*   pKey);

    /// <summary>
    /// Removes a graph at the specified key for the database.
    /// </summary>
    ///
    /// <param name="pDb">
    /// Database from which to remove the graph.
    /// </param>
    /// <param name="pKey">
    /// Key at which the graph is associated.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eKeyNotFound if there is
    /// no graph with that key associated to the database 
    /// </returns>
    static Acad::ErrorStatus removeGraph(AcDbDatabase* pDb,
                                         const ACHAR*   pKey);

    /// <summary>
    /// Replaces the graph on the object.
    /// </summary>
    ///
    /// <param name="pObj">
    /// Object on which to create a graph.
    /// </param>
    ///
    /// </param>
    /// <param name="pKey">
    /// Key at which the graph is associated.
    /// </param>
    ///
    /// <param name="graphId">
    /// AcDbObjectId of the graph that will be the replacement
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns eWrongObjectType if wrong type
    /// of object (i.e. not an AcDbEvalGraph).
    /// </returns>
    ///
    static Acad::ErrorStatus replaceGraph(AcDbObject* pObj,
                                         const ACHAR* pKey,
                                         AcDbObjectId grphId);
    /* Graph Query/Edit */

    // This set of methods are to do with editing the graph - i.e. adding,
    // removing, querying for nodes and edges.  The api is geared towards being
    // able to work with a non database resident version of the graph, i.e. it
    // deals with object pointers. 
    //
    // For an AcDbGraph which is database resident, the caller must close the
    // returned nodes after they are done. This also includes add() methods,
    // e.g. addNode(AcDbEvalExpr* pNode). The caller is expected to close the
    // supplied pNode argument

    /// <summary>
    /// Adds a node to the graph and returns the AcDbEvalNodeId of the newly
    /// added node. 
    /// </summary>
    ///
    /// <param name="pNode">
    /// A pointer to the node to add to the graph.
    /// </param>
    /// <param name="id">
    /// The id of newly added node. 
    /// </param>
    ///
    /// <returns>
    /// Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// If the graph is database-resident the caller must call close() on
    /// <c>pNode</c> when it is no longer needed. 
    /// </remarks>
    /// 
    virtual Acad::ErrorStatus addNode     (AcDbEvalExpr*   pNode,
                                           AcDbEvalNodeId& id);

    /// <summary>
    /// Removes a node from the graph. 
    /// </summary>
    ///
    /// <param name="id">
    /// The id of the node to remove from the graph. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eGraphNodeNotFound if no
    /// node with the specified id exists in the graph.
    /// </returns>
    /// 
    virtual Acad::ErrorStatus removeNode  (const AcDbEvalNodeId& id);


    /// <summary>
    /// Removes a node from the graph. Assumes the object is already opened
    ///  for read or write.
    /// </summary>
    ///
    /// <param name="pNode">
    /// The node to remove from the graph.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eGraphNodeNotFound
    /// if the node does not exist in the graph.
    /// </returns>
    /// 
    virtual Acad::ErrorStatus removeNode  (AcDbEvalExpr* pNode);


    /// <summary>
    /// Returns an array of all node ids contained in the graph.
    /// </summary>
    ///
    /// <param name="nodes">
    /// An array of AcDbEvalNodeId objects for all of the nodes in the graph.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. 
    /// </returns>
    ///
    virtual Acad::ErrorStatus getAllNodes (AcDbEvalNodeIdArray& nodes) const;

    /// <summary>
    /// Opens a node in the graph given its node id. 
    /// </summary>
    ///
    /// <param name="nodeId">
    /// The AcDbEvalNodeId of the node to open.
    /// </param>
    /// <param name="mode">
    /// The AcDb::OpenMode to open the node with.
    /// </param>
    /// <param name="ppNode">
    /// A pointer to the opened node. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eGraphNodeNotFound if no
    /// node with the specified id exists in the graph. 
    /// </returns>
    ///
    /// <remarks>
    /// Callers must call close() on the returned node pointer when it is no
    /// longer needed.
    /// </remarks>
    virtual Acad::ErrorStatus getNode     (const AcDbEvalNodeId& nodeId,
                                           AcDb::OpenMode        mode,
                                           AcDbObject**        ppNode) const;

    /// <summary>
    /// Adds a non-invertable edge between two nodes in the graph.
    /// </summary>
    ///
    /// <param name="idFrom">
    /// The AcDbEvalNodeId of the node from which the edge originates.
    /// </param>
    /// <param name="idTo">
    /// The AcDbEvalNodeId of the node at which the edge terminates. 
    /// </param>
    ///
    /// <returns> 
    /// Returns Acad::eOk if successful. Returns Acad::eGraphNodeNotFound if
    /// either of the nodes are not resident in the graph. 
    /// </returns>
    ///
    virtual Acad::ErrorStatus addEdge(const AcDbEvalNodeId& idFrom, 
                                      const AcDbEvalNodeId& idTo);
    /// <summary>
    /// Adds an edge between two nodes in the graph.
    /// </summary>
    ///
    /// <param name="idFrom">
    /// The AcDbEvalNodeId of the node from which the edge originates.
    /// </param>
    /// <param name="idTo">
    /// The AcDbEvalNodeId of the node at which the edge terminates. 
    /// </param>
    /// <param name="bInvertible">
    /// True if the edge can be inverted depending on which of the nodes 
    /// has been activated. 
    /// </param>
    ///
    /// <returns> 
    /// Returns Acad::eOk if successful. Returns Acad::eGraphNodeNotFound if
    /// either of the nodes are not resident in the graph. 
    /// </returns>
    ///
    virtual Acad::ErrorStatus addEdge(const AcDbEvalNodeId& idFrom, 
                                      const AcDbEvalNodeId& idTo,
                                      bool  bInvertible);

    /// <summary>
    /// Removes an edge between to nodes in the graph.
    /// </summary>
    ///
    /// <param name="idFrom">
    /// The AcDbEvalNodeId of the node from which the edge originates.
    /// </param>
    /// <param name="idTo">
    /// The AcDbEvalNodeId of the node at which the edge terminates. 
    /// </param>
    ///
    /// <returns> 
    /// Returns Acad::eOk if successful. Returns Acad::eGraphEdgeNotFound if
    /// an edge between the nodes does not exist.
    /// </returns>
    ///
    virtual Acad::ErrorStatus removeEdge(const AcDbEvalNodeId& idFrom,
                                         const AcDbEvalNodeId& idTo);

    /// <summary>
    /// Returns a list of incoming edges to a node in the graph.
    /// </summary>
    ///
    /// <param name="nodeId">
    /// The AcDbEvalNodeId of the node to retrieve incoming edges for.
    /// </param>
    /// <param name="edges">
    /// An array of AcDbEvalEdgeInfo objects describing incoming edges for the
    /// node. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eGraphNodeNotFound if
    /// the node with the specified id does not exist in the graph.
    /// </returns>
    /// 
    virtual Acad::ErrorStatus getIncomingEdges(const AcDbEvalNodeId& nodeId,
                                      AcDbEvalEdgeInfoArray& edges) const;

    /// <summary>
    /// Returns a list of outgoing edges from a node in the graph.
    /// </summary>
    ///
    /// <param name="nodeId">
    /// The AcDbEvalNodeId of the node to retrieve outgoing edges for.
    /// </param>
    /// <param name="edges">
    /// An array of AcDbEvalEdgeInfo objects describing outgoing edges for the
    /// node. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eGraphNodeNotFound if
    /// the node with the specified id does not exist in the graph.
    /// </returns>
    ///
    virtual Acad::ErrorStatus getOutgoingEdges(const AcDbEvalNodeId& nodeId,
                                      AcDbEvalEdgeInfoArray& edges) const;

    /// <summary>
    /// Returns information about an edge between two nodes in a graph. 
    /// </summary>
    ///
    /// <param name="nodeFrom">
    /// The AcDbEvalNodeId of the orginating node for the edge.
    /// </param>
    /// <param name="nodeTo">
    /// The AcDbEvalNodeId of the destination node for the edge.
    /// </param>
    /// <param name="einfo">
    /// An AcDbEvalEdgeInfo object describing the edge. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eGraphNodeNotFound if
    /// either of the nodes with the specified id does not exist in the graph.
    /// Returns Acad::eGraphEdgeNotFound if edge exists between the nodes. 
    /// </returns>
    virtual Acad::ErrorStatus getEdgeInfo(const AcDbEvalNodeId& nodeFrom,
            const AcDbEvalNodeId& nodeTo, AcDbEvalEdgeInfo& einfo) const;


    /// <summary>
    /// Adds the nodes from one graph to another graph by moving the nodes and
    /// edges from the source graph to this graph.
    /// </summary>
    ///
    /// <param name="pGraphToAdd">
    /// The graph containing the nodes and edges to add to this graph.
    /// </param>
    ///
    /// <param name="idMap">
    /// Pointer to output map from old node ids within 'pGraphToAdd' to their 
    /// new ids within this graph.  
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. 
    /// </returns>
    ///
    /// <remarks> 
    /// All nodes and edges in <paramref name="pGraphToAdd"/> are moved to the
    /// destination graph. The argument graph is emptied as as result
    /// of the operation.
    /// </remarks>
    ///
    virtual Acad::ErrorStatus addGraph(AcDbEvalGraph* pGraphToAdd, 
                AcDbEvalIdMap*& idMap);

    /* Evaluation */

    /// <summary>
    /// Evaluates the class by traversing the graph and invoking
    /// <c>AcDbEvalExpr::evaluate()</c> on all of the visited nodes. 
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if succssful. If any of the calls to
    /// <c>AcDbEvalExpr::evaluate()</c> fails the error returned by
    /// <c>AcDbEvalExpr::evaluate()</c> is returned by this method.
    /// </returns>
    /// 
    /// <remarks>
    /// Applications must first activate one or more nodes in the graph by 
    /// calling <c>AcDbEvalGraph::activatedNodes()</c> before calling this
    /// method. 
    /// </remarks>
    /// 
    virtual Acad::ErrorStatus evaluate() const;
    
    /// <summary>
    /// Evaluates the class by traversing the graph and invoking
    /// <c>AcDbEvalExpr::evaluate()</c> on all of the visited nodes. 
    /// </summary>
    ///
    /// <param name="pContext">
    /// A pointer to an AcDbEvalContext object that will be passed to each node
    /// as it is visited when calling its <c>AcDbEvalExpr::evaluate()</c>
    /// method. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if succssful. If any of the calls to
    /// <c>AcDbEvalExpr::evaluate()</c> fails the error returned by
    /// <c>AcDbEvalExpr::evaluate()</c> is returned by this method.
    /// </returns>
    /// 
    /// <remarks>
    /// Applications must first activate one or more nodes in the graph by 
    /// calling <c>AcDbEvalGraph::activatedNodes()</c> before calling this
    /// method. 
    /// </remarks>
    /// 
    virtual Acad::ErrorStatus evaluate(
            const AcDbEvalContext*     pContext) const; 

    /// <summary>
    /// Evaluates the class by traversing the graph and invoking
    /// <c>AcDbEvalExpr::evaluate()</c> on all of the visited nodes. 
    /// </summary>
    ///
    /// <param name="pContext">
    /// A pointer to an AcDbEvalContext object that will be passed to each node
    /// as it is visited when calling its <c>AcDbEvalExpr::evaluate()</c>
    /// method. 
    /// </param>
    /// <param name="activatedNodes">
    /// An array of AcDbEvalNodeIds to activate when performing the evaluation. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if succssful. If any of the calls to
    /// <c>AcDbEvalExpr::evaluate()</c> fails the error returned by
    /// <c>AcDbEvalExpr::evaluate()</c> is returned by this method.
    /// </returns>
    /// 
    /// <remarks>
    /// Applications may activate and evaulate nodes in one step by providing a
    /// non-null <paramref name="activatedNodes"/> array pointer. Otherwise
    /// applications must first activate one or more nodes in the graph by
    /// calling <c>AcDbEvalGraph::activatedNodes()</c> before calling this
    /// method. 
    /// </remarks>
    /// 
    virtual Acad::ErrorStatus evaluate(
            const AcDbEvalContext*     pContext,
            const AcDbEvalNodeIdArray* activatedNodes) const; 

    /// <summary>
    /// Activates a collection of nodes in a graph.
    /// </summary>
    ///
    /// <param name="activatedNodes">
    /// An array of AcDbEvalNodeIds of the nodes in the graph to activate. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eGraphCyclesFound if the 
    /// node activation resulted in a cyclic graph. 
    /// </returns>
    ///
    /// <remarks>
    /// Applications must activate nodes in a graph before calling
    /// <c>AcDbEvalGraph::evaluate()</c>. Active nodes are used as the starting
    /// point for the directed traversal of the graph during graph evaluation. 
    ///  
    /// If activatedNodes is empty, all the nodes in the graph are deactivated.
    /// </remarks>
    ///
    virtual Acad::ErrorStatus activate(
            const AcDbEvalNodeIdArray& activatedNodes) const;
    
    /// <summary>
    /// Activates a collection of nodes in a graph.
    /// </summary>
    ///
    /// <param name="activatedNodes">
    /// An array of AcDbEvalNodeIds of the nodes in the graph to activate. 
    /// </param>
    /// <param name="pActiveSubgraph">
    /// An array of the nodes that would be visited given the activated nodes.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eGraphCyclesFound if the 
    /// node activation resulted in a cyclic graph. 
    /// </returns>
    ///
    /// <remarks>
    /// Applications must activate nodes in a graph before calling
    /// <c>AcDbEvalGraph::evaluate()</c>. Active nodes are used as the starting
    /// point for the directed traversal of the graph during graph evaluation. 
    ///  
    /// If activatedNodes is empty, all the nodes in the graph are deactivated.
    /// </remarks>
    ///
    virtual Acad::ErrorStatus activate(
            const AcDbEvalNodeIdArray& activatedNodes,
            AcDbEvalNodeIdArray*       pActiveSubgraph) const;

    /// <summary>
    /// Activates a collection of nodes in a graph.
    /// </summary>
    ///
    /// <param name="activatedNodes">
    /// An array of AcDbEvalNodeIds of the nodes in the graph to activate. 
    /// </param>
    /// <param name="pActiveSubgraph">
    /// An array of the nodes that would be visited given the activated nodes.
    /// </param>
    /// <param name="pCycleNodes">
    /// An array of the nodes that are cyclic given the activated nodes.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eGraphCyclesFound if the 
    /// node activation resulted in a cyclic graph. 
    /// </returns>
    ///
    /// <remarks>
    /// Applications must activate nodes in a graph before calling
    /// <c>AcDbEvalGraph::evaluate()</c>. Active nodes are used as the starting
    /// point for the directed traversal of the graph during graph evaluation. 
    ///  
    /// If activatedNodes is empty, all the nodes in the graph are deactivated.
    /// </remarks>
    ///
    virtual Acad::ErrorStatus activate(
            const AcDbEvalNodeIdArray& activatedNodes,
            AcDbEvalNodeIdArray*       pActiveSubgraph,
            AcDbEvalNodeIdArray*       pCycleNodes) const;

    /// <summary>
    /// Determines whether the specified node is activated in the graph.
    /// </summary>
    ///
    /// <param name="id">
    /// The AcDbEvalNodeId of a node in the graph.
    /// </param>
    /// <param name="bIsActive">
    /// True if the specified node exists in the graph and is active, false
    /// otherwise.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eGraphNodeNotFound no
    /// node with the specified id exists in the graph. 
    /// </returns>
    ///
    virtual Acad::ErrorStatus getIsActive(const AcDbEvalNodeId& id,
            bool& bIsActive) const;

    /// <summary>
    /// Determines whether two graphs are 'equal' with equality defined
    /// as Graph A equals Graph B if A is a subgraph of B and B is a subgraph
    /// of A - where 'is a subgraph' is defined by the isSubgraphOf() method
    /// below.
    /// </summary>
    ///
    /// <param name="pOther">
    /// The graph to be tested for equality with
    /// </param>
    ///
    /// <returns>
    /// true if the graphs are equal. 
    /// </returns>
    ///
    virtual bool equals(const AcDbEvalGraph* pOther) const;

    /// <summary>
    /// Determines whether the 'this' graph is a subgraph of the graph 
    /// passed in as an argument. 'A is a subgraph of B' is defined by
    /// considering of mapping of nodes from A to B map(node) where the
    /// nodeId of node in A is the same as the nodeId of the node
    /// map(node) in B. If no such mapping exists, A is not a subgraph of
    /// B.
    /// If such a mapping exists - the order and types of both the
    /// incoming and outgoing edges from nodes in A have to be a subset of 
    /// the incoming and outgoing edges for each of the mapped nodes in B.
    /// If this is true, A is a subgraph of B. If not, A is not a subgraph 
    /// of B.
    ///
    /// </summary>
    ///
    /// <param name="pOther">
    /// The graph to be tested against being a subgraph of.
    /// </param>
    ///
    /// <returns>
    /// true if 'this' is a subgraph of 'pOther'
    /// </returns>
    ///
    virtual bool isSubgraphOf(const AcDbEvalGraph* pOther) const;


    /// <summary>
    /// Adds this graph to the database, giving it a 
    /// handle and an object ID. 
    /// The new object ID is returned in the objId argument.
    /// All of this graph's nodes are added to the database and 
    /// this graph is made their owner.
    /// This function does not establish ownership of this graph.
    /// </summary>
    ///
    /// <param name="objId">
    /// Output new object ID obtained by this function.
    /// </param>
    ///
    /// <param name="pDb">
    /// The destination database.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    virtual Acad::ErrorStatus postInDatabase(AcDbObjectId& objId, AcDbDatabase* pDb);

};


////////////////////////////////////////////////////////////////////////
// class AcDbEvalEdgeInfo
////////////////////////////////////////////////////////////////////////

/// <summary>
/// Utility class that holds directed edge information between two nodes in an
/// AcDbEvalGraph. Instances of this class are returned by calls to edge methods
/// on AcDbEvalGraph. 
/// </summary>
///
/// <seealso cref="AcDbEvalGraph.getIncomingEdges"/>
/// <seealso cref="AcDbEvalGraph.getOutgoingEdges"/>
/// <seealso cref="AcDbEvalGraph.getEdgeInfo"/>
/// 
class AcDbEvalEdgeInfo
{
public:

    /// <summary>
    /// Constructor.
    ///Adesk::UInt32 </summary>
    AcDbEvalEdgeInfo()
        : mFlags(0), mRefCount(0)
    {
        mIdFrom = AcDbEvalGraph::kNullNodeId;
        mIdTo = AcDbEvalGraph::kNullNodeId;
    }

    /// <summary>
    /// Constructor.
    /// </summary>
    ///
    /// <param name="from">
    /// The graph node id of the node from which this edge originates. 
    /// </param>
    /// <param name="to">
    /// The graph node id of the node at which this edge terminates. 
    /// </param>
    /// <param name="flags">
    /// Description to come.
    /// </param>
    /// <param name="count">
    /// Description to come. 
    /// </param>
    AcDbEvalEdgeInfo(AcDbEvalNodeId from,  
                     AcDbEvalNodeId to, 
                     Adesk::Int32   flags,
                     Adesk::UInt32  count)
        : mIdFrom(from), mIdTo(to), mFlags(flags), mRefCount(count)
        {}

    /// <summary>
    /// The originating node of the edge.
    /// </summary>
    ///
    /// <returns>
    /// The edge's originating node id. 
    /// </returns>
    AcDbEvalNodeId from () const;

    /// <summary>
    /// The terminal node of the edge.
    /// </summary>
    /// 
    /// <returns>
    /// The edge's terminating node id. 
    /// </returns>
    AcDbEvalNodeId to   () const;

    /// <summary>
    /// Description to come.
    /// </summary>
    /// 
    /// <returns>
    /// Description to come.
    /// </returns>
    ///
    Adesk::UInt32 refCount() const;

    /// <summary> 
    /// Indicates whether the edge is invertable, i.e. whether the originating
    /// and terminating nodes can be swapped depending on which of the nodes is
    /// activated.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if the edge is invertable. 
    /// </returns>
    bool isInvertible () const;

    /// <summary>
    /// Tests whether an edge is suppressed, i.e. temporarily considered
    /// 'removed' from the graph during activation and/or evaluation.
    /// This flag applies only to an invertible pair of edges, where
    /// during activation one of the directions are 'active' and the
    /// complementary one 'suppressed'
    /// </summary>
    ///
    /// <returns>
    /// true if the edge is active.
    /// </returns>
    ///
    bool isSuppressed  () const;

    /// <summary>
    /// Member wise equality
    /// </summary>
    ///
    /// <param name="other">
    /// Item to be tested against for equality.
    /// </param>
    ///
    /// <returns>
    /// true if the two items are equal
    /// </returns>
    ///
    bool operator == (const AcDbEvalEdgeInfo& other) const;

private:
    AcDbEvalNodeId mIdFrom;
    AcDbEvalNodeId mIdTo;
    Adesk::Int32 mFlags;
    Adesk::UInt32 mRefCount;
};


////////////////////////////////////////////////////////////////////////
// class AcDbEvalExpr
////////////////////////////////////////////////////////////////////////
//  
/// <summary> 
/// This class represents a single node in an AcDbEvalGraph. The node
/// represents an action (or "expression"). The owning graph calls the node's
/// evaluate() method when visiting the node during a traversal of the graph
/// from within the graph's evaluate().
/// </summary>
class AcDbEvalExpr : public AcDbObject
{

public:
    ACDB_DECLARE_MEMBERS(AcDbEvalExpr);
    
    /// <summary>
    /// Default constructor.
    /// </summary>
    /// 
    AcDbEvalExpr();

    /// <summary>
    /// Destructor. 
    /// </summary>
    /// 
    virtual ~AcDbEvalExpr();

    /* Graph methods */
    
    /// <summary>
    /// Returns a pointer to the graph owning the node. 
    /// </summary>
    ///
    /// <param name="pGraph">
    /// Pointer to the graph owning the node. 
    /// </param>
    /// <param name="mode">
    /// The AcDb::OpenMode to open the owning graph with. 
    /// </param>
    /// 
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eNulNodeId if the node
    /// is not graph-resident. 
    /// </returns>
    ///
    /// <remarks>
    /// The caller is responsible for calling <c>close</c> on the returned
    /// graph pointer. 
    /// </remarks>
    ///
    Acad::ErrorStatus getGraph(AcDbEvalGraph** pGraph, 
                               AcDb::OpenMode  mode) const;
    
    /// <summary>
    /// Returns the id of the node. 
    /// </summary>
    ///
    /// <returns> 
    /// The ID of the node if it is graph-resident. Returns AcDbGraph::kNullId
    /// if the node is not graph-resident.
    /// </returns>
    ///
    /// <remarks>
    /// When a node is added to a graph it is assigned an ID that is unique
    /// among all nodes in the graph. If the node is not graph-resident the id
    /// will be AcDbEvalGraph::kNullNodeId;
    /// </remarks>
    ///
    AcDbEvalNodeId    nodeId() const;

    /* Graph notification methods */

    /// <summary>
    /// Called when a node is added to a graph.
    /// </summary>
    /// 
    /// <param name="pGraph">
    /// A pointer to the graph the node is added to.
    /// </param>
    ///
    /// <remarks>
    /// AcDbEvalGraph::addNode() calls this method on the node after it has
    /// been added to the graph. 
    /// </remarks>
    ///
    virtual void addedToGraph       (AcDbEvalGraph*  pGraph);

    /// <summary>
    /// Called when a node is removed from a graph.
    /// </summary>
    /// 
    /// <param name="pGraph">
    /// A pointer to the graph the node is removed from.
    /// </param>
    /// 
    /// <remarks>
    /// AcDbEvalGraph::removeNode() calls this method on the node after it has
    /// been removed from the graph.
    /// </remarks>
    ///
    virtual void removedFromGraph   (AcDbEvalGraph*  pGraph);

    /// <summary>
    /// Called when a node with a shared edge to this node is removed from the
    /// graph.
    /// </summary>
    /// 
    /// <param name="adjNodeId">
    /// The AcDbEvalNodeId of the removed node.
    /// </param>
    /// 
    /// <remarks>
    /// AcDbEvalGraph::removeNode() calls this method on nodes with shared
    /// edges to the node being removed. 
    /// </remarks>
    ///
    virtual void adjacentNodeRemoved (const AcDbEvalNodeId& adjNodeId);
    
    /// <summary>
    /// Called when an edge on the node is removed. 
    /// </summary>
    ///
    /// <param name="adjEdgeNodeId">
    /// The AcDbEvalNodeId of the node whose shared edge is being removed. 
    /// </param>
    ///
    /// <remarks>
    /// AcDbEvalGraph::removeEdge() calls this method on node at either end of
    /// the edge being removed.
    /// </remarks>
    virtual void adjacentEdgeRemoved (const AcDbEvalNodeId& adjEdgeNodeId);
    
    /// <summary>
    /// Called when an edge is added.
    /// </summary>
    ///
    /// <param name="fromId">
    /// The from AcDbEvalNodeId of the node whose shared edge is being 
    /// removed. 
    /// </param>
    ///  
    /// <param name="toId">
    /// The to AcDbEvalNodeId of the node whose shared edge is being 
    /// removed. 
    /// </param>
    ///  
    /// <param name="bIsInvertible">
    /// Whether the edge is invertible or not.
    /// </param>
    ///
    /// <remarks>
    /// Both the AcDbEvalGraph::addEdge() methods calls this method on each
    /// of the nodes at either end of the edge being added. So, when adding an
    /// invertible edge, for example, Four notifications will occur.
    /// </remarks>
    ///
    virtual void adjacentEdgeAdded (const AcDbEvalNodeId& fromId,
            const AcDbEvalNodeId& toId,
            bool bIsInvertible);

    /// <summary>
    /// Called when a node is about to be moved from pFromGraph to another
    /// graph.
    /// </summary>
    ///
    /// <param name="pFromGraph">
    /// The the graph from which the node is being transplanted from.
    /// </param>
    ///
    /// <remarks>
    /// AcDbEvalGraph::addGraph() calls this method on the node
    /// just before it is added to the destination graph.
    /// </remarks>
    ///
    virtual void movedFromGraph (AcDbEvalGraph* pFromGraph);

    /// <summary>
    /// Called when a node is done being moved from pFromGraph to another
    /// graph.
    /// </summary>
    ///
    /// <param name="pIntoGraph">
    /// The the graph into which the node is being transplanted to.
    /// </param>
    ///
    /// <remarks>
    /// AcDbEvalGraph::addGraph() calls this method on the node
    /// just after it is added to the destination graph.
    /// Since addGraph() copies a disjoint subgraph into the destination
    /// graph, the newly added subgraph is isomorphic to the source
    /// graph in the addGraph operation.
    /// </remarks>
    ///
    virtual void movedIntoGraph (AcDbEvalGraph* pIntoGraph);


    /// <summary>
    /// Called exactly once for each node in a graph after all nodes 
    /// in a graph had their ids changed.
    /// </summary>
    ///
    /// <param name="idMap">
    /// Map from old node ids within 'pGraphToAdd' to their new ids within
    /// this graph.  Should be empty initially and be the size of the number
    /// of nodes on successful return.
    /// </param>
    /// 
    /// <remarks>
    /// AcDbEvalGraph::addGraph() calls this method on each node in the
    /// to-be-added graph just after after all nodes have been added to the 
    /// destination graph.
    /// The default behavior is to do nothing.  Some subclasses of 
    /// AcDbEvalExpr should override this function to update
    /// their references to other nodes.
    /// Nodes should not alter the map.
    /// </remarks>
    ///
    virtual void remappedNodeIds (AcDbEvalIdMap& idMap);

    /// <summary>
    /// Called when a node is done being inserted due to a copy
    /// operation from one graph to another.
    /// </summary>
    ///
    /// <param name="pIntoGraph">
    /// The the graph into which the node is being added to.
    /// </param>
    ///
    /// <remarks>
    /// AcDbEvalGraph::copyFrom() calls this method on the nodes
    /// that are copies from the argument graph nodes. Since all the
    /// nodes from the argument graph, as well as their edges are copied,
    /// the graph structure in 'this' becomes isomorphic to the 
    /// graph structure in the source graph.
    /// </remarks>
    ///
    virtual void copiedIntoGraph(AcDbEvalGraph* pIntoGraph);

    /// <summary>
    /// Returns whether this node should be actived
    /// </summary>
    ///
    /// <remarks>
    /// This method allows a node to indicate that its active() method should
    /// not be called directly.  The default implementation is to return true,
    /// nodes are by default activatable.
    /// </remarks>
    ///
    virtual bool isActivatable  ();
    
    /// <summary>
    /// Called on graph resident nodes that become active. 
    /// </summary>
    ///
    /// <param name="argumentActiveList">
    /// An array of AcDbEvalNodeIds of the nodes being activated in the graph.
    /// </param>
    ///
    /// <remarks>
    /// This method is called by AcDbEvalGraph::activate(), or by
    /// AcDbEvalGraph::evaluate() when it is called with a non-null node
    /// activation arrray, on every node being activated by the call. 
    /// </remarks>
    ///
    virtual void activated           (AcDbEvalNodeIdArray& argumentActiveList);
    
    /// <summary>
    /// Called on graph resident nodes before traversing the graph in a call to
    /// AcDbEvalGraph::evaluate().
    /// </summary>
    ///
    /// <param name="bNodeIsActive">
    /// True if the node has been activated for the traversal.
    /// </param>
    ///
    /// <remarks>
    /// This method is called by AcDbEvalGraph::evaluate() for nodes that will
    /// be traversed during the graph evaluation.
    /// </remarks>
    ///
    virtual void graphEvalStart      (bool bNodeIsActive);
    
    /// <summary>
    /// Called on graph resident nodes after traversing the graph in a call to
    /// AcDbEvalGraph::evaluate().
    /// </summary>
    ///
    /// <param name="bNodeIsActive">
    /// True if the node has been activated for the traversal.
    /// </param>
    ///
    /// <remarks>
    /// This method is called by AcDbEvalGraph::evaluate() for nodes that were
    /// visited during the taversal of the graph.
    /// </remarks>
    ///
    virtual void graphEvalEnd        (bool bNodeIsActive);
    
    /// <summary>
    /// Called on graph resident nodes after aborting the traversal of the
    /// graph in a call to AcDbEvalGraph::evaluate().
    /// </summary>
    ///
    /// <param name="bNodeIsActive">
    /// True if the node has been activated for the traversal.
    /// </param>
    ///
    /// <remarks>
    /// This method is called by AcDbEvalGraph::evaluate() for nodes that were
    /// in the traversal list of an aborted graph evaluation. 
    /// </remarks>
    ///
    virtual void graphEvalAbort      (bool bNodeIsActive);

    /* Evaluation methods */

    /// <summary>
    /// Causes the expression represented by the node to be evaluated. Called
    /// by for a graph-resident node when the node is visited during a call to
    /// <c>AcDbEvalGraph::evaluate()</c>
    /// </summary>
    ///
    /// <param name="ctxt">
    /// A pointer to the AcDbEvalContext object used for the graph evaluation.
    /// May be NULL.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Any non successful result terminates
    /// the graph traversal.
    /// </returns>
    ///
    /// <remarks>
    /// The default implementation does nothing and returns Acad::eOk.
    /// </remarks>
    ///
    virtual Acad::ErrorStatus evaluate(const AcDbEvalContext* ctxt);


    /// <summary>
    /// Determines if two AcDbEvalExprs are equal. The default
    /// implementation is to check that the concrete class types
    /// are the same, i.e. this->isA() == pOther->isA().
    /// </summary>
    ///
    /// <param name="pOther">
    /// Argument to be tested for equality against.
    /// </param>
    ///
    /// <returns>
    /// true if the objects are equal. 
    /// </returns>
    ///
    virtual bool equals(const AcDbEvalExpr* pOther) const;

    /* Expression value methods */

    /// <summary>
    /// The value of the variant node. 
    /// </summary>
    ///
    /// <returns> 
    /// An AcDbEvalVariant representing the value of the evaluated expression.
    /// </returns>
    ///
    /// <remarks>
    /// The value is usually updated during the <c>AcDbEvalExpr::evaluate()</c>
    /// call. The default value is uninitialized
    /// (<c>AcDbEvalVariant::Type::kNone</c>).
    /// </remarks>
    ///
    AcDbEvalVariant value() const;

    /// <summary>
    /// Adds this object to the database, giving it a 
    /// handle and an object ID. 
    /// The new object ID is returned in the objId argument.
    /// This function does not establish ownership of this object.
    /// Subclasses with child objects should override this
    /// function to add them to the database at this time and
    /// establish ownership.
    /// </summary>
    ///
    /// <param name="objId">
    /// Output new object ID obtained by this function.
    /// </param>
    ///
    /// <param name="pDb">
    /// The destination database.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    virtual Acad::ErrorStatus postInDatabase(AcDbObjectId& objId, AcDbDatabase* pDb);

protected:
    /// <summary>
    /// The value of the expression. <seealso cref="value"/>.
    /// </summary>
    ///
    /// <remarks>
    /// The default implementation does not persist this value, nor does it
    /// ever update it from its initialized value
    /// (<c>AcDbEvalVaraint::Type::kNone</c>).
    /// </remarks>
    ///
    AcDbEvalVariant m_lastValue;
    friend class AcDbImpEvalExpr;
};


////////////////////////////////////////////////////////////////////////
// class AcDbEvalConnectable
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class implements a runtime inspection interface for named properties
/// on AcDbEvalExpr objects. Objects implementing this class expose a
/// collection of named, typed properties and semantics for "connecting"
/// properties between AcDbEvalGraph resident connectable instances. 
/// </summary>
///
class AcDbEvalConnectable : public AcDbEvalExpr
{
public:
    ACDB_DECLARE_MEMBERS(AcDbEvalConnectable);

    /// <summary>
    /// Destructor.
    /// </summary>
    ///
    virtual ~AcDbEvalConnectable();
    
    /* Connection Inspection */

    /// <summary>
    /// Returns an array of named connections.
    /// </summary>
    ///
    /// <param name="names">
    /// Returned array of named connections. 
    /// </param>
    ///
    /// <returns>
    /// Acad::eOk if successful.
    /// </returns>
    ///
    virtual Acad::ErrorStatus getConnectionNames (AcStringArray& names) const;

    /// <summary>
    /// Tests whether an object exposes a connection.
    /// </summary>
    ///
    /// <param name="name">
    /// The name of the connection to test for.
    /// </param>
    ///
    /// <returns>
    /// True if a connection with the specified name exists.
    /// </returns>
    ///
    virtual bool              hasConnectionNamed (const AcString& name) const;
    
    /// <summary>
    /// Returns the <c>AcDbEvalVariant::Type</c> of a named connection.
    /// </summary>
    ///
    /// <param name="name">
    /// The name of the connection to return the type of.
    /// </param>
    /// <param name="type">
    /// The type of the named connection.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eKeyNotFound if no
    /// connection with the specified name exists. 
    /// </returns>
    ///
    virtual Acad::ErrorStatus getConnectionType  (
                                    const AcString&        name, 
                                    AcDb::DwgDataType& type) const;
    
    /* Connection Operations */

    /// <summary>
    /// Returns the value of a named connection.
    /// </summary>
    ///
    /// <param name="name">
    /// The name of the connection to return the value of. 
    /// </param>
    /// <param name="value">
    /// The value of the named connection.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eKeyNotFound if no
    /// connection with the specified name exists. 
    /// </returns>
    ///
    virtual Acad::ErrorStatus getConnectionValue (
                                    const AcString&    name,
                                    AcDbEvalVariant&    value) const;
    
    /// <summary>
    /// Sets the value of a named connection.
    /// </summary>
    ///
    /// <param name="name">
    /// The name of the connection to set the value of. 
    /// </param>
    /// <param name="value">
    /// The new value of the named connection.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eKeyNotFound if no
    /// connection with the specified name exists. 
    /// </returns>
    virtual Acad::ErrorStatus setConnectionValue (
                                    const AcString&       name,
                                    const AcDbEvalVariant& value);

    /// <summary>
    /// Connects a named connection on this object to a connection on
    /// another AcDbEvalConnectable. Both objects must be graph-resident.
    /// </summary>
    ///
    /// <param name="thisConnection">
    /// The name of the connection on this object.
    /// </param>
    /// <param name="sourceConnectableId">
    /// The AcDbEvalNodeId of the other connectable.
    /// </param>
    /// <param name="sourceConnectionName">
    /// The name of the connection on the other connectable.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eKeyNotFound if either
    /// object does not expose its respective named connection. 
    /// </returns>
    ///
    virtual Acad::ErrorStatus connectTo (
                                const AcString&      thisConnection, 
                                const AcDbEvalNodeId sourceConnectableId,
                                const AcString&      sourceConnectionName);

    /// <summary>
    /// Disconnects a named connection on this object from a connection on
    /// another AcDbEvalConnectable. Both objects must be graph-resident.
    /// </summary>
    ///
    /// <param name="thisConnection">
    /// The name of the connection on this object.
    /// </param>
    /// <param name="sourceConnectableId">
    /// The AcDbEvalNodeId of the other connectable.
    /// </param>
    /// <param name="sourceConnectionName">
    /// The name of the connection on the other connectable.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eKeyNotFound if either
    /// object does not expose its respective named connection. 
    /// </returns>
    ///
    virtual Acad::ErrorStatus disconnectFrom (
                                const AcString&      thisConnection,
                                const AcDbEvalNodeId sourceConnectableId,
                                const AcString&      sourceConnectionName);
    
    /// <summary>
    /// Determines whether a connection is allowed between to objects.
    /// </summary>
    ///
    /// <param name="thisConnection">
    /// The name of the connection on this object.
    /// </param>
    /// <param name="sourceConnectableId">
    /// The AcDbEvalNodeId of the other connectable.
    /// </param>
    /// <param name="sourceConnectionName">
    /// The name of the connection on the other connectable.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if the connection is allowed. Returns
    /// Acad::eKeyNotFound if either object does not expose its respective
    /// named connection. 
    /// </returns>
    ///
    virtual bool connectionAllowed ( 
                            const AcString&      thisConnection,
                            const AcDbEvalNodeId sourceConnectableId,
                            const AcString&      sourceConnectionName) const;

    /*---- Connection Information ---*/
    
    /// <summary>
    /// Returns a list objects connected to an exposed connection.
    /// </summary>
    ///
    /// <param name="thisConnection">
    /// The name of the connection on this object.
    /// </param>
    /// <param name="connectedObjects">
    /// An array of AcDbEvalNodeIds of objects connected to the exposed
    /// connection.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if the connection is allowed. Returns
    /// Acad::eKeyNotFound if the object does not expose the named connection. 
    /// </returns>
    ///
    virtual Acad::ErrorStatus getConnectedObjects ( 
                                const AcString&      thisConnection,
                                AcDbEvalNodeIdArray& connectedObjects) const;
    
    /// <summary>
    /// Returns a list connection names shared between a named connection on this 
    /// object and another connected object. 
    /// </summary>
    ///
    /// <param name="thisConnection">
    /// The name of the connection on this object.
    /// </param>
    /// <param name="sourceConnectableId">
    /// The AcDbEvalNodeId of the other connected object.
    /// </param>
    /// <param name="sourceConnectionNames">
    /// An array of AcStrings identifying the connections on <paramref
    /// name="sourceConnectableId"/> connected to <paramref
    /// name="thisConnection"/>. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if the connection is allowed. Returns
    /// Acad::eKeyNotFound if the object does not expose the named connection. 
    /// </returns>
    ///
    virtual Acad::ErrorStatus getConnectedNames (
                                const AcString&      thisConnection,
                                const AcDbEvalNodeId sourceConnectableId,
                                AcStringArray&       sourceConnectionNames) const;
protected:
    /// <summary>
    /// Default constructor.
    /// </summary>
    ///
    AcDbEvalConnectable();
};


////////////////////////////////////////////////////////////////////////
// class AcDbEvalContext 
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class implements a simple container for application data that can be
/// used during the evaluation of an AcDbEvalGraph. The graph passes any
/// AcDbEvalContext object supplied in a call to
/// <c>AcDbEvalGraph::evaluate()</c> to each node in the graph when calling
/// <c>AcDbEvalExpr::evaluate()</c> during the ensuing traversal. Graph client
/// applications typically use the context to store application-specific data
/// used by custom nodes during their evaluation. 
/// </summary>
///
/// 
class AcDbEvalContext : public AcRxObject, public AcHeapOperators
{
public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    /// 
    AcDbEvalContext();

    /// <summary>
    /// Destructor.
    /// </summary>
    ///
    virtual ~AcDbEvalContext();

    ACRX_DECLARE_MEMBERS(AcDbEvalContext);

    /* Collection access methods */

    /// <summary>
    /// Inserts an AcDbEvalContextPair into the context. 
    /// </summary>
    /// 
    /// <param name="pair">
    /// The AcDbEvalContextPair to insert into the context.
    /// </param>
    ///
    /// <remarks>
    /// If an AcDbEvalContextPair with the specified key already exists it is
    /// replaced with the new pair.
    /// </remarks>
    virtual void        insertAt (const AcDbEvalContextPair& pair);

    /// <summary>
    /// Removes an AcDbEvalContextPair from the context. 
    /// </summary>
    /// 
    /// <param name="szKey">
    /// The key of the AcDbEvalContextPair to remove from the context.
    /// </param>
    ///
    virtual void        removeAt (const ACHAR*                szKey);
    
    /// <summary>
    /// Returns an AcDbEvalContextPair stored in the context. 
    /// </summary>
    /// 
    /// <param name="pair">
    /// The AcDbEvalContextPair to insert into the context.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eKeyNotFound if no entry
    /// exists with the specified key.
    /// </returns>
    ///
    /// <remarks>
    /// The <paramref name="pair"/> passed in should be initialized with the
    /// desired key to return in the context. If the key exists <paramref
    /// name="pair"/> is updated with the value from the context. 
    /// </remarks>
    ///
    virtual Acad::ErrorStatus getAt (AcDbEvalContextPair& pair) const;

    /// <summary>
    /// Returns a new AcDbEvalContextIterator for the context.
    /// </summary>
    ///
    /// <returns>
    /// A new AcDbEvalContextIterator. Callers must delete the iterator when it
    /// is no longer needed by calling <c>delete</c>.
    /// </returns>
    ///
    virtual AcDbEvalContextIterator* newIterator() const;         
    
private:
    AcDbImpEvalContext* mpImp;
    friend class AcDbImpEvalContextIterator;
};


////////////////////////////////////////////////////////////////////////
// class AcDbEvalContextPair
////////////////////////////////////////////////////////////////////////// 

/// <summary>
/// The AcDbEvalContextPair class represents a single entry in an
/// AcDbEvalContext container. 
/// </summary>
///
/// <remarks>
/// This is a simple key-value pair stored in an AcDbEvalContext. The values
/// are void pointers. Neither this class nor the AcDbEvalContext class are
/// responsible for managing the memory allocated to the values stored in the
/// context. 
/// </remarks>
///
class AcDbEvalContextPair : public AcHeapOperators 
{
public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    /// 
    AcDbEvalContextPair();

    /// <summary>
    /// Constructor.
    /// </summary>
    ///
    /// <param name="szKey">
    /// The key used to lookup the pair in an AcDbEvalContext.
    /// </param>
    /// <param name="pValue">
    /// A pointer to the data stored in the context pair. 
    /// </param>
    ///
    AcDbEvalContextPair(const ACHAR* szKey, void *pValue);

    /// <summary>
    /// Destructor.
    /// </summary>
    ///
    virtual ~AcDbEvalContextPair();
    
    /// <summary>
    /// Sets the key used to lookup the pair in an AcDbEvalContext.
    /// </summary>
    ///
    /// <param name="szKey">
    /// The key used to lookup the pair in an AcDbEvalContext.
    /// </param>
    /// 
    void        setKey   (const ACHAR* szKey);

    /// <summary>
    /// Gets the key used to lookup the pair in an AcDbEvalContext.
    /// </summary>
    ///
    /// <returns>
    /// The key used to lookup the pair in an AcDbEvalContext.
    /// </returns>
    /// 
    const ACHAR* key      () const;

    /// <summary>
    /// Sets the values stored with the pair in an AcDbEvalContext.
    /// </summary>
    ///
    /// <param name="pValue">
    /// The value to store in the AcDbEvalContextPair.
    /// </param>
    ///
    /// <remarks>
    /// The memory pointed to by <paramref name="pValue"/> must be allocated and
    /// freed by the caller. 
    /// </remarks>
    void        setValue (void* pValue);

    /// <summary>
    /// Gets the values stored with the pair in an AcDbEvalContext.
    /// </summary>
    ///
    /// <returns>
    /// The value stored in the AcDbEvalContextPair.
    /// </returns>
    ///
    void*       value    () const;

private:
    ACHAR* mKey;
    void* mValue;
};


////////////////////////////////////////////////////////////////////////
// class AcDbEvalContextIterator
////////////////////////////////////////////////////////////////////////

/// <summary>
/// Provides access to the contents of an AcDbEvalContext collection.
/// </summary>
///
/// <remarks>
/// AcDbEvalContextIterator instances are returned by calls to AcDbEvalContext::newIterator().
/// </remarks>
///
class AcDbEvalContextIterator : public AcRxObject, public AcHeapOperators
{
public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    ///
    AcDbEvalContextIterator();

    /// <summary>
    /// Destructor.
    /// </summary>
    ///
    virtual ~AcDbEvalContextIterator();

    ACRX_DECLARE_MEMBERS(AcDbEvalContextIterator);
    
    /// <summary>
    /// Initializes the iterator to the start of the collection.
    /// </summary>
    ///
    virtual void   start();

    /// <summary>
    /// Advances the iterator to the next object in the collection.
    /// </summary>
    ///
    /// <returns>
    /// Returns true when the iterator has reached the end of the collection.
    /// </returns>
    ///
    virtual bool   next();

    /// <summary>
    /// Determines whether the iterator has reached the end of the collection.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if the iterator has reached the end of the collection.
    /// </returns>
    /// 
    virtual bool   done() const;
    
    /// <summary>
    /// Returns the AcDbEvalContextPair at the current iterator position.
    /// </summary>
    ///
    /// <returns>
    /// The AcDbEvalContextPair at the current iterator position.
    /// </returns>
    virtual AcDbEvalContextPair contextPair() const;
    
private:
    AcDbEvalContextIterator(AcDbEvalContext* pContext);
    AcDbImpEvalContextIterator* mpImp;
    friend class AcDbImpEvalContext;
};

#pragma pack(pop)

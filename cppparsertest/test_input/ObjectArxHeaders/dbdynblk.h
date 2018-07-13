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
// dbdynblk.h
//
// DESCRIPTION: 
// Utility classes for dynamic blocks, allows manipulation of dynamic
// block references, discovering dynamic block properties, and updating
// dynamic block definitions.
//
// AcDbDynBlockReference
// AcDbDynBlockReferenceProperty
// AcDbDynBlockTableRecord
//
#pragma once

#include "dbeval.h"
#include "acstring.h"

#pragma pack (push, 8)

// Forward class declarations

class AcDbDynBlockReference;
class AcDbDynBlockReferenceProperty;
class AcDbImpDynBlockReference;
class AcDbImpDynBlockReferenceProperty;
class AcDbImpDynBlockTableRecord;

/// <summary>
/// A utility class describing a property on a dynamic block, including getting
/// and setting the current value on the dynamic block. The
/// AcDbDynBlockReferenceProperty class is a reference to a property defined on
/// a dynamic block instance, and can be used to get and set the current value
/// on that instance.
/// </summary>
///
class AcDbDynBlockReferenceProperty : public AcHeapOperators
{
public:

    /// <summary>
    /// Describes the units (if any) of the property. Clients may use this
    /// information to format the property in their user interface. 
    /// </summary>
    enum UnitsType {

        /// <summary>
        /// No units defined.
        /// </summary>
        kNoUnits = 0,

        /// <summary>
        /// Property represents and angle between two vectors.
        /// </summary>
        kAngular,

        /// <summary>
        /// Property represents a distance between two points.
        /// </summary>
        kDistance,

        /// <summary>
        /// Property represents a two-dimensional area.
        /// </summary>
        kArea
    };

    /// <summary>
    /// Default constructor.
    /// </summary>
    AcDbDynBlockReferenceProperty ();

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~AcDbDynBlockReferenceProperty ();

    /// <summary>
    /// Copy constructor.
    /// </summary>
    ///
    /// <param name="other">
    /// The dynamic block property to construct a copy of.
    /// </param>
    AcDbDynBlockReferenceProperty (const AcDbDynBlockReferenceProperty& other);
    
    /// <summary>
    /// Assignment operator.
    /// </summary>
    ///
    /// <param name="other">
    /// The dynamic block property to assign this property to.
    /// </param>
    ///
    /// <remarks>
    /// The assignment operator causes the dynamic property object to reference
    /// the same property as that it is being assigned to, that is a named
    /// property on a dynamic block instance. The actual property value is not
    /// changed. 
    /// </remarks>
    AcDbDynBlockReferenceProperty& operator=(
            const AcDbDynBlockReferenceProperty& other);

    /// <summary>
    /// The AcDbObjectId of the dynamic block reference containing the property.
    /// </summary>
    ///
    /// <returns>
    /// Returns the AcDbObjectId of the dynamic block reference containing the
    /// property represented by the AcDbDynBlockReferenceProperty.
    /// </returns>
    AcDbObjectId          blockId() const;
    
    /// <summary>
    /// The property name.
    /// </summary>
    ///
    /// <returns>
    /// The name of the property as an AcString.
    /// </returns>
    ///
    /// <remarks>
    /// Property names are guaranteed to be unique amongst all properties on a
    /// given block reference. 
    /// </remarks>
    AcString              propertyName ()   const;

    /// <summary>
    /// The property type.
    /// </summary>
    ///
    /// <returns>
    /// The value type of the property.
    /// </returns>
    AcDb::DwgDataType propertyType ()  const;

    /// <summary>
    /// Whether the property is read-only.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if the property value can be changed by calls to
    /// <c>setValue()</c>.
    /// </returns>
    bool                  readOnly ()       const;

    /// <summary>
    /// Whether the property is displayed by Property Palette when the block
    /// reference containing the property is selected.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if the property is displayed by Property Palette when the
    /// block reference containing the property is selected. 
    /// </returns>
    bool                  show ()           const;

    /// <summary>
    /// Whether the property is visible in the current visibility state.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if the property is visible in the current visibility state. 
    /// </returns>
    bool ACDB_PORT        visibleInCurrentVisibilityState ()       const;


    /// <summary>
    /// The property description.
    /// </summary>
    ///
    /// <returns>
    /// An property description as an AcString object.
    /// </returns>
    AcString              description ()    const;

    /// <summary>
    /// The units of the property.
    /// </summary>
    ///
    /// <returns>
    /// The units of the property in the form of a UnitsType enumeration.
    /// </returns>
    ///
    /// <remarks>
    /// Clients may use this information to format the property consistently in
    /// their user interface.
    /// </remarks>
    UnitsType             unitsType () const;

    /// <summary>
    /// Returns the allowed values for the property.
    /// </summary>
    /// 
    /// <param name="values">
    /// An AcDbEvalVariantArray that upon a successful return is populated with
    /// the allowed property values. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// Not all dynamic block properties have a restricted set of property
    /// values. Some properties are unrestricted, some a mimimum or maximum
    /// value (or both), and some have a list of allowed values. This function
    /// only returns a non-empty <paramref name="values"/> array when the
    /// allowed property values are defined by a list. Mimimum, maximum, and
    /// unrestricted property types are not supported by this method.
    /// </remarks>
    Acad::ErrorStatus     getAllowedValues(AcDbEvalVariantArray& values);
 
    /// <summary>
    /// The current value of the property on the block.
    /// </summary>
    ///
    /// <returns>
    /// Returns the current value of the property as an AcDbEvalVariant.
    /// </returns>
    AcDbEvalVariant       value () const;

    /// <summary>
    /// Sets the current value of the property on the block.
    /// </summary>
    ///
    /// <param name="value">
    /// The new value to assign to the parameter.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if the parameter exists and the block can be modified. 
    /// </returns>
    ///
    /// <remarks>
    /// Note that there is no error returned if the specified property value
    /// could not be set, for example if the property has a list of allowable
    /// values or a minimum-maximum range and the value provided is not in the
    /// list or is out of range. In this case the method succeeds but no error
    /// is returned. 
    /// </remarks>
    Acad::ErrorStatus     setValue (const AcDbEvalVariant& value);

    /// <summary>
    /// Compare whether these two properties belongs to the same block reference
    /// </summary>
    bool operator==(const AcDbDynBlockReferenceProperty& other);

   
private:
    
    AcDbImpDynBlockReferenceProperty* mpImp;
    friend class AcDbImpDynBlockReferenceProperty;
    friend class AcDbImpDynBlockReference;
};

typedef AcArray<AcDbDynBlockReferenceProperty, 
        AcArrayObjectCopyReallocator<AcDbDynBlockReferenceProperty> > 
             AcDbDynBlockReferencePropertyArray;

/// <summary>
/// A utility class for accessing information about block references to dynamic
/// blocks.
/// </summary>
///
class AcDbDynBlockReference : public AcHeapOperators
{
public:
   
    /// <summary>
    /// Constructor.
    /// </summary>
    ///
    /// <param name="blockRefId">
    /// The AcDbObjectId of the AcDbBlockReference to get dynamic block
    /// information from.
    /// </param>
    AcDbDynBlockReference(AcDbObjectId blockRefId);

    /// <summary>
    /// Constructor.
    /// </summary>
    ///
    /// <param name="blockRef">
    /// A pointer to the AcDbBlockReference to get dynamic block
    /// information from.
    /// </param>
    ///
    /// <remarks>
    /// For internal use only.
    /// </remarks>
    AcDbDynBlockReference(AcDbBlockReference* pRef);

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~AcDbDynBlockReference ();

    /// <summary>
    /// Static method for determining whether an AcDbBlockTableRecord contains
    /// dynamic block information.
    /// </summary>
    ///
    /// <param name="blockTableRecordId">
    /// The AcDbObjectId of an AcDbBlockTableRecord.
    /// </param>
    ///
    /// <returns>
    /// Returns true if <paramref name="blockTableRecordId"/> is an
    /// AcDbBlockTableRecord and contains dynamic block information.
    /// </returns>
    static bool       isDynamicBlock (AcDbObjectId blockTableRecordId);

    /// <summary>
    /// Determines whether the AcDbBlockReference passed to the class
    /// constructor contains dynamic block information.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if the AcDbBlockReference passed to the class constructor
    /// contains dynamic block information. 
    /// </returns>
    bool              isDynamicBlock () const;

    /// <summary> 
    /// The AcDbObjectId of the block reference.
    /// </summary>
    ///
    /// <returns>
    /// Returns the AcDbObjectId of the block reference.
    /// </returns>
    AcDbObjectId blockId() const;

    /// <summary>
    /// Returns a collection of AcDbDynBlockReferenceProperty instances
    /// referencing dynamic block properties on the AcDbBlockReference.
    /// </summary>
    ///
    /// <param name="properties">
    /// Returned collection of AcDbDynBlockReferenceProperty instances.
    /// </param>
    ///
    /// <remarks>
    /// If the AcDbBlockReference contains no dynamic property information the
    /// returned array is empty.
    /// </remarks>
    void              getBlockProperties (
                        AcDbDynBlockReferencePropertyArray& properties) const;

    /// <summary>
    /// Resets the AcDbBlockReference to the default state of the dynamic
    /// block.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// All properties on the AcDbBlockReference are set to match the values in
    /// the block definition.  
    /// </remarks>
    Acad::ErrorStatus resetBlock ();

    /// <summary>
    /// Converts the dynamic block instance to a legacy (non-dynamic) 
    /// anonymous block.
    /// </summary>
    /// 
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// When successful the block reference "freezes" the dynamic block
    /// properties at their current values and ceases to become a dynamic
    /// block. It becomes an anonymous block for all purposes.
    /// </remarks>
    Acad::ErrorStatus convertToStaticBlock ();

    /// <summary>
    /// Converts the dynamic block instance to a legacy (non-dynamic) block.
    /// </summary>
    ///
    /// <param name="newBlockName">
    /// The name of the new block definition.
    /// </param>
    /// 
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// When successful the block the dynamic block properties are "frozen" at
    /// their current values and the reference ceases to become a dynamic
    /// block. A new block is defined with the name 
    /// <paramref  name="newBlockName"/>, which must not already exist in the 
    /// drawing and must satisfy all of the naming restrictions of normal block
    /// references.
    /// </remarks>
    Acad::ErrorStatus convertToStaticBlock (const AcString& newBlockName);

    /// <summary>
    /// The dynamic block definition.
    /// </summary>
    ///
    /// <returns>
    /// Returns the AcDbObjectId of the dynamic block definition (an
    /// AcDbBlockTableRecord) if the block reference is a dynamic block,
    /// otherwise it returns AcDbObjectId::kNull.
    /// </returns>
    AcDbObjectId      dynamicBlockTableRecord () const;

    /// <summary>
    /// The anonymous block definition used to draw the dynamic block.
    /// </summary>
    ///
    /// <returns>
    /// Returns the AcDbObjectId of the anonymous block definition (an
    /// AcDbBlockTableRecord) used to draw the block reference. Returns
    /// AcDbObjectId::kNull if the block reference is not a dynamic block or is
    /// not currently using an anonymous block to draw itself.
    /// </returns>
    ///
    /// <remarks>
    /// Dynamic blocks whose properties differ from that of the dynamic block
    /// definition may use an anonymous block to draw themselves. This
    /// anonymous block may be shared between multiple block references and
    /// should not be modified by client applications directly. 
    /// </remarks>
    ///
    AcDbObjectId      anonymousBlockTableRecord () const; 
    
private:
    AcDbDynBlockReference();
    
    AcDbImpDynBlockReference* mpImp;
};

/// <summary>
/// A utility class for accessing information about dynamic block definitions
/// and managing the associated anonymous blocks.  
/// </summary>
///
class AcDbDynBlockTableRecord : public AcHeapOperators
{
public:
   
    /// <summary>
    /// Constructor.
    /// </summary>
    ///
    /// <param name="blockTableRecordId">
    /// The AcDbObjectId of the AcDbBlockTableRecord to get dynamic block
    /// information from.
    /// </param>
    ACDB_PORT AcDbDynBlockTableRecord(AcDbObjectId blockTableRecordId);

    /// <summary>
    /// Destructor.
    /// </summary>
    ACDB_PORT virtual ~AcDbDynBlockTableRecord();

    /// <summary>
    /// Determines whether the AcDbBlockTableRecord passed to the class
    /// constructor contains dynamic block information.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if the AcDbBlockTableRecord passed to the class constructor
    /// contains dynamic block information. 
    /// </returns>
    ACDB_PORT bool isDynamicBlock () const;

    /// <summary> 
    /// The AcDbObjectId of the block table record.
    /// </summary>
    ///
    /// <returns>
    /// Returns the AcDbObjectId of the block table record. 
    /// </returns>
    ACDB_PORT AcDbObjectId blockTableRecordId() const;

    /// <summary> 
    /// Obtains the list of anonymous blocks created from the dynamic block
    /// definition.
    /// </summary>
    ///
    /// <param name="anonymousIds">
    /// Array populated with the AcDbObjectIds of the anonymous blocks created
    /// from the dynamic block definition. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// AutoCAD creates and manages anonymous blocks by deep cloning the
    /// contents of a dynamic block definition when a reference to the
    /// definition needs a modified copy of the block geometry. 
    /// </remarks>
    ACDB_PORT Acad::ErrorStatus getAnonymousBlockIds 
                                (AcDbObjectIdArray& anonymousIds) const;
    
    /// <summary>
    /// Updates the anonymous blocks created from this dynamic block definition
    /// to reflect any changes made to the dynamic block definition. 
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// Calling this method after updating a dynamic block definition causes
    /// AutoCAD to replace all anonymous block definitions created from this
    /// definition with new anonymous block definitions, thereby causing all
    /// references to reflect changes made to the dynamic block. The update
    /// preserves the values of dynamic block properties on the references
    /// where possible, adding newly created properties and deleting properties
    /// that no longer exist. When complete all references to the dynamic block
    /// reflect the new state of the block definition. 
    /// </remarks>
    ACDB_PORT Acad::ErrorStatus updateAnonymousBlocks() const;

private:
    AcDbDynBlockTableRecord();
    
    AcDbImpDynBlockTableRecord* mpImp;
};
#pragma pack (pop)


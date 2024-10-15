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
// CREATED BY: Jiri Kripac                                 October 2007
//
// DESCRIPTION:
//
// AcDbAssocDimDependencyBodyBase class. 
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocGlobal.h"
#include "AcString.h"
#include "AcArray.h"
#include "AcConstrainedGeometry.h"
#include "AcDbAssocDependencyBody.h"
#pragma pack (push, 8)


/// <summary> <para>
/// AcDbAssocDimDependencyBodyBase ties together the following objects that 
/// define a dimensional constraint:
///
/// AcDbAssocVariable                  Keeps dimensional constraint name and expression.
/// AcDbAssoc2dConstraintGroup         Keeps AcExplicitConstraint.
/// AcDbEntity (such as AcDbDimension) Graphical representation of the dimensional constraint.
///
/// AcDbAssocDimDependencyBodyBase class represents a dependency of an AcExplicitConstraint
/// owned by an AcDbAssoc2dConstraintGroup, on an AcDbEntity that is the graphical 
/// representation of the dimensional constraint. AcDbAssocDimDependencyBodyBase
/// is an abstract base class, there are concrete derived classes (such as 
/// AcDbAssocDimDependencyBody) that deal with concrete entity types (such as AcDbDimension)
/// that are used as graphical representations of dimensional constraints.
/// </para> <para>
/// The AcDbAssocDimDependencyBodyBase does all the work of managing the graphical 
/// entity, receiving notifications about entity text changes, updating the entity 
/// text and entity positioning, keeping the entity text in sync with the 
/// AcDbAssocVariable, and keeping it in sync with the corresponding 
/// AcExplicitConstraint in AcDbAssoc2dConstraintGroup.
/// </para> <para>
/// There always is a corresponding AcDbAssocVariable that keeps the name, expression
/// and value of the dimensional constraint and is also referenced by the 
/// AcExplicitConstraint via AcDbAssocValueDependency. The AcDbAssocDimDependencyBodyBase 
/// obtains the corresponding AcDbAssocVariable by going up to the 
/// AcDbAssoc2dConstraintGroup that owns the AcDbAssocDimDependencyBody, finds
/// the AcExplicitConstraint that references this dependency, obtains the 
/// AcDbAssocValueDependency and obtains the object it depends on, which is the 
/// corresponding AcDbAssocVariable.
/// </para> </summary>
///
class ACDB_PORT AcDbAssocDimDependencyBodyBase : public AcDbAssocDependencyBody
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocDimDependencyBodyBase);

    /// <summary> Default constructor. </summary>
    explicit AcDbAssocDimDependencyBodyBase(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> Destructor. </summary>
    virtual ~AcDbAssocDimDependencyBodyBase();

    /// <summary> 
    /// Derived classes needs to override this pure virtual method. This is how 
    /// they provide the text of the entity they manage.
    /// </summary>
    /// <returns> The entity text. </returns>
    ///
    virtual AcString getEntityTextOverride() const = 0;

    /// <summary> 
    /// Derived classes need to override this pure virtual method to set the 
    /// text of the entity they manage. 
    /// </summary>
    /// <param  name="newText"> New text to set to the entity. </param>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    virtual Acad::ErrorStatus setEntityTextOverride(const AcString& newText) = 0;

    /// <summary> 
    /// Derived classes needs to override this pure virtual method to provide the
    /// current measurement of the entity they manage. 
    /// </summary>
    /// <returns> The entity measurement. </returns>
    ///
    virtual double getEntityMeasurementOverride() const = 0;

    /// <summary> 
    /// Derived classes need to override this pure virtual method to inform 
    /// whether the attachment of the entity they manage changed, such as whether 
    /// the entity has been repositioned.
    /// </summary>
    /// <returns> True if the entity attachment changed, false otherwise. </returns>
    ///
    virtual bool isEntityAttachmentChangedOverride() const = 0;

    /// <summary> This method needs to be overriden and implemented by derived 
    /// classes. It updates the controlled entity position, size and orientation. 
    /// The base class impplementation just handles reference dimensions that are 
    /// not dimensional constraints. This method updates the corresponding
    /// AcDbAssocVariable with the current measured value of the dimension and
    /// updates the entity text with the current measurement. </summary>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    virtual Acad::ErrorStatus updateDependentOnObjectOverride() override;

    /// <summary> Returns the corresponding dimensional constraint node. </summary>
    /// <returns> The dimensional constraint node. </returns>
    ///
    class AcExplicitConstraint* constraint() const;

    /// <summary> Returns object id of the corresponding AcDbAssocVariable. </summary>
    /// <returns> Object id of the AcDbAssocVariable. </returns>
    ///
    AcDbObjectId variable() const; // of AcDbAssocVariable

    /// <summary> Returns all AcConstrainedGeometries constrained by this 
    /// dimensional constraint. </summary>
    /// <param  name="geoms"> All AcConstrainedGeometries constrained by this 
    /// dimensional constraint. </param>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    Acad::ErrorStatus getConstrainedGeoms(AcArray<AcConstrainedGeometry*>& geoms) const;

    /// <summary> Returns all constrained subentities of AcDbEntities constrained 
    /// by this dimensional constraint. </summary>
    /// <param  name="geoms"> All constrained subentities of AcDbEntities 
    /// constrained by this dimensional constraint. </param>
    /// <returns> Returns Acad::eOk if successful. </returns>
    ///
    Acad::ErrorStatus getConstrainedGeoms(AcArray<AcDbFullSubentPath>& geoms) const;

    /// <summary> Returns all constrained subentities of AcDbEntities constrained 
    /// by this dimensional constraint. </summary>
    /// <param  name="geoms"> All constrained subentities of AcDbEntities 
    /// constrained by this dimensional constraint. </param>
    /// <param  name="distanceDirection"> Direction of the distance constraint. </param>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    Acad::ErrorStatus getConstrainedGeoms(AcArray<AcDbSubentGeometry>& geoms,
                                          AcGeVector3d&                distanceDirection) const;

    /// <summary> Returns name, expression and current value of the AcDbAssocVariable 
    /// that corresponds to this dimensional constraint. </summary>
    /// <param  name="name"> Variable name. </param>
    /// <param  name="expression"> Variable expression. </param>
    /// <param  name="value"> Variable value. </param>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    Acad::ErrorStatus getVariableNameAndExpression(AcString& name, AcString& expression, AcString& value) const;

    /// <summary> Returns name and expression from the text that the managed 
    /// entity is displaying. </summary>
    /// <param  name="name"> Name from the managed entity display text. </param>
    /// <param  name="expression"> Expression from the managed entity display text. </param>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    Acad::ErrorStatus getEntityNameAndExpression(AcString& name, AcString& expression) const;

    /// <summary> Sets new name and expression of the AcDbAssocVariable that
    /// corresponds to this dimensional constraint. Either name or expression 
    /// may be empty strings which indicates not to change them. </summary>
    /// <param  name="name"> New name of the AcDbAssocVariable. </param>
    /// <param  name="expression"> New expression of the AcDbAssocVariable. </param> 
    /// <returns> Acad::eOk if successful. </returns>
    ///
    Acad::ErrorStatus setVariableNameAndExpression(const AcString& name, const AcString& expression);

    /// <summary> Sets name and expression that the managed entity should display. 
    /// Either name or expression may be empty strings which indicates not 
    /// to change them. </summary>
    /// <param  name="name"> New name the managed entity should display. </param>
    /// <param  name="expression"> New expression the managed entity should display. </param>
    /// <param  name="value"> New value the managed entity should display. </param>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    Acad::ErrorStatus setEntityNameAndExpression(const AcString& name, const AcString& expression, const AcString& value);

    /// <summary> Sets name and expression on both the AcDbAssocVariable that
    /// corresponds to this dimensional constraint and on the managed entity 
    /// that serves as graphical representation of this dimensional constraint.
    /// Either name or expression may be empty strings which indicates not to 
    /// change them. </summary>
    /// <param  name="name"> New name to be set. </param>
    /// <param  name="expression"> New expression to be set. </param>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    Acad::ErrorStatus setNameAndExpression(const AcString& name, const AcString& expression); // Both variable and entity

    /// <summary> Checks if the given entityTextToValidate can be used as the 
    /// text the managed entity displays. Either the name or the expression part 
    /// of the entityTextToValidate text may be empty which means that the
    /// current name/expression should be used. </summary>
    /// <param  name="entityTextToValidate"> The entity text to check. </param>
    /// <param  name="errorMessage"> The error message if any errors. </param>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    Acad::ErrorStatus validateEntityText(const AcString& entityTextToValidate, 
                                         AcString&       errorMessage) const;

    /// <summary> 
    /// If needed, opens itself for write and updates the text in the managed entity. 
    /// If no changes are needed, does nothing. Notice that this AcDbAssocDimDependencyBodyBase
    /// may be open just for read when this method is called. This is to avoid the overhead
    /// with opening the object for write in case it does not need to be modified.
    /// </summary>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    Acad::ErrorStatus updateEntityText();

    /// <summary> Composes the text that the managed entity should display. The
    /// text is composed from the corresponding AcDbAssocVariable name, expression 
    /// and/or value. The text formatting follows requiredNameFormat. </summary>
    /// <param  name="requiredNameFormat"> 
    /// The constraint name format display, deafault value if -1. 
    /// If requiredNameFormat == -1, CONSTRAINTNAMEFORMAT sysvar is used for 
    /// choosing the text format. </param>
    /// <returns> The composed entity text. </returns>
    ///
    AcString composeEntityText(int requiredNameFormat = -1) const;

    /// <summary> Measures the current dimensional constraint based on
    /// the current positions and sizes of the constrained geometries and sets 
    /// the corresponding AcDbAssocVariable to this measured value. If the 
    /// dimensional constraint is satisfied, the AcDbAssocVariable value will 
    /// already be equal to the measured value and no setting is needed and it 
    /// does not happen. Notice that if AcDbAssocVariable contained an expression, 
    /// it will be erased and the variable will just contain a numerical value, 
    /// not expression. </summary>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    Acad::ErrorStatus setVariableValueToMeasuredValue() const;

    /// <summary> Deactivates the constraint. Deactivating a constraint means 
    /// still keeping the AcExplicitConstraint in the AcDbAssoc2dConstraintGroup 
    /// but removing its d_node or r_node from the DCM dimension system. </summary>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    Acad::ErrorStatus deactivateConstraint() const;

    /// <summary> Reactivates the constraint. Reactivating a constraint means 
    /// creating a d_node or r_node for this AcExplicitConstraint and adding it 
    /// to the DCM dimension system. </summary>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    Acad::ErrorStatus reactivateConstraint() const;

    /// <summary> Returns whether the constraint is active. </summary>
    /// <returns> True if the constraint is active, false otherwise. </returns>
    ///
    bool isConstraintActive() const; // Has DCM d_node or r_node

    /// <summary> Measures the current dimensional constraint based on the
    /// current positions and sizes of the constrained geometries. If the 
    /// dimensional constraint is satisfied, the AcDbAssocVariable value will 
    /// already be equal to the measured value. </summary>
    /// <param  name="measurement"> The returned measured value. </param>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    Acad::ErrorStatus getMeasuredValue(double& measurement) const;

    /// <summary> Sets whether the constraint is reference only. 
    /// A reference "constraint" keeps updating its AcDbAssocVariable and the 
    /// dimension text with the measured value of the dimension, but it does 
    /// not function as a dimensional constraint. </summary>
    /// <param  name="yesNo"> 
    /// Bool value indicating whether the constraint is reference only. </param>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    Acad::ErrorStatus setIsReferenceOnly(bool yesNo);

    /// <summary> Parses the given entityText string and extracts name and 
    /// expression components from it. It is mainly for internal use. </summary>
    /// <param  name="entityText"> The string to extract name and expression from. </param>
    /// <param  name="useMeasurementIfNoText"> 
    /// Indicates whether to use measurement value if no text is given. </param>
    /// <param  name="measurement"> The provided entity measurement. </param>
    /// <param  name="isAngular"> Indicates that the constraint is angular. </param>
    /// <param  name="name"> Name component extracted from entityText. </param>
    /// <param  name="expression"> Expression component extracted from entityText. </param>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    static Acad::ErrorStatus 
    getNameAndExpressionFromEntityText(const AcString& entityText,
                                       bool            useMeasurementIfNoText,
                                       double          measurement,
                                       bool            isAngular,
                                       AcString&       name, 
                                       AcString&       expression);

    /// <summary> Returns the format that is used to display the entity name 
    /// and expression by looking at the currently displayed entity text. 
    /// See CONSTRAINTNAMEFORMAT sysvar for the possible format values. </summary>
    /// <returns> The currently used constraint display format. </returns>
    ///
    int getCurrentlyUsedEntityNameFormat() const;

    /// <summary>
    /// This function should be called when dependent object grips are dragged.
    /// </summary> 
    /// <param  name="status"> The current AcDb::DragStat. </param>
    ///
    void dragStatus(const AcDb::DragStat status);

    /// <summary> Gets the AcDbAssocDimDependencyBodyBase from the dependent-on 
    /// AcDbEntity, such as from the AcDbDimension it controls. If the entity
    /// does not have an AcDbAssocDimDependencyBodyBase attached, AcDbObjectId::kNull
    /// is returned. </summary>
    /// <param  name="entityId"> The entity id of the dependent-on AcDbEntity, 
    /// such as of an AcDbDimension. </param>
    /// <param  name="dimDepBodyId"> The returned AcDbObjectId of the 
    /// AcDbAssocDimDependencyBodyBase, or AcDbObjectId::kNull if none found. </param>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    static Acad::ErrorStatus getFromEntity(const AcDbObjectId& entityId, AcDbObjectId& dimDepBodyId);

    /// <summary> <para> Updates the constraint geometry when dimension grip 
    /// points are moved. Any move made through triangular grip should move the
    /// constraint geometry by the same amount and update the constraint variable 
    /// value. Clients of this function need to pass new positions of the dimension 
    /// attachment in AcDbSubentGeometry array, and new dimension measurement. 
    /// </para> <para>
    /// This API performs the following operations:
    /// </para> <para> 
    /// 1. Moves the constraint geometry sub entity by the same 
    /// amount the dimension grip point has been moved.
    /// </para> <para> 
    /// 2. Moves the constrained geometry at the opposite end of 
    /// the dimensional constraint by identity transform. This is a hint to DCM 
    /// not to move the opposite end of the dimensional constraint.
    /// </para> <para> 
    /// 3. Updates the constraint variable value with new measurement.
    /// </para> </summary>
    /// <param  name="newAttachedGeometries"> 
    /// The new attached geometries to be updated. </param>
    /// <param  name="measurement"> New measurement, default value is 0.0. </param>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    Acad::ErrorStatus entityAttachmentPointMoved(const AcArray<AcDbSubentGeometry>& newAttachedGeometries,
                                                 double measurement = 0.0);

    /// <summary> Overridden method from AcDbAssocDependencyBody base class. </summary>
    /// <param  name="isRelevChange"> 
    /// Returns true if one of the following has happened:
    /// <para> Entity text changed in any way, </para>
    /// <para> Name or expression of the corresponding AcDbAssocVariable are 
    /// different from name or expression in the controlled entity, </para>
    /// <para> Entity attachment changed. </para>
    /// </param>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    virtual Acad::ErrorStatus isRelevantChangeOverride(bool& isRelevChange) const override;

    /// <summary> This function sets the name and expression in the controlled 
    /// entity text to be the same as the name and expression of the corresponding 
    /// AcDbAssocVariable. </summary>
    ///
    virtual void evaluateOverride() override;

    /// <summary> If the controlled entity text changed, this function sets the 
    /// name and expression of the AcDbAssocVariable to be the same as the name 
    /// and expression in the entity text. </summary>
    /// <param name="pDbObj"> The controlled entity. </param>
    ///
    virtual void modifiedOverride(const AcDbObject* pDbObj) override;

    /// <summary> When the dependent-on object (such as an AcDbDimension) is 
    /// erased, the corresponding AcDbAssocVariable is also erased.</summary>
    /// <param name="pDbObj"> The controlled entity. </param>
    /// <param name="isErasing"> Boolean isErasing. </param>
    ///
    virtual void erasedOverride(const AcDbObject* pDbObj, Adesk::Boolean isErasing) override;

    /// <summary> Overridden method from the AcDbObject base class.
    /// It erases the controlled entity, such as the AcDbDimension. </summary>
    /// <param  name="erasing"> Boolean erasing. </param>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    virtual Acad::ErrorStatus subErase(Adesk::Boolean erasing) override;

    /// <summary> Formats the given expression to current precision. </summary>
    /// <param  name="expression"> The expression to be formatted. </param>
    /// <param  name="isAngular"> Indicates it is an angular constraint. </param>
    /// <returns> The formatted expression. </returns>
    ///
    static AcString formatToCurrentPrecision(const AcString& expression, bool isAngular);

    /// <summary> Under normal circumstances the controlled AcDbDimension object 
    /// is erased if the AcDbAssocDimDependencyBodyBase is erased. This static 
    /// method allows to control if this behavior is to be surpressed, i.e. 
    /// not erasing the AcDbDimension if the AcDbAssocDimDependencyBodyBase is 
    /// erased. This can be useful for the creation of reference constraints 
    /// since the same dimension should be retained and used for a reference 
    /// constraint later on. </summary>
    /// <param  name="yesNo"> Indicates to surpress the erase behavior or not. </param>
    /// <returns> Returns whether the behavior is surpressed or not. </returns>
    ///
    static bool setEraseDimensionIfDependencyIsErased(bool yesNo);

    /// <summary> Under normal circumstances an associated AcDbDimension object 
    /// is erased if the AcDbAssocDimDependencyBodyBase is erased. This static 
    /// method returns true iff this behavior is surpressed , i.e. not erasing 
    /// the AcDbDimension if the AcDbAssocDimDependencyBodyBase is erased. </summary>
    /// <returns> Returns whether the behavior is surpressed or not. </returns>
    ///
    static bool getEraseDimensionIfDependencyIsErased();

    /// <summary> This class is for internal use only. It disables notifications 
    /// when the dependency is not yet fully setup and these notifications would 
    /// complain about the data being in inconsistent state. </summary>
    ///
    class ACDB_PORT NotificationIgnorer
    {
    public:
        /// <summary> Default constructor. </summary>
        NotificationIgnorer();

        /// <summary> Destructor. </summary>
        ~NotificationIgnorer();

        /// <summary> Returns true iff notifications are ignored. </summary>
        /// <returns> Returns whether notifications are ignored. </returns>
        ///
        static bool isIgnoringNotifications();
    private:
        const bool mPrevIsIgnoringNotifications;
        static bool smIsIgnoringNotifications;
    };
};


#pragma pack (pop)


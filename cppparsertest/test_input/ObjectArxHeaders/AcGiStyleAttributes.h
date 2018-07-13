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
// AcGiStyleAttributes interface

#ifndef __AcGiStyleAttributes_H_Defined__
#define __AcGiStyleAttributes_H_Defined__

#include "AcGiLineAttributes.h"

class ADESK_NO_VTABLE AcGiStyleAttributes
{
public:

    enum AttributeFlags {
        kNothing                = 0x00,
        kColor                  = 0x01,
        kLine                   = 0x02,
        kLineType               = 0x04,
        kPlotStyle              = 0x08,
        kEverything             = 0x0F
    }; 

    // Ctor/dtor/copy
    AcGiStyleAttributes()   { }
    AcGiStyleAttributes(const AcGiStyleAttributes& source);
    virtual ~AcGiStyleAttributes()  { }

    // Member data access
    // Color
    AcCmEntityColor& getColorAttribute();
    const AcCmEntityColor& getColorAttribute() const;
    void setColorAttribute(const AcCmEntityColor& color);

    // Complex line type
    AcDbObjectId linetypeObjectId() const;
    void setLinetypeObjectId(const AcDbObjectId& newId);

    // Plot style
    AcDbObjectId plotStyleNameId() const;
    void setPlotStyleName(const AcDbObjectId& newId);

    // Interface methods - Other line attributes
    virtual AcGiLineAttributes* getLineAttribute()                              = 0;
    virtual const AcGiLineAttributes* getLineAttribute() const                  = 0;
    virtual void setLineAttribute(const AcGiLineAttributes* pLineAttributes)    = 0;

    virtual void EnsureColorVisibility (AcCmEntityColor& color)                 = 0;    

protected:
    /* The style engine will resolve the color, taking into account color
        policy, dither, specified color, assigned pen number, and dimming.
        If m_colorAttribute.isByColor() then use
        getColorAttribute().color();
        if m_colorAttribute.isByPen() then use
        getColorAttribute().penIndex()
    */
    AcCmEntityColor m_colorAttribute;

    AcDbObjectId    m_idLinetype;
    AcDbObjectId    m_idPlotstyle;
};

inline
AcGiStyleAttributes::AcGiStyleAttributes(
    const AcGiStyleAttributes& source) 
{
    m_colorAttribute = source.getColorAttribute();
    m_idLinetype = source.linetypeObjectId();
    m_idPlotstyle = source.plotStyleNameId();
}

inline
AcCmEntityColor& 
AcGiStyleAttributes::getColorAttribute()
{ 
    return m_colorAttribute; 
}

inline
const AcCmEntityColor& 
AcGiStyleAttributes::getColorAttribute() const
{ 
    return m_colorAttribute; 
}

inline 
void    
AcGiStyleAttributes::setColorAttribute (
    const AcCmEntityColor& color) 
{
    m_colorAttribute = color; 
}

inline
AcDbObjectId
AcGiStyleAttributes::linetypeObjectId() const
{
    return m_idLinetype;
}

inline
void 
AcGiStyleAttributes::setLinetypeObjectId(const AcDbObjectId& newId)
{
    m_idLinetype = newId;
}

inline
AcDbObjectId
AcGiStyleAttributes::plotStyleNameId() const
{
    return m_idPlotstyle;
}

inline
void
AcGiStyleAttributes::setPlotStyleName(const AcDbObjectId& newId)
{
    m_idPlotstyle = newId;
}

#endif // #ifndef __AcGiStyleAttributes_H_Defined__

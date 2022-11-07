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

#ifndef AcDMMEPlotProperty_h
#define AcDMMEPlotProperty_h

#include "AcArray.h"

/////////////////////////////////////////////////////////////////////////
// class AcDMMXMLAttribute
/////////////////////////////////////////////////////////////////////////

/// <summary>
/// This is a subsidiary class to AcDMMEplotProperty defined below.
/// You generally don't need to use this class.
///
/// Normal attributes, i.e. those predefined by Dwf such as name, value, units, etc.,
/// are added to an AcDMMEplotProperty using its built-in methods such as SetUnits.
/// 
/// Applications that define their own private namespaces and want to publish attributes
/// belonging to those namespaces need to use this class.
/// </summary>
///
/// <remarks>
/// On the publishing side, you generally don't need to create elements of this class, and can add
/// your elements to an AcDMMEplotProperty by using
///		AcDMMEplotProperty::AddXMLAttribute(const wchar_t *ns, const wchar_t *nsUrl, 
///                                         const wchar_t *attName, const wchar_t *attValue);
/// You will need this class mainly to read and interpret the existing vector of attributes
/// returned by AcDMMEplotProperty::GetXMLAttributes().
/// </remarks>
///

class AcDMMXMLAttribute
{
public:
    /// <summary>
    /// Default constructor
    /// </summary>
    ///
    /// <remarks> initializes data members to an empty state
    /// </remarks>
    ///
    AcDMMXMLAttribute()
    {
        setNull();
    }

    /// <summary>
    /// constructs an AcDMMXMLAttribute wrapping a namespace, namespace 
    /// location, attribute name and attribute value
    /// </summary>
    ///
    /// <param name="ns">
    /// a non-empty Unicode string supplying the namespace "tag" of the property
    /// </param>
    ///
    /// <param name="nsUrl">
    /// a non-empty Unicode string supplying a namespace URI for the property
    /// </param>
    ///
    /// <param name="attName">
    /// a Unicode string supplying the hidden attribute name of the property
    /// </param>
    ///
    /// <param name="attValue">
    /// a Unicode string supplying the hidden attribute value for the property
    /// this must not exceed 8192 bytes after xml encoding
    /// </param>
    ///
    /// <remarks> An AcDMMXMLAttribute must contain non-null values for all parameters,
    /// otherwise it will be ignored. Empty strings ("") for the namespace parameters will
    /// cause undefined behavior.
    /// </remarks>
    ///
    AcDMMXMLAttribute(const wchar_t *ns, const wchar_t *nsUrl, 
        const wchar_t *attName, const wchar_t *attValue)
    {
        setNull();
        SetNamespace(ns);
        SetNamespaceUrl(nsUrl);
        SetAttributeName(attName);
        SetAttributeValue(attValue);
    }

    /// <summary>
    /// operator= also used by the copy constructor
    /// </summary>
    ///
    /// <param name="src">
    /// the object whose values will be copied to this object
    /// </param>
    ///
    /// <returns>
    /// a const reference to this
    /// </returns>
    ///
    const AcDMMXMLAttribute& operator= (const AcDMMXMLAttribute& src)
    {
        if (this != &src)
        {
            setNull();
            SetNamespace(src.GetNamespace());
            SetNamespaceUrl(src.GetNamespaceUrl());
            SetAttributeName(src.GetAttributeName());
            SetAttributeValue(src.GetAttributeValue());
        }
        return *this;
    }

    /// <summary>
    /// Copy Constructor
    /// </summary>
    ///
    /// <param name="src">
    /// The object to copy from
    /// </param>
    ///
    AcDMMXMLAttribute(const AcDMMXMLAttribute& src)
    {
        *this = src;
    }

    /// <summary>
    /// Destructor
    /// </summary>
    ///
    /// <remarks>
    /// The string data in the property is freed by this destructor
    /// </remarks>
    ///
    ~AcDMMXMLAttribute()
    {
        if (NULL != m_namespace)
            delete [] m_namespace;
        if (NULL != m_namespaceUrl)
            delete [] m_namespaceUrl;
        if (NULL != m_attributeName)
            delete [] m_attributeName;
        if (NULL != m_attributeValue)
            delete [] m_attributeValue;
    }

    /// <summary>
    /// mutator for the namespace xml attribute
    /// </summary>
    ///
    /// <param name ="ns">
    /// A Unicode string setting the namespace of the property
    /// </param>
    ///
    void SetNamespace(const wchar_t* ns) 
    {
        delete [] m_namespace;
        if (NULL != ns) {
            size_t nSize = ::wcslen(ns) + 1;
            m_namespace = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_namespace, nSize, ns);
            assert(err == 0);
        } else {
            m_namespace = NULL;
        }
    }

    /// <summary>
    /// accessor for the namespace of the xml attribute
    /// </summary>
    ///
    /// <returns>
    /// Returns a const pointer to the Unicode xml namespace string
    /// </returns>
    ///
    const wchar_t* GetNamespace() const 
    {
        return m_namespace;
    }

    /// <summary>
    /// mutator for the namespace location of the xml attribute
    /// </summary>
    ///
    /// <param name ="nsUrl">
    /// A Unicode string setting the namespace location of the property
    /// </param>
    ///
    void SetNamespaceUrl(const wchar_t* nsUrl)    
    {
        delete [] m_namespaceUrl;
        if (NULL != nsUrl) {
            size_t nSize = ::wcslen(nsUrl) + 1;
            m_namespaceUrl = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_namespaceUrl, nSize, nsUrl);
            assert(err == 0);
        } else {
            m_namespaceUrl = NULL;
        }
    }

    /// <summary>
    /// accessor for the namespace location of the xml attribute
    /// </summary>
    ///
    /// <returns>
    /// Returns a const pointer to the Unicode namespace location string
    /// </returns>
    ///
    const wchar_t* GetNamespaceUrl() const  
    {
        return m_namespaceUrl;
    }

    /// <summary>
    /// mutator for the xml attribute name
    /// </summary>
    ///
    /// <param name ="attName">
    /// A Unicode string setting the attribute name of the property
    /// </param>
    ///
    void SetAttributeName(const wchar_t* attName)
    {
        delete [] m_attributeName;
        if (NULL != attName) {
            size_t nSize = ::wcslen(attName) + 1;
            m_attributeName = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_attributeName, nSize, attName);
            assert(err == 0);
        } else {
            m_attributeName = NULL;
        }
    }

    /// <summary>
    /// accessor for the xml attribute name
    /// </summary>
    ///
    /// <returns>
    /// Returns a const pointer to the Unicode xml attribute name string
    /// </returns>
    ///
    const wchar_t* GetAttributeName() const 
    {
        return m_attributeName;
    }

    /// <summary>
    /// mutator for the xml attribute value
    /// </summary>
    ///
    /// <param name ="attValue">
    /// A Unicode string setting the xml attribute value of the property
    /// </param>
    ///
    void SetAttributeValue(const wchar_t* attValue)
    {
        delete [] m_attributeValue;
        if (NULL != attValue) {
            size_t nSize = ::wcslen(attValue) + 1;
            m_attributeValue = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_attributeValue, nSize, attValue);
            assert(err == 0);
        } else {
            m_attributeValue = NULL;
        }
    }

    /// <summary>
    /// accessor for the xml attribute value
    /// </summary>
    ///
    /// <returns>
    /// Returns a const pointer to the xml attribute value string
    /// </returns>
    ///
    const wchar_t* GetAttributeValue() const 
    {
        return m_attributeValue;
    }

private:
    wchar_t * m_namespace;
    wchar_t * m_namespaceUrl;
    wchar_t * m_attributeName;
    wchar_t * m_attributeValue;

    void setNull() 
    {
        m_namespace = NULL;
        m_namespaceUrl = NULL;
        m_attributeName = NULL;
        m_attributeValue = NULL;
    }
};
typedef AcArray<AcDMMXMLAttribute> AcDMMXMLAttributeVec;


/////////////////////////////////////////////////////////////////////////
// class AcDMMEPlotProperty
/////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class is a lightweight proxy for the DWF EPlotProperty object.
/// It allows clients of the DMM (DWF Metadata Manager) API to add
/// properties to an AcDMMEPlotProperties object which in turn
/// is used to associate properties with an entity in a DWF file
/// without linking to the DWF toolkit
/// </summary>
///
/// <remarks>
/// This is just a container for Unicode strings. Two of these are required,
/// the property name and its value. The other three are optional. If the 
/// strings are not already XML encoded, they will be encoded when this 
/// object is converted to the corresponding DWF toolkit object and this
/// can result in significant expansion of the string due to the
/// escaping of reserved characters. The maximum length of any encoded
/// attribute string is 8192 bytes.
/// </remarks>
///
class AcDMMEPlotProperty
{
public:

    /// <summary>
    /// Default constructor
    /// </summary>
    ///
    /// <remarks> initializes data members to an empty state
    /// </remarks>
    ///
    AcDMMEPlotProperty()
    {
        m_name = NULL;
        m_value = NULL;
        m_type = NULL;
        m_units = NULL;
        m_category = NULL;
    }
    
    /// <summary>
    /// constructs an AcDMMEPlotProperty wrapping a name and value
    /// </summary>
    ///
    /// <param name="name">
    /// a Unicode string supplying the name of the property
    /// </param>
    ///
    /// <param name="value">
    /// a Unicode string supplying a value for the property
    /// this must not exceed 8192 bytes after xml encoding
    /// </param>
    ///
    /// <remarks> can construct from two wide strings supplying just 
    /// the property name and property value. 
    /// </remarks>
    ///
    AcDMMEPlotProperty(const wchar_t *name, const wchar_t * value)
    {
        if (NULL != name) {
            size_t nSize = ::wcslen(name) + 1;
            m_name = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_name, nSize, name);
            assert(err == 0);
        } else {
            m_name = NULL;
        }    
    
        if (NULL != value) {
            size_t nSize = ::wcslen(value) + 1;
            m_value = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_value, nSize, value);
            assert(err == 0);
        } else {
            m_value = NULL;
        }    
        m_category = NULL;
        m_type = NULL;
        m_units = NULL;
    }
    
    /// <summary>
    /// Copy Constructor
    /// </summary>
    ///
    /// <param name="src">
    /// The object to copy from
    /// </param>
    ///
    AcDMMEPlotProperty(const AcDMMEPlotProperty &src)
    {
        m_name = NULL;
        m_value = NULL;
        m_type = NULL;
        m_units = NULL;
        m_category = NULL;
        {*this = src;}
    }


    /// <summary>
    /// Destructor
    /// </summary>
    ///
    /// <remarks>
    /// The string data in the property is freed by this destructor
    /// </remarks>
    ///
    ~AcDMMEPlotProperty()
    {
        if (NULL != m_name)
            delete [] m_name;
        if (NULL != m_value)
            delete [] m_value;
        if (NULL != m_category)
            delete [] m_category;
        if (NULL != m_type)
            delete [] m_type;
        if (NULL != m_units)
            delete [] m_units;
    }
    
    /// <summary>
    /// mutator for the optional Type attribute
    /// </summary>
    ///
    /// <param name ="type">
    /// A Unicode string setting the DWF type of the property
    /// </param>
    ///
    /// <remarks>
    /// type is an optional Unicode string
    ///    
    /// some recognized type name strings:
    /// String_List_Type "string"
    /// Boolean_Type "boolean"
    /// UriReference_Type "uriReference"
    /// TimeDuration_Type "timeDuration"
    /// TimeInstant_Type "timeInstant"
    /// Date_Type "date"
    /// Month_Type "month"
    /// Year_Type "year"
    /// Century_Type "century"
    /// RecurringDate_Type "recurringDate"
    /// RecurringDay_Type "recurringDay"
    /// Float_Type "float"
    /// Double_Type "double"
    /// Double_List_Type "doubleList"
    /// Long_Type  "long"
    /// Long_List_Type; "longList"
    /// Int_Type "int"
    /// Short_Type "short"
    /// Byte_Type "byte"
    /// UnsignedLong_Type "unsignedLong"
    /// UnsignedInt_Type "unsignedint"
    /// UnsignedShort_Type "unsignedShort"
    /// UnsignedByte_Type "unsignedByte"
    /// StringList_Type "stringList"
    ///
    /// Note: the List types are space separated lists of values 
    /// </remarks>
    void SetType(const wchar_t * type)
    {
        if (m_type) {
            delete [] m_type;
            m_type = NULL;
        }
    
        if (NULL != type) {
            size_t nSize = ::wcslen(type) + 1;
            m_type = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_type, nSize, type);
            assert(err == 0);
        } else {
            m_type = NULL;
        }    
    }
    
    /// <summary>
    /// accessor for the optional Type attribute
    /// </summary>
    ///
    /// <returns>
    /// Returns a const pointer to the Unicode Type string
    /// </returns>
    const wchar_t * GetType() const
    {
        return m_type;
    }
    
    
    /// <summary>
    /// mutator for the optional Units attribute
    /// </summary>
    ///
    /// <param name ="units">
    /// A Unicode string setting the DWF units of the property
    /// </param>
    ///
    /// <remarks>
    /// The units string is appended to the value string by the viewer
    /// when displaying properties. The convention is that they should be
    /// English and obvious, e.g., standard, abbreviations wherever possible.
    /// Examples include mm, cm, m, km, in, ft, yd and mi.
    /// </remarks>
    void SetUnits(const wchar_t * units)
    {
        if (m_units) {
            delete [] m_units;
            m_units = NULL;
        }
    
        if (NULL != units) {
            size_t nSize = ::wcslen(units) + 1;
            m_units = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_units, nSize, units);
            assert(err == 0);
        } else {
            m_units = NULL;
        }    
    }
    
    /// <summary>
    /// accessor for the optional Units attribute
    /// </summary>
    ///
    /// <returns>
    /// Returns a const pointer to the Unicode Units string
    /// </returns>
    const wchar_t * GetUnits() const
    {
        return m_units;
    }
    
    
    /// <summary>
    /// mutator for the optional Category attribute
    /// </summary>
    ///
    /// <param name ="category">
    /// A Unicode string setting the category of the property
    /// </param>
    ///
    /// <remarks>
    /// category is a Unicode string property for categorizing objects
    /// The category string is displayed in the DWF viewer properties window
    /// Clients may use category in various ways. The viewer recognizes one
    /// magic category, hidden, which will cause it not to display the 
    /// property.
    /// </remarks>
    ///
    void SetCategory(const wchar_t * category)
    {
        if (m_category) {
            delete [] m_category;
            m_category = NULL;
        }
    
        if (NULL != category) {
            size_t nSize = ::wcslen(category) + 1;
            m_category = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_category, nSize, category);
            assert(err == 0);
        } else {
            m_category = NULL;
        }    
    }
    
    
    /// <summary>
    /// accessor for the optional Category attribute
    /// </summary>
    ///
    /// <returns>
    /// Returns a const pointer to the Unicode Category string
    /// </returns>
    ///
    const wchar_t * GetCategory() const
    {
        return m_category;
    }


    /// <summary>
    /// mutator for the required property Name attribute
    /// </summary>
    ///
    /// <param name ="name">
    /// A Unicode string setting the name of the property
    /// </param>
    ///
    /// <remarks>
    /// the name is a Unicode string property 
    /// The name string is displayed in the DWF viewer properties window
    /// </remarks>
    ///
    void SetName(const wchar_t * name)
    {
        if (m_name) {
            delete [] m_name;
            m_name = NULL;
        }
    
        if (NULL != name) {
            size_t nSize = ::wcslen(name) + 1;
            m_name = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_name, nSize, name);
            assert(err == 0);
        } else {
            m_name = NULL;
        }    
    }
        
        
    /// <summary>
    /// accessor for the required property name attribute
    /// </summary>
    ///
    /// <returns>
    /// Returns a const pointer to the Unicode name string
    /// </returns>
    ///
    const wchar_t * GetName() const
    {
        return m_name;
    }
    
    /// <summary>
    /// mutator for the reqiured property Value attribute
    /// </summary>
    ///
    /// <param name ="value">
    /// A Unicode string setting the value of the property
    /// </param>
    ///
    /// <remarks>
    /// value is a Unicode string property for objects
    /// The value string is displayed in the DWF viewer properties window
    /// </remarks>
    void SetValue(const wchar_t * value)
    {
        if (m_value) {
            delete [] m_value;
            m_value = NULL;
        }
    
        if (NULL != value) {
            size_t nSize = ::wcslen(value) + 1;
            m_value = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_value, nSize, value);
            assert(err == 0);
        } else {
            m_value = NULL;
        }    
    }
    
    /// <summary>
    /// accessor for the required proterty Value attribute
    /// </summary>
    ///
    /// <returns>
    /// Returns a const pointer to the Unicode Value string
    /// </returns>
    ///
    const wchar_t * GetValue() const
    {
        return m_value;
    }
    
    /// <summary>
    /// operator= also used by the copy constructor
    /// </summary>
    ///
    /// <param name="src">
    /// the object whose values will be copied to this object
    /// </param>
    ///
    /// <returns>
    /// a const reference to this
    /// </returns>
    ///
    AcDMMEPlotProperty& operator= (const AcDMMEPlotProperty& src)
    {
        if (this == &src)
            return *this;
    
        SetName(src.m_name);
        SetValue(src.m_value);
        SetType(src.m_type);
        SetUnits(src.m_units);
        SetCategory(src.m_category);
        m_XMLAttributes = src.m_XMLAttributes;
        return *this;
    }
    
    /// <summary>
    /// Adds a new AcDMMXMLAttribute object to the internal 
    /// vector of XML Attributes.
    /// </summary>
    ///
    /// <param name="attrib">
    /// a const pointer to the XMLAttibute that needs to be added to the
    /// vector of XML attributes
    /// </param>
    ///
    void AddXMLAttribute(const AcDMMXMLAttribute * attrib)
    {
        if(attrib)
            AddXMLAttribute(attrib->GetNamespace(),
                            attrib->GetNamespaceUrl(),
                            attrib->GetAttributeName(),
                            attrib->GetAttributeValue());
    }

    /// <summary>
    /// Creates and adds a new AcDMMXMLAttribute object to the internal 
    /// vector of XML Attributes.
    /// </summary>
    ///
    /// <param name="ns">
    /// the new Attribute's namespace name
    /// </param>
    ///
    /// <param name="nsUrl">
    /// the new Attribute's namepsace location
    /// </param>
    ///
    /// <param name="attName">
    /// the new Attribute's name
    /// </param>
    ///
    /// <param name="value">
    /// the new Attribute's value
    /// </param>
    ///
    void AddXMLAttribute(const wchar_t *ns, const wchar_t *nsUrl, const wchar_t *attName, const wchar_t *attValue)
    {
        if (NULL != ns && NULL != nsUrl && NULL != attName && NULL != attValue)
            m_XMLAttributes.append(AcDMMXMLAttribute(ns,nsUrl,attName,attValue));
    }
    
    /// <summary>
    /// accessor for the internal vector of AcDMMXMLAttribute objects
    /// contained by this object
    /// </summary>
    ///
    /// <returns>
    /// Returns a const reference to the internal Vector of 
    /// AcDMMXMLAttribute objects contained by this object
    /// </returns>
    const AcDMMXMLAttributeVec& GetXMLAttributes() const
    {
        return m_XMLAttributes;
    }

    
private:
    wchar_t * m_name; 
    wchar_t * m_value;
    wchar_t * m_type;
    wchar_t * m_units;
    wchar_t * m_category;

    AcDMMXMLAttributeVec    m_XMLAttributes;
};
    
typedef AcArray<AcDMMEPlotProperty> AcDMMEPlotPropertyVec;
    
#endif // AcDMMEPlotProperty_h

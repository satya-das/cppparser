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

#pragma once
#include "rxvar.h"
#include "adscodes.h"
///<summary>Cache for very performance sensitive code paths that
///require checking the value an AcRxVariable.
/// <example>
///recommended usage:
///static AcRxVariableCache var(L"GPULINETYPE");
///if (var.getBool(true)) {...}
///Note that the variable is static (or long scope) otherwise
///you are not gaining anything performance wise.
///< / example>
class AcRxVariableCache : public AcRxVariableReactor
{
    /// <summary>
    /// Implemenation detail: handles updating the cache when variable changes.
    /// </summary>
    virtual void changed(const AcRxVariable* sender, const AcRxVariableChangedEventArgs& args) override
    {
        const auto& rb = args.newValue();
        memcpy(&m_cache, &rb, sizeof(rb));
        if (rb.restype == RTSTR)
        {
            Acad::ErrorStatus es = acutUpdString(rb.resval.rstring, m_cache.resval.rstring);
            ASSERT(Acad::eOk == es);
        }
    }
    resbuf m_cache;
    AcString m_name;
public:
    /// <summary>
    /// Constructs a cache instance. The cache should be scoped long enough so that it is not 
    /// created/destroyed for every access.
    /// </summary>
    /// <param name="name"/>Name of the AcRxVariable which the cache is to be constructed for.</param>
    AcRxVariableCache(const ACHAR* name)
        :m_name(name)
        , m_cache({ 0 })
    {
        m_cache.restype = RTNONE;
        auto var = AcRxVariablesDictionary::get()->getVariable(name);
        //we will tolerate sysvars that are missing
        if (var == nullptr)
            return;
        var->addReactor(this);
        Acad::ErrorStatus es = var->getValue(m_cache);
        ASSERT(Acad::eOk == es);
    }
    /// <summary>
    /// Destructs the cache.
    /// </summary>
    ~AcRxVariableCache()
    {
        auto var = AcRxVariablesDictionary::get()->getVariable(m_name.kwszPtr());
        if (var == nullptr)
            return;
        var->removeReactor(this);
    }
    /// <summary>
    /// High performance accessor (boolean overload)
    /// </summary>
    /// <param name="def">default value that the function will return if
    /// the value of the variable is not available for any reason.
    /// </param>
    bool getBool(bool def)
    {
        return !!getInt16(def ? 1 : 0);
    }
    /// <summary>
    /// High performance accessor (int16 overload)
    /// </summary>
    /// <param name="def">default value that the function will return if
    /// the value of the variable is not available for any reason.
    /// </param>
    short getInt16(short def)
    {
        ASSERT(m_cache.restype == RTSHORT || m_cache.restype == RTNONE);
        if (m_cache.restype != RTSHORT)
            return def;
        return m_cache.resval.rint;
    }
    /// <summary>
    /// High performance accessor (double overload)
    /// </summary>
    /// <param name="def">default value that the function will return if
    /// the value of the variable is not available for any reason.
    /// </param>
    double getDouble(double def)
    {
        ASSERT(m_cache.restype == RTREAL || m_cache.restype == RTNONE);
        if (m_cache.restype != RTREAL)
            return def;
        return m_cache.resval.rreal;
    }
    /// <summary>
    /// High performance accessor (string overload)
    /// </summary>
    AcString getString()
    {
        AcString ret;
        ASSERT(m_cache.restype == RTSTR || m_cache.restype == RTNONE);
        if (m_cache.restype != RTSTR)
            return ret;
        return m_cache.resval.rstring;
    }
};
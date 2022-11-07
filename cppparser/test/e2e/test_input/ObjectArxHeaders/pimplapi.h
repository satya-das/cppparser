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

namespace Pimpl
{
    class ImpBase;
    //Simple helper template to implement to help implement the Pimpl Idiom.
    template <typename Base, class ImpPart>
    class ApiPart : public Base
    {
    protected:
        ApiPart(ImpPart* pImp) throw()
        :m_pImp(pImp)
        {
        }
        //Must be defined by user code to delete m_pImp.
        //The template cannot do this since ImpPart is not known here.
        ~ApiPart(); 
    private:
        friend class ImpBase;
        ImpPart* m_pImp;
    };
    
    //partial specialization for no base class
    template <class ImpPart>
    class ApiPart<void, ImpPart>
    {
    protected:
        ApiPart(ImpPart* pImp) throw()
        :m_pImp(pImp)
        {
        }
        ~ApiPart(); //must be defined by user code
    private:
        friend class ImpBase;
        ImpPart* m_pImp;
    };
}

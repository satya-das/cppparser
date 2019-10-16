//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#pragma  once
namespace Pimpl
{
  class ImpBase;
  template <typename Base, typename ImpPart>
  class ApiPart : public Base
  {
  protected:
    ApiPart(ImpPart* pImp)
      : m_pImp(pImp)
    {
    }
    ~ApiPart();
  private:
    friend class ImpBase;
    ImpPart* m_pImp;
  };
  template <typename ImpPart>
  class ApiPart<void, ImpPart>
  {
  protected:
    ApiPart(ImpPart* pImp)
      : m_pImp(pImp)
    {
    }
    ~ApiPart();
  private:
    friend class ImpBase;
    ImpPart* m_pImp;
  };
}

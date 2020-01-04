/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GrProcessorUnitTest_DEFINED
#  define GrProcessorUnitTest_DEFINED
#  include "include/core/SkTypes.h"
#  if  GR_TEST_UTILS
#    include "include/private/SkTArray.h"
#    include "src/gpu/GrTestUtils.h"
#    include "src/gpu/GrTextureProxy.h"
class SkMatrix;
class GrCaps;
class GrContext;
class GrProxyProvider;
class GrRenderTargetContext;
struct GrProcessorTestData;
class GrTexture;
class GrXPFactory;
class GrGeometryProcessor;
namespace GrProcessorUnitTest
{
// Used to access the dummy textures in TestCreate procs.
  enum {
    kSkiaPMTextureIdx = 0,
    kAlphaTextureIdx = 1,
};
/** This allows parent FPs to implement a test create with known leaf children in order to avoid
creating an unbounded FP tree which may overflow various shader limits. */
  std::unique_ptr<GrFragmentProcessor> MakeChildFP(GrProcessorTestData*);
}
struct GrProcessorTestData
{
  GrProcessorTestData(SkRandom* random, GrContext* context, const GrRenderTargetContext* renderTargetContext, sk_sp<GrTextureProxy> proxies[2])
    : fRandom(random)
    , fRenderTargetContext(renderTargetContext)
    , fContext(context)
  {
    SkASSERT(proxies[0] && proxies[1]);
    fProxies[0] = proxies[0];
    fProxies[1] = proxies[1];
  }
  SkRandom* fRandom;
  const GrRenderTargetContext* fRenderTargetContext;
  GrContext* context()
  {
    return fContext;
  }
  GrResourceProvider* resourceProvider();
  GrProxyProvider* proxyProvider();
  const GrCaps* caps();
  sk_sp<GrTextureProxy> textureProxy(int index)
  {
    return fProxies[index];
  }
private:
  GrContext* fContext;
  sk_sp<GrTextureProxy> fProxies[2];
};
class GrProcessor;
class GrTexture;
template <typename ProcessorSmartPtr>
class GrProcessorTestFactory : private SkNoncopyable
{
  using Processor = typename ProcessorSmartPtr::element_type;
  using MakeProc = ProcessorSmartPtr (*) (GrProcessorTestData*);
;
public:
  GrProcessorTestFactory(MakeProc makeProc)
  {
    fMakeProc = makeProc;
    GetFactories()->push_back(this);
  }
    /** Pick a random factory function and create a processor.  */
  static ProcessorSmartPtr Make(GrProcessorTestData* data)
  {
    VerifyFactoryCount();
    if (GetFactories()->count() == 0)
    {
      return nullptr;
    }
    uint32_t idx = data->fRandom->nextRangeU(0, GetFactories()->count() - 1);
    return MakeIdx(idx, data);
  }
    /** Number of registered factory functions */
  static int Count()
  {
    return GetFactories()->count();
  }
    /** Use factory function at Index idx to create a processor. */
  static ProcessorSmartPtr MakeIdx(int idx, GrProcessorTestData* data)
  {
    SkASSERT(idx < GetFactories()->count());
    GrProcessorTestFactory<ProcessorSmartPtr>* factory = (*GetFactories())[idx];
    ProcessorSmartPtr processor = factory->fMakeProc(data);
    SkASSERT(processor);
    return processor;
  }
private:
    /**
     * A test function which verifies the count of factories.
     */
  static void VerifyFactoryCount();
  MakeProc fMakeProc;
  static SkTArray<GrProcessorTestFactory<ProcessorSmartPtr>*, true>* GetFactories();
};
using GrFragmentProcessorTestFactory = GrProcessorTestFactory<std::unique_ptr<GrFragmentProcessor>>;
using GrGeometryProcessorTestFactory = GrProcessorTestFactory<sk_sp<GrGeometryProcessor>>;
class GrXPFactoryTestFactory : private SkNoncopyable
{
  using GetFn = const GrXPFactory* (*) (GrProcessorTestData*);
;
public:
  GrXPFactoryTestFactory(GetFn* getProc)
    : fGetProc(getProc)
  {
    GetFactories()->push_back(this);
  }
  static const GrXPFactory* Get(GrProcessorTestData* data)
  {
    VerifyFactoryCount();
    if (GetFactories()->count() == 0)
    {
      return nullptr;
    }
    uint32_t idx = data->fRandom->nextRangeU(0, GetFactories()->count() - 1);
    const GrXPFactory* xpf = (*GetFactories())[idx]->fGetProc(data);
    SkASSERT(xpf);
    return xpf;
  }
private:
  static void VerifyFactoryCount();
  GetFn* fGetProc;
  static SkTArray<GrXPFactoryTestFactory*, true>* GetFactories();
};
#    if  SK_ALLOW_STATIC_GLOBAL_INITIALIZERS
#      define GR_DECLARE_GEOMETRY_PROCESSOR_TEST	static GrGeometryProcessorTestFactory gTestFactory SK_UNUSED; \
    static sk_sp<GrGeometryProcessor> TestCreate(GrProcessorTestData*);
#      define GR_DECLARE_FRAGMENT_PROCESSOR_TEST	static GrFragmentProcessorTestFactory gTestFactory SK_UNUSED; \
    static std::unique_ptr<GrFragmentProcessor> TestCreate(GrProcessorTestData*);
#      define GR_DECLARE_XP_FACTORY_TEST	static GrXPFactoryTestFactory gTestFactory SK_UNUSED;                                          \
    static const GrXPFactory* TestGet(GrProcessorTestData*);
#      define GR_DEFINE_FRAGMENT_PROCESSOR_TEST(Effect)	 \
    GrFragmentProcessorTestFactory Effect::gTestFactory(Effect::TestCreate)
#      define GR_DEFINE_GEOMETRY_PROCESSOR_TEST(Effect)	 \
    GrGeometryProcessorTestFactory Effect::gTestFactory(Effect::TestCreate)
#      define GR_DEFINE_XP_FACTORY_TEST(Factory)	                                                         \
    GrXPFactoryTestFactory Factory::gTestFactory(Factory::TestGet)
#    else 
#      define GR_DECLARE_FRAGMENT_PROCESSOR_TEST	static std::unique_ptr<GrFragmentProcessor> TestCreate(GrProcessorTestData*);
#      define GR_DEFINE_FRAGMENT_PROCESSOR_TEST(X)
#      define GR_DECLARE_GEOMETRY_PROCESSOR_TEST	static sk_sp<GrGeometryProcessor> TestCreate(GrProcessorTestData*);
#      define GR_DEFINE_GEOMETRY_PROCESSOR_TEST(X)
#      define GR_DECLARE_XP_FACTORY_TEST	const GrXPFactory* TestGet(GrProcessorTestData*);
#      define GR_DEFINE_XP_FACTORY_TEST(X)
#    endif
#  else 
#    define GR_DECLARE_GEOMETRY_PROCESSOR_TEST
#    define GR_DECLARE_FRAGMENT_PROCESSOR_TEST
#    define GR_DECLARE_XP_FACTORY_TEST
#    define GR_DEFINE_FRAGMENT_PROCESSOR_TEST	(...)
#    define GR_DEFINE_GEOMETRY_PROCESSOR_TEST	(...)
#    define GR_DEFINE_XP_FACTORY_TEST	(...)
#    define GR_DECLARE_FRAGMENT_PROCESSOR_TEST
#    define GR_DEFINE_FRAGMENT_PROCESSOR_TEST	(...)
#    define GR_DECLARE_GEOMETRY_PROCESSOR_TEST
#    define GR_DEFINE_GEOMETRY_PROCESSOR_TEST	(...)
#    define GR_DECLARE_XP_FACTORY_TEST
#    define GR_DEFINE_XP_FACTORY_TEST	(...)
#  endif
#endif

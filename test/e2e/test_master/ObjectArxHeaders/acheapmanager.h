#ifndef ACHEAPMANAGER_H_
#  define ACHEAPMANAGER_H_
#  pragma  once
#  include "PAL/api/heap.h"
#  include "acbasedefs.h"
ACBASE_PORT void* acStackHeapAlloc(size_t size, const void* pParent);
ACBASE_PORT void* acStackHeapRealloc(void* p, size_t size);
ACBASE_PORT void acStackHeapFree(void* p);
#  pragma  push_macro("new")
#  undef new
#  pragma  push_macro("delete")
#  undef delete
#  pragma  pack (push, 8)
class AcStackAllocator
{
public:
  virtual ~AcStackAllocator();
  static void* operator new(size_t size, void* pParent)
  {
    return acStackHeapAlloc(size, pParent);
  }
  static void operator delete(void* p, void* pParent)
  {
    ADESK_UNREFED_PARAM(pParent);
    return acStackHeapFree(p);
  }
  static void deallocate(AcStackAllocator* p, void* pParent)
  {
    p->~AcStackAllocator();
    AcStackAllocator::operator delete(p, pParent);
  }
protected:
  static void operator delete(void* p)
  {
    return acStackHeapFree(p);
  }
};
inline AcStackAllocator::~AcStackAllocator()
{
}
#  pragma  pack (pop)
#  pragma  pop_macro("delete")
#  pragma  pop_macro("new")
#endif

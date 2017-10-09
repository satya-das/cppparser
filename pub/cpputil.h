#pragma once

#include "cppconst.h"

/**
* Can be used to find default inheritance type of a compound object.
* @param type Type of compound object.
* @return Default inheritance type of class/struct/union if not explicitly specified.
*/
inline CppObjProtLevel defaultInheritanceType(CppCompoundType type)
{
  return type == kClass ? kPrivate : kPublic;
}

/**
* Can be used to find default protection level of a compound object.
* @param type Type of compound object.
* @return Default protection level of member of a class/struct/union if not explicitly specified.
*/
inline CppObjProtLevel defaultMemberProtLevel(CppCompoundType type)
{
  return type == kClass ? kPrivate : kPublic;
}

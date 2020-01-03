/**
 * P: This test file is for ascertaining how cppparser preserves comments.
 * C++ can have comments anywhere and it is almost impossible to not ignore
 * any comments. So, CppParser is designed to preserve "well formed" comments only.
 * Comments at unusual places are just ignored.
 * This file explains what CppParser preserves and what are losts.
 * Comments marked with "P: " are preserved and those with "L: " are ignored and lost.
 * For example comments at beginning of files are preserved and so we have "P: " at line #2.
 */

// P: ///////////////////////////////////////////////////////////////////////////

/****************************************************************************
 * P: Any free standing comment                                             *
 ***************************************************************************/
int x;
int y;
void* buf;
#define CALLTYPE	__stdcall // L: Line comment used in #define
#define CDECLTYP	__cdecl   /* L: Block comment used in #define */
// P: Comments are fine here
struct B
{
};
/*
P: Comment before class definition
*/
class A : public B
{
  // P: Comments here are OK.
public:
  // P: Here as well.
  void func()
  {
    // P: It's fine here.
    auto x = ;
    f(param1, param2);
  }
};
// P: From here again we can preserve the comments

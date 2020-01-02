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

/* L: Two comments in same line */ /* L: are lost because they are not free standing */
int x; // L: Line comment after statement
int y; /* L: Block comment after var declaration */

void* /* L: Comments embedded in a statement*/ buf;

#define CALLTYPE __stdcall // L: Line comment used in #define
#define CDECLTYP __cdecl   /* L: Block comment used in #define */

// P: Comments are fine here
struct B
{
} /* L: Not here */;
/*
P: Comment before class definition
*/
class A /* L: Why put comment here? */ : public /* L: And why here? */ B
// L: Here as well, just why?
{
  // P: Comments here are OK.
public:
  // P: Here as well.
  void func() /* L: But not here */
  {
    // P: It's fine here.
    auto x = [](/* L: But not here*/) // L: not here as well
    {
      // P: It's OK here.
      int x = 5;
    }; /* L: No way it will be preserved. */

    f(
      /* L: A comment like this only looks like free standing one but are actually not. */
      param1, // L: no no, we will not preserve comments in the middle of parameters passing.
      /* L: This too will be lost. Sorry. */ param2);
  }
}; /*L: No way, stop putting comments at arbitrary places. */
// P: From here again we can preserve the comments

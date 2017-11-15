/////////////////////////////////////////////////////////////////////////////

/**
 * Doxygen style block comment.
 * Test else fail
 */

/// Doxygen style line comment.

/****************************************************************************
 * Copyright style comment 													*
 ***************************************************************************/

int x; // Line comment after var declaration
int y; /* Block comment after var declaration */

void* /* comment embedded in a statement*/ buf;

#define CALLTYPE	__stdcall // Line comment used in #define
#define CDECLTYP	__cdecl /* Block comment used in #define */


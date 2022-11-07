#define RENAME	NEWNAME
#define STRDEF	"string definition"
#define STRCAT	STRDEF STRDEF
#define STRLITCAT	STRDEF "concatenating string"
#define STRLITCAT2	"concatenating string1" "concatenating string2"
#define MACROCALL(x)	 MacroCall(x)
#define MACROCALL2(x, y)	 MacroCall2(x, y)
#define MULTILINEMACRO(x)	 MacroCall(x)  \
  MacroCallLine2(x)                     \
  MacroCallLine3(x)
#define MULTILINEMACRO2(x)	 MacroCall2(x, y)  \
  MacroCall2Line2(x, y)                     \
  MacroCall2Line3(x, y)
#define _ACRX_T(x)		L ## x
#define ACRX_DECLARE_MEMBERS_ACBASE_PORT_EXPIMP(CLASS_NAME)	 \
    ACRX_DECLARE_MEMBERS_EXPIMP(CLASS_NAME, ACBASE_PORT)

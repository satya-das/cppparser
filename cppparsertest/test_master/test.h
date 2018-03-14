#define PI	3.1416
#define MACRO	(x) x##x
#define GL_POLYGON	0x0009
typedef short GLshort;
typedef int GLint, GLsizei;
typedef unsigned char GLboolean;
typedef unsigned int GLenum, GLbitfield;
WINGDIAPI void APIENTRY glVertex2iv(const GLint* v);
WINGDIAPI void APIENTRY glVertex2s(GLshort x, GLshort y);
/* Single line block comment to document code*/
int x;
int a[100];
double d[2 * 7];
class FwdDeclClass;
const FwdDeclClass* XXX;
extern "C" {
int i;
int j;
int* pi;
void FunctionWithoutParam();
void FunctionWithOneParam(float* x);
void FunctionWithTwoParam(int, double);
typedef void (APIENTRY *PFNGLADDSWAPHINTRECTWINPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
}
/**
 * Multiple line block comment to document code
 */
class EXPIMP TestClass :  BaseClass1, private BaseClass2
{
public:
	TestClass();
	~TestClass();
	~TestClass()
	{
	}
	virtual int PureVirtualMethod() = 0;
	// Line comment to document code.
	static double& dMem;
	const float* fMem;
	int* const piMem;
	static const int* XXX;
	A ::B x;
	signed short s;
};
x = 0;

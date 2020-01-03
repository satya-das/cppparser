inline int f(int x)
{
  return 5;
}
inline int g(int& x)
{
  return x = 5;
}
static double add(double x, double y)
{
  double a = x + y;
  return a;
}
double sub(double x, double y)
{
  return x - y;
}
void proc()
{
  printf("Test test and more test\n");
  return ;
}
// Function call tests
void variousFunctionCallingTests()
{
  add(4, 50);
  add(2, 4) + sub(4, 1);
  f(6);
	// Member function tests
  a.f();
  a->f();
	// Function proc test
	/* It is failing as of now.
	double (*p)(double, double) = add;
	(*p)(4, 5);
	*/
  typedef double (*P) (double, double);
  P p = add;
  (*p)(4, 5);
}
extern void externFunc();

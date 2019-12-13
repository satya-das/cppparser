typedef int* INTP;
int main()
{
  int i, j;
  const INTP p = &i;
  const INTP q = &i;
  const int* x = &i;
  int* const y = &i;
  int* const * pcpi;
  std::vector<int>& x;
}

typedef int* INTP;
int main()
{
  int i, j;
  const INTP p = &i;
  INTP const q = &i;
  const int* x = &i;
  int* const y = &i;
  int* const * pcpi;
  std::vector<int>& x;
}

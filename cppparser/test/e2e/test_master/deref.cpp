struct S
{
  int x;
  double y;
};
S s;
s.x = 4;
s.y = 10.8;
S* ps = &s;
ps->x = 8;
ps->y = 78 * 6.0 / 19.8;

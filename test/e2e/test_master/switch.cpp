void SwitchTest()
{
  switch(GetParam())
  {
    case 1:
      What();
      break;
    case 2:
      JustContinue();
    case 3:
      NowBreak();
      break;
default:
    DoDefault();
}
}

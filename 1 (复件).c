
void mian(void)
{
#if A
	int a;
#else
	int not_a;
#   ifdef B
	int define_b;
#   endif
#   ifndef C
	int ndef_c;
#   else
	int def_c;
#       if defind(D)
	int defined_d;
#       endif
#   endif
#endif
	return 0;
}

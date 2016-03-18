void mian(void)
{
#if A /* mix with if else define endif*/
	int a;
#else /* mix with if else define endif*/
	int nota;
#   ifdef B
	int b;
#   endif
#   ifndef C
	int notc;
#   else
	int c;
#       if defind(D)
	int d;
#       elif E /* mix with if else define endif*/
	int e;
#       elif F
#			if F1 /* mix with if else define endif*/
#			elif F2
	int f2;
#			elif F3
#			else /* mix if else define and so on*/
    int notfx 
#			endif /* mix with if else define endif*/
#       elif G
#			if G1  // here is G1 defined 
	int g1;
#			else //asdasd
	int gx;
#			endif /** sadasdasd */
#       elif H
	int h;
#		else /* mix with if else define endif*/
	int notefgh; /* mix with if else define endif*/
#       endif
# endif
#endif /* mix with if else define endif*/
 	int x;
	return 0; /* mix with if else define endif*/
}

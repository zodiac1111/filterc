void mian(void)
{
#if A /* mix with if else define endif*/
	int aaaa;
#else /* mix with if else define endif*/
	int nota;
#   ifdef B
	int abcd;
	int b;
#   endif
	int bbbb;
	int cccc;
#   ifdef C
	int c;
#   endif
	abcd=3;
	aaaa=2;
#endif
	bbbb=3;
	return 0; /* mix with if else define endif*/
}

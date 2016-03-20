void mian(void)
{
#if A 
	int aaaa;
#else /* A */
	int nota;
#   ifdef B
	int b;
	int be;
#   endif /* B */
	int bbbb;
	int cccc;
#   ifdef C
	int c;
#   endif /* C */
	abcd=3;
	aaaa=4;
#endif /* A */
	bbbb=3;
	return 0; /* mix with if else define endif*/
}

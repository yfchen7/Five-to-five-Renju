


struct patnum
{
	unsigned char changlian;
	unsigned char chengwu;
	unsigned char huosi;
	
	unsigned char chongsi;
	unsigned char huosan;
	
	unsigned char miansan;

	unsigned char lianer1;
	unsigned char lianer2;
	unsigned char tiaoer;
	unsigned char jianer;
	
	unsigned char mianer;
	unsigned char huoyi1;
	unsigned char huoyi2;
	unsigned char yuchanglian;
	unsigned char yuchongsi;
};
extern struct patnum patbook[1 << 16];
extern void GenPat(void);

#define min(x, y) (x < y ? x : y)
#define max(x, y) (x < y ? y : x)
#define swp(x, y) { const int a = min(arr[x], arr[y]); \
                    const int b = max(arr[x], arr[y]); \
                    arr[x] = a; arr[y] = b; }

inline void sort_net_3(int *arr)
{
	swp(1, 2); swp(0, 2); swp(0, 1);
}

inline void sort_net_4(int *arr)
{
	swp(0, 1); swp(2, 3); swp(0, 2); swp(1, 3); swp(1, 2);
}

inline void sort_net_5(int *arr)
{
	swp(0, 1); swp(3, 4); swp(2, 3); swp(1, 4);
	swp(0, 3); swp(0, 2); swp(1, 3); swp(1, 2);
}

inline void sort_net_6(int *arr)
{
	swp(1, 2); swp(4, 5); swp(0, 2); swp(3, 5); swp(0, 1); swp(3, 4);
	swp(2, 5); swp(0, 3); swp(1, 4); swp(2, 4); swp(1, 3); swp(2, 3);
}

#undef min
#undef max
#undef swp

/* The mixing step */
#define mix32(a, b, c)							    \
{									    \
	a -= b;  a -= c;  a ^= (c >> 13); b -= c;  b -= a;  b ^= (a <<  8); \
	c -= a;  c -= b;  c ^= (b >> 13); a -= b;  a -= c;  a ^= (c >> 12); \
	b -= c;  b -= a;  b ^= (a << 16); c -= a;  c -= b;  c ^= (b >>  5); \
	a -= b;  a -= c;  a ^= (c >>  3); b -= c;  b -= a;  b ^= (a << 10); \
	c -= a;  c -= b;  c ^= (b >> 15);				    \
}

inline uint32_t jhash32(register unsigned char *k,    /* the key */
			register const size_t length, /* length of the key in bytes */
			register uint32_t init_val)   /* prev hash or arb val */
{
	register uint32_t a, b, c; /* the internal state */
	register size_t len;	   /* how many key bytes still need mixing */

	/* Set up the internal state */
	a = b = 0x9e3779b9; /* the golden ratio; an arbitrary value */
	c = init_val;       /* variable initialization of internal state */

	/*---------------------------------------- handle most of the key */
	for (len = length; len >= 12; k += 12, len -= 12) {

		a += (k[0]			 + ((uint32_t) k[ 1] <<  8)
		      + ((uint32_t) k[ 2] << 16) + ((uint32_t) k[ 3] << 24));

		b += (k[4]			 + ((uint32_t) k[ 5] <<  8)
		      + ((uint32_t) k[ 6] << 16) + ((uint32_t) k[ 7] << 24));

		c += (k[8]			 + ((uint32_t) k[ 9] <<  8)
		      + ((uint32_t) k[10] << 16) + ((uint32_t) k[11] << 24));

		mix32(a, b, c);
	}

	/*------------------------------------- handle the last 11 bytes */
	c += length;

	switch (len) {
		/* all the case statements fall through */
		case 11: c += ((uint32_t) k[10] << 24);
		case 10: c += ((uint32_t) k[ 9] << 16);
		case  9: c += ((uint32_t) k[ 8] <<  8);
		/* the first byte of c is reserved for the length */
		case  8: b += ((uint32_t) k[ 7] << 24);
		case  7: b += ((uint32_t) k[ 6] << 16);
		case  6: b += ((uint32_t) k[ 5] <<  8);
		case  5: b += ((uint32_t) k[ 4]	     );
		case  4: a += ((uint32_t) k[ 3] << 24);
		case  3: a += ((uint32_t) k[ 2] << 16);
		case  2: a += ((uint32_t) k[ 1] <<  8);
		case  1: a += ((uint32_t) k[ 0]	     );
		/* case 0: nothing left  to add */
	}

	mix32(a, b, c);

	/*-------------------------------------------- report the result */
	return c;
}
#undef mix32

/* The mixing step */
#define mix64(a, b, c)							    \
{									    \
	a -= b;  a -= c;  a ^= (c >> 43); b -= c;  b -= a;  b ^= (a <<  9); \
	c -= a;  c -= b;  c ^= (b >>  8); a -= b;  a -= c;  a ^= (c >> 38); \
	b -= c;  b -= a;  b ^= (a << 23); c -= a;  c -= b;  c ^= (b >>  5); \
	a -= b;  a -= c;  a ^= (c >> 35); b -= c;  b -= a;  b ^= (a << 49); \
	c -= a;  c -= b;  c ^= (b >> 11); a -= b;  a -= c;  a ^= (c >> 12); \
	b -= c;  b -= a;  b ^= (a << 18); c -= a;  c -= b;  c ^= (b >> 22); \
}

inline uint64_t jhash64(register unsigned char *k,    /* the key */
			register const size_t length, /* num bytes of key */
			register uint64_t level)	    /* prev hash or arb val */
{
	register uint64_t a, b, c; /* the internal state */
	register size_t len;	   /* how many key bytes still need mixing */

	/* Set up the internal state */
	a = b = level;		  /* variable initialization of internal state */
	c = 0x9e3779b97f4a7c13LL; /* the golden ratio; an arbitrary value */

	/*---------------------------------------- handle most of the key */
	for (len = length; len >= 24; k += 24, len -= 24) {

		a += (k[ 0]			 + ((uint64_t) k[ 1] <<  8)
		      + ((uint64_t) k[ 2] << 16) + ((uint64_t) k[ 3] << 24)
		      + ((uint64_t) k[ 4] << 32) + ((uint64_t) k[ 5] << 40)
		      + ((uint64_t) k[ 6] << 48) + ((uint64_t) k[ 7] << 56));

		b += (k[ 8]			 + ((uint64_t) k[ 9] <<  8)
		      + ((uint64_t) k[10] << 16) + ((uint64_t) k[11] << 24)
		      + ((uint64_t) k[12] << 32) + ((uint64_t) k[13] << 40)
		      + ((uint64_t) k[14] << 48) + ((uint64_t) k[15] << 56));

		c += (k[16]			 + ((uint64_t) k[17] <<  8)
		      + ((uint64_t) k[18] << 16) + ((uint64_t) k[19] << 24)
		      + ((uint64_t) k[20] << 32) + ((uint64_t) k[21] << 40)
		      + ((uint64_t) k[22] << 48) + ((uint64_t) k[23] << 56));

		mix64(a, b, c);
	}

	/*------------------------------------- handle the last 23 bytes */
	c += length;

	switch (len) {
		/* all the case statements fall through */
		case 23: c += ((uint64_t) k[22] << 56);
		case 22: c += ((uint64_t) k[21] << 48);
		case 21: c += ((uint64_t) k[20] << 40);
		case 20: c += ((uint64_t) k[19] << 32);
		case 19: c += ((uint64_t) k[18] << 24);
		case 18: c += ((uint64_t) k[17] << 16);
		case 17: c += ((uint64_t) k[16] <<  8);
		/* the first byte of c is reserved for the length */
		case 16: b += ((uint64_t) k[15] << 56);
		case 15: b += ((uint64_t) k[14] << 48);
		case 14: b += ((uint64_t) k[13] << 40);
		case 13: b += ((uint64_t) k[12] << 32);
		case 12: b += ((uint64_t) k[11] << 24);
		case 11: b += ((uint64_t) k[10] << 16);
		case 10: b += ((uint64_t) k[ 9] <<  8);
		case  9: b += ((uint64_t) k[ 8]	     );
		case  8: a += ((uint64_t) k[ 7] << 56);
		case  7: a += ((uint64_t) k[ 6] << 48);
		case  6: a += ((uint64_t) k[ 5] << 40);
		case  5: a += ((uint64_t) k[ 4] << 32);
		case  4: a += ((uint64_t) k[ 3] << 24);
		case  3: a += ((uint64_t) k[ 2] << 16);
		case  2: a += ((uint64_t) k[ 1] <<  8);
		case  1: a += ((uint64_t) k[ 0]	     );
		/* case 0: nothing left to add */
	}

	mix64(a, b, c);

	/*-------------------------------------------- report the result */
	return c;
}

inline uint64_t jhash64_2(register unsigned char *k,    /* the key */
			  register const size_t length, /* num bytes of key */
			  register uint64_t level)	/* prev hash or arb val */
{
	register uint64_t a, b, c; /* the internal state */
	register size_t len;	   /* how many key bytes still need mixing */

	/* Set up the internal state */
	a = b = level;		  /* variable initialization of internal state */
	c = 0x9e3779b97f4a7c13LL; /* the golden ratio; an arbitrary value */

	for (len = length; len >= 3; k += 3, len -= 3) {

		a += k[0]; b += k[1]; c += k[2];

		mix64(a, b, c);
	}

	c += (length << 3);

	switch (len) {
		/* all the case statements fall through */
		/* c is reserved for the length */
		case 2: b += k[1];
		case 1: a += k[0];
		/* case 0: nothing left to add */
	}

	mix64(a, b, c);

	/*-------------------------------------------- report the result */
	return c;
}
#undef mix64

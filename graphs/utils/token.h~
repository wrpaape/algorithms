#ifndef _GRAPHS_UTILS_TOKEN_H_
#define _GRAPHS_UTILS_TOKEN_H_

/*			- token.h -
 * macros for printing multi-byte characters to char pointer 'PTR'
 */

#define PUT_CHAR(PTR, BYTE)	\
do {				\
	*PTR = BYTE;		\
	++PTR;			\
} while (0)

#define PUT_SPACE(PTR) PUT_CHAR(' ')


/* ANSI ESCAPE SEQUENCES
 ******************************************************************************/
#define OPEN_ANSI(PTR)		\
do {				\
	PUT_CHAR(PTR, 27);	\
	PUT_CHAR(PTR, 91);	\
} while (0)


#define CLOSE_ANSI(PTR) PUT_CHAR(PTR, 109)


#define SML_ANSI(PTR, B2)	\
do {				\
	OPEN_ANSI(PTR);		\
	PUT_CHAR(PTR, B2);	\
	CLOSE_ANSI(PTR);	\
} while (0)


#define BIG_ANSI(PTR, B2, B3)	\
do {				\
	OPEN_ANSI(PTR);		\
	PUT_CHAR(PTR, B2);	\
	PUT_CHAR(PTR, B3);	\
	CLOSE_ANSI(PTR);	\
} while (0)

/* 4 bytes */

#define ANSI_FAINT "\e[2m"
#define ANSI_BRIGHT "\e[1m"
#define ANSI_RESET "\e[0m"

#define PUT_ANSI_RESET(PTR) SML_ANSI(PTR, 48)

#define PUT_ANSI_BRIGHT(PTR) SML_ANSI(PTR, 49)

#define PUT_ANSI_FAINT(PTR) SML_ANSI(PTR, 50)

/* 5 bytes */
#define ANSI_NORMAl "\e[22m"
#define ANSI_WHITE_BG "\e[47m"
#define ANSI_BLACK_BG "\e[40m"
#define ANSI_WHITE "\e[37m"
#define ANSI_BLUE "\e[34m"
#define ANSI_CYAN "\e[36m"
#define ANSI_GREEN "\e[32m"
#define ANSI_YELLOW "\e[33m"
#define ANSI_RED "\e[31m"
#define ANSI_MAGENTA "\e[35m"
#define ANSI_BLACK "\e[30m"

#define PUT_ANSI_NORMAl(PTR) BIG_ANSI(PTR, 50, 50)
#define PUT_ANSI_WHITE_BG(PTR) BIG_ANSI(PTR, 52, 53)
#define PUT_ANSI_BLACK_BG(PTR) BIG_ANSI(PTR, 52, 48)
#define PUT_ANSI_WHITE(PTR) BIG_ANSI(PTR, 51, 55)
#define PUT_ANSI_BLUE(PTR) BIG_ANSI(PTR, 51, 52)
#define PUT_ANSI_CYAN(PTR) BIG_ANSI(PTR, 51, 54)
#define PUT_ANSI_GREEN(PTR) BIG_ANSI(PTR, 51, 50)
#define PUT_ANSI_YELLOW(PTR) BIG_ANSI(PTR, 51, 51)
#define PUT_ANSI_RED(PTR) BIG_ANSI(PTR, 51, 49)
#define PUT_ANSI_MAGENTA(PTR) BIG_ANSI(PTR, 51, 53)
#define PUT_ANSI_BLACK(PTR) BIG_ANSI(PTR, 51, 48)

/* #undef OPEN_ANSI */
/* #undef CLOSE_ANSI */
/* #undef SML_ANSI */
/* #undef BIG_ANSI */



/* BOX DRAWING CHARACTERS
 ******************************************************************************/
#define BOX_CHAR_SIZE 3lu

#define SGL_BOX_CHAR(PTR, BYTE)	\
do {				\
	PUT_CHAR(PTR, 226);	\
	PUT_CHAR(PTR, 148);	\
	PUT_CHAR(PTR, BYTE);	\
} while (0)

#define DBL_BOX_CHAR(PTR, BYTE)	\
do {				\
	PUT_CHAR(PTR, 226);	\
	PUT_CHAR(PTR, 149);	\
	PUT_CHAR(PTR, BYTE);	\
} while (0)

/* light */
#define PUT_BOX_CHAR_LIGHT_NW_CORNER(PTR) SGL_BOX_CHAR(PTR, 140)  /* ┌ */
#define PUT_BOX_CHAR_LIGHT_NE_CORNER(PTR) SGL_BOX_CHAR(PTR, 144)  /* ┐ */
#define PUT_BOX_CHAR_LIGHT_SW_CORNER(PTR) SGL_BOX_CHAR(PTR, 148)  /* └ */
#define PUT_BOX_CHAR_LIGHT_SE_CORNER(PTR) SGL_BOX_CHAR(PTR, 152)  /* ┘ */
#define PUT_BOX_CHAR_LIGHT_N_JOIN(PTR) SGL_BOX_CHAR(PTR, 172)	  /* ┬ */
#define PUT_BOX_CHAR_LIGHT_S_JOIN(PTR) SGL_BOX_CHAR(PTR, 180)	  /* ┴ */
#define PUT_BOX_CHAR_LIGHT_W_JOIN(PTR) SGL_BOX_CHAR(PTR, 156)	  /* ├ */
#define PUT_BOX_CHAR_LIGHT_E_JOIN(PTR) SGL_BOX_CHAR(PTR, 164)	  /* ┤ */
#define PUT_BOX_CHAR_LIGHT_H_LINE(PTR) SGL_BOX_CHAR(PTR, 128)	  /* ─ */
#define PUT_BOX_CHAR_LIGHT_V_LINE(PTR) SGL_BOX_CHAR(PTR, 130)	  /* │ */
#define PUT_BOX_CHAR_LIGHT_CROSS(PTR) SGL_BOX_CHAR(PTR, 188)	  /* ┼ */

/* heavy */
#define PUT_BOX_CHAR_HEAVY_NW_CORNER(PTR) SGL_BOX_CHAR(PTR, 143)  /* ┏ */
#define PUT_BOX_CHAR_HEAVY_NE_CORNER(PTR) SGL_BOX_CHAR(PTR, 147)  /* ┓ */
#define PUT_BOX_CHAR_HEAVY_SW_CORNER(PTR) SGL_BOX_CHAR(PTR, 151)  /* ┗ */
#define PUT_BOX_CHAR_HEAVY_SE_CORNER(PTR) SGL_BOX_CHAR(PTR, 155)  /* ┛ */
#define PUT_BOX_CHAR_HEAVY_N_JOIN(PTR) SGL_BOX_CHAR(PTR, 179)	  /* ┳ */
#define PUT_BOX_CHAR_HEAVY_S_JOIN(PTR) SGL_BOX_CHAR(PTR, 187)	  /* ┻ */
#define PUT_BOX_CHAR_HEAVY_W_JOIN(PTR) SGL_BOX_CHAR(PTR, 163)	  /* ┣ */
#define PUT_BOX_CHAR_HEAVY_E_JOIN(PTR) SGL_BOX_CHAR(PTR, 171)	  /* ┫ */
#define PUT_BOX_CHAR_HEAVY_H_LINE(PTR) SGL_BOX_CHAR(PTR, 129)	  /* ━ */
#define PUT_BOX_CHAR_HEAVY_V_LINE(PTR) SGL_BOX_CHAR(PTR, 131)	  /* ┃ */
#define PUT_BOX_CHAR_HEAVY_CROSS(PTR) SGL_BOX_CHAR(PTR, 139)	  /* ╋ */

/* double */
#define PUT_BOX_CHAR_DOUBLE_NW_CORNER(PTR) DBL_BOX_CHAR(PTR, 148)  /* ╔ */
#define PUT_BOX_CHAR_DOUBLE_NE_CORNER(PTR) DBL_BOX_CHAR(PTR, 151)  /* ╗ */
#define PUT_BOX_CHAR_DOUBLE_SW_CORNER(PTR) DBL_BOX_CHAR(PTR, 154)  /* ╚ */
#define PUT_BOX_CHAR_DOUBLE_SE_CORNER(PTR) DBL_BOX_CHAR(PTR, 157)  /* ╝ */
#define PUT_BOX_CHAR_DOUBLE_N_JOIN(PTR) DBL_BOX_CHAR(PTR, 166)	   /* ╦ */
#define PUT_BOX_CHAR_DOUBLE_S_JOIN(PTR) DBL_BOX_CHAR(PTR, 169)	   /* ╩ */
#define PUT_BOX_CHAR_DOUBLE_W_JOIN(PTR) DBL_BOX_CHAR(PTR, 160)	   /* ╠ */
#define PUT_BOX_CHAR_DOUBLE_E_JOIN(PTR) DBL_BOX_CHAR(PTR, 163)	   /* ╣ */
#define PUT_BOX_CHAR_DOUBLE_H_LINE(PTR) DBL_BOX_CHAR(PTR, 144)	   /* ═ */
#define PUT_BOX_CHAR_DOUBLE_V_LINE(PTR) DBL_BOX_CHAR(PTR, 145)	   /* ║ */
#define PUT_BOX_CHAR_DOUBLE_CROSS(PTR) DBL_BOX_CHAR(PTR, 172)	   /* ╬ */

/* #undef SGL_BOX_CHAR */
/* #undef DBL_BOX_CHAR */



/* BLOCK ELEMENTS
 ******************************************************************************/
#define BLOCK_CHAR_SIZE 3lu

#define FILL_BLOCK_CHAR(PTR, BYTE)	\
do {					\
	PUT_CHAR(PTR, 226);		\
	PUT_CHAR(PTR, 150);		\
	PUT_CHAR(PTR, BYTE);		\
} while (0)

/* filled from bottom:
 * ▁ ▂ ▃ ▄ ▅ ▆ ▇ █
 * 1 2 3 4 5 6 7 8 */
#define PUT_BLOCK_CHAR_BASE_FILL(PTR, FILL) FILL_BLOCK_CHAR(PTR, 128 + (FILL))

/* filled from left:
 * ▏ ▎ ▍ ▌ ▋ ▊ ▉ █
 * 1 2 3 4 5 6 7 8 */
#define PUT_BLOCK_CHAR_LEFT_FILL(PTR, FILL) FILL_BLOCK_CHAR(PTR, 128 + (FILL))

/* #undef FILL_BLOCK_CHAR */
#endif /* ifndef _GRAPHS_UTILS_TOKEN_H_ */

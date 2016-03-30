#ifndef _GRAPHS_UTILS_TOKEN_H_
#define _GRAPHS_UTILS_TOKEN_H_

#define PUT_CHAR(PTR, BYTE)						\
do {									\
	*PTR = BYTE;							\
	++PTR;								\
} while (0)


#define PUT_UNIBLOCK(PTR, EIGHTHS)					\
do {									\
	PUT_CHAR(PTR, 226);						\
	PUT_CHAR(PTR, 150);						\
	PUT_CHAR(PTR, 128 + EIGHTHS);					\
} while (0)

#define PUT_SML_ANSI(PTR, B2)						\
do {									\
	PUT_CHAR(PTR, 27);						\
	PUT_CHAR(PTR, 97);						\
	PUT_CHAR(PTR, B2);						\
	PUT_CHAR(PTR, 109);						\
} while (0)

#define PUT_BIG_ANSI(PTR, B2, B3)					\
do {									\
	PUT_CHAR(PTR, 27);						\
	PUT_CHAR(PTR, 97);						\
	PUT_CHAR(PTR, B2);						\
	PUT_CHAR(PTR, B3);						\
	PUT_CHAR(PTR, 109);						\
} while (0)

#define PUT_BOX_CHAR_SINGLE(PTR, BYTE)					\
do {									\
	PUT_CHAR(PTR, 226);						\
	PUT_CHAR(PTR, 148);						\
	PUT_CHAR(PTR, BYTE);						\
} while (0)

#define PUT_BOX_CHAR_DOUBLE(PTR, BYTE)					\
do {									\
	PUT_CHAR(PTR, 226);						\
	PUT_CHAR(PTR, 149);						\
	PUT_CHAR(PTR, BYTE);						\
} while (0)

#define PUT_ANSI_RESET(PTR) PUT_SML_ANSI(PTR, 48)
#define PUT_ANSI_BRIGHT(PTR) PUT_SML_ANSI(PTR, 49)
#define PUT_ANSI_FAINT(PTR) PUT_SML_ANSI(PTR, 50)

#define PUT_ANSI_NORMAl(PTR) PUT_BIG_ANSI(PTR, 50, 50)
#define PUT_ANSI_WHITE_BG(PTR) PUT_BIG_ANSI(PTR, 52, 53)
#define PUT_ANSI_BLACK_BG(PTR) PUT_BIG_ANSI(PTR, 52, 48)
#define PUT_ANSI_WHITE(PTR) PUT_BIG_ANSI(PTR, 51, 55)
#define PUT_ANSI_BLUE(PTR) PUT_BIG_ANSI(PTR, 51, 52)
#define PUT_ANSI_CYAN(PTR) PUT_BIG_ANSI(PTR, 51, 54)
#define PUT_ANSI_GREEN(PTR) PUT_BIG_ANSI(PTR, 51, 50)
#define PUT_ANSI_YELLOW(PTR) PUT_BIG_ANSI(PTR, 51, 51)
#define PUT_ANSI_RED(PTR) PUT_BIG_ANSI(PTR, 51, 49)
#define PUT_ANSI_MAGENTA(PTR) PUT_BIG_ANSI(PTR, 51, 53)
#define PUT_ANSI_BLACK(PTR) PUT_BIG_ANSI(PTR, 51, 48)


/* 4 bytes */
#define FAINT "\e[2m"
#define BRIGHT "\e[1m"
#define RESET "\e[0m"

/* 5 bytes */
#define NORMAl "\e[22m"
#define WHITE_BG "\e[47m"
#define BLACK_BG "\e[40m"
#define WHITE "\e[37m"
#define BLUE "\e[34m"
#define CYAN "\e[36m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define RED "\e[31m"
#define MAGENTA "\e[35m"
#define BLACK "\e[30m"

/* ┏: , <<226, 148, 143>> */
/* ┳: , <<226, 148, 179>> */
/* ┓: , <<226, 148, 147>> */
/* ┣: , <<226, 148, 163>> */
/* ╋: , <<226, 149, 139>> */
/* ┫: , <<226, 148, 171>> */
/* ┗: , <<226, 148, 151>> */
/* ┻: , <<226, 148, 187>> */
/* ┛: , <<226, 148, 155>> */
/* ━: , <<226, 148, 129>> */
/* ┃: , <<226, 148, 131>> */

/* BOX DRAWING CHARACTERS
 ******************************************************************************/

/* light */
#define PUT_BOX_CHAR_LIGHT_NW_CORNER(PTR) PUT_BOX_CHAR_SINGLE(PTR, 140)	 /* ┌ */
#define PUT_BOX_CHAR_LIGHT_NE_CORNER(PTR) PUT_BOX_CHAR_SINGLE(PTR, 144)	 /* ┐ */
#define PUT_BOX_CHAR_LIGHT_SW_CORNER(PTR) PUT_BOX_CHAR_SINGLE(PTR, 148)	 /* └ */
#define PUT_BOX_CHAR_LIGHT_SE_CORNER(PTR) PUT_BOX_CHAR_SINGLE(PTR, 152)	 /* ┘ */
#define PUT_BOX_CHAR_LIGHT_N_JOIN(PTR) PUT_BOX_CHAR_SINGLE(PTR, 172)     /* ┬ */
#define PUT_BOX_CHAR_LIGHT_S_JOIN(PTR) PUT_BOX_CHAR_SINGLE(PTR, 180)     /* ┴ */
#define PUT_BOX_CHAR_LIGHT_W_JOIN(PTR) PUT_BOX_CHAR_SINGLE(PTR, 156)     /* ├ */
#define PUT_BOX_CHAR_LIGHT_E_JOIN(PTR) PUT_BOX_CHAR_SINGLE(PTR, 164)     /* ┤ */
#define PUT_BOX_CHAR_LIGHT_H_LINE(PTR) PUT_BOX_CHAR_SINGLE(PTR, 128)     /* ─ */
#define PUT_BOX_CHAR_LIGHT_V_LINE(PTR) PUT_BOX_CHAR_SINGLE(PTR, 130)     /* │ */
#define PUT_BOX_CHAR_LIGHT_CROSS(PTR) PUT_BOX_CHAR_SINGLE(PTR, 188)      /* ┼ */

/* heavy */
#define PUT_BOX_CHAR_HEAVY_NW_CORNER(PTR) PUT_BOX_CHAR_SINGLE(PTR, 143)	 /* ┏ */
#define PUT_BOX_CHAR_HEAVY_NE_CORNER(PTR) PUT_BOX_CHAR_SINGLE(PTR, 147)	 /* ┓ */
#define PUT_BOX_CHAR_HEAVY_SW_CORNER(PTR) PUT_BOX_CHAR_SINGLE(PTR, 151)	 /* ┗ */
#define PUT_BOX_CHAR_HEAVY_SE_CORNER(PTR) PUT_BOX_CHAR_SINGLE(PTR, 155)	 /* ┛ */
#define PUT_BOX_CHAR_HEAVY_N_JOIN(PTR) PUT_BOX_CHAR_SINGLE(PTR, 179)	 /* ┳ */
#define PUT_BOX_CHAR_HEAVY_S_JOIN(PTR) PUT_BOX_CHAR_SINGLE(PTR, 187)	 /* ┻ */
#define PUT_BOX_CHAR_HEAVY_W_JOIN(PTR) PUT_BOX_CHAR_SINGLE(PTR, 163)	 /* ┣ */
#define PUT_BOX_CHAR_HEAVY_E_JOIN(PTR) PUT_BOX_CHAR_SINGLE(PTR, 171)	 /* ┫ */
#define PUT_BOX_CHAR_HEAVY_H_LINE(PTR) PUT_BOX_CHAR_SINGLE(PTR, 129)	 /* ━ */
#define PUT_BOX_CHAR_HEAVY_V_LINE(PTR) PUT_BOX_CHAR_SINGLE(PTR, 131)	 /* ┃ */
#define PUT_BOX_CHAR_HEAVY_CROSS(PTR) PUT_BOX_CHAR_SINGLE(PTR, 139)	 /* ╋ */

/* double */
#define PUT_BOX_CHAR_HEAVY_NW_CORNER(PTR) PUT_BOX_CHAR_SINGLE(PTR, 143)	 /* ┏ */
#define PUT_BOX_CHAR_HEAVY_NE_CORNER(PTR) PUT_BOX_CHAR_SINGLE(PTR, 147)	 /* ┓ */
#define PUT_BOX_CHAR_HEAVY_SW_CORNER(PTR) PUT_BOX_CHAR_SINGLE(PTR, 151)	 /* ┗ */
#define PUT_BOX_CHAR_HEAVY_SE_CORNER(PTR) PUT_BOX_CHAR_SINGLE(PTR, 155)	 /* ┛ */
#define PUT_BOX_CHAR_HEAVY_N_JOIN(PTR) PUT_BOX_CHAR_SINGLE(PTR, 179)	 /* ┳ */
#define PUT_BOX_CHAR_HEAVY_S_JOIN(PTR) PUT_BOX_CHAR_SINGLE(PTR, 187)	 /* ┻ */
#define PUT_BOX_CHAR_HEAVY_W_JOIN(PTR) PUT_BOX_CHAR_SINGLE(PTR, 163)	 /* ┣ */
#define PUT_BOX_CHAR_HEAVY_E_JOIN(PTR) PUT_BOX_CHAR_SINGLE(PTR, 171)	 /* ┫ */
#define PUT_BOX_CHAR_HEAVY_H_LINE(PTR) PUT_BOX_CHAR_SINGLE(PTR, 129)	 /* ━ */
#define PUT_BOX_CHAR_HEAVY_V_LINE(PTR) PUT_BOX_CHAR_SINGLE(PTR, 131)	 /* ┃ */
#define PUT_BOX_CHAR_HEAVY_CROSS(PTR) PUT_BOX_CHAR_SINGLE(PTR, 139)	 /* ╋ */

╔: , <<226, 149, 148>>
╦: , <<226, 149, 166>>
╗: , <<226, 149, 151>>
╠: , <<226, 149, 160>>
╬: , <<226, 149, 172>>
╣: , <<226, 149, 163>>
╚: , <<226, 149, 154>>
╩: , <<226, 149, 169>>
╝: , <<226, 149, 157>>
|: , <<124>>
═: , <<226, 149, 144>>
║: , <<226, 149, 145>>
┏: , <<226, 148, 143>>
┳: , <<226, 148, 179>>
┓: , <<226, 148, 147>>
┣: , <<226, 148, 163>>
╋: , <<226, 149, 139>>
┫: , <<226, 148, 171>>
┗: , <<226, 148, 151>>
┻: , <<226, 148, 187>>
┛: , <<226, 148, 155>>
━: , <<226, 148, 129>>
┃: , <<226, 148, 131>>
#endif /* ifndef _GRAPHS_UTILS_TOKEN_H_
 */

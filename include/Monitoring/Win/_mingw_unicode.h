1	/**
2	 * This file has no copyright assigned and is placed in the Public Domain.
3	 * This file is part of the w64 mingw-runtime package.
4	 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
5	 */
6
7	#if !defined(_INC_CRT_UNICODE_MACROS)
8	/* _INC_CRT_UNICODE_MACROS defined based on UNICODE flag */
9
10	#if defined(UNICODE)
11	# define _INC_CRT_UNICODE_MACROS 1
12	# define __MINGW_NAME_AW(func) func##W
13	# define __MINGW_NAME_AW_EXT(func,ext) func##W##ext
14	# define __MINGW_NAME_UAW(func) func##_W
15	# define __MINGW_NAME_UAW_EXT(func,ext) func##_W_##ext
16	# define __MINGW_STRING_AW(str) L##str  /* same as TEXT() from winnt.h */
17	# define __MINGW_PROCNAMEEXT_AW "W"
18	#else
19	# define _INC_CRT_UNICODE_MACROS 2
20	# define __MINGW_NAME_AW(func) func##A
21	# define __MINGW_NAME_AW_EXT(func,ext) func##A##ext
22	# define __MINGW_NAME_UAW(func) func##_A
23	# define __MINGW_NAME_UAW_EXT(func,ext) func##_A_##ext
24	# define __MINGW_STRING_AW(str) str     /* same as TEXT() from winnt.h */
25	# define __MINGW_PROCNAMEEXT_AW "A"
26	#endif
27
28	#define __MINGW_TYPEDEF_AW(type)        \
29	    typedef __MINGW_NAME_AW(type) type;
30	#define __MINGW_TYPEDEF_UAW(type)       \
31	    typedef __MINGW_NAME_UAW(type) type;
32
33	#endif /* !defined(_INC_CRT_UNICODE_MACROS) */

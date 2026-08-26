/*** defines ***/
//RWX_VERSION can be max 12 characters long
#define RWX_VERSION "1.0.0"

//Tabs must be power of 2 (2,4 or 8)
#define TAB_STOP      2
#define QUIT_TIMES    1
#define SIZE_LIMIT 1024

#define FG_BLACK   30
#define FG_RED     31
#define FG_GREEN   32
#define FG_YELLOW  33
#define FG_BLUE    34
#define FG_MAGENTA 35
#define FG_CYAN    36
#define FG_WHITE   37
#define BG_BLACK   40
#define BG_RED     41
#define BG_GREEN   42
#define BG_YELLOW  43
#define BG_BLUE    44
#define BG_MAGENTA 45
#define BG_CYAN    46
#define BG_WHITE   47

#define DEFAULT_SYNTAX_COLOR   FG_BLACK
#define COMMENT_SYNTAX_COLOR   FG_GREEN
#define KEYWORD_1_SYNTAX_COLOR FG_BLUE
#define KEYWORD_2_SYNTAX_COLOR FG_MAGENTA
#define KEYWORD_3_SYNTAX_COLOR FG_RED
#define STRING_SYNTAX_COLOR    FG_BLUE
#define NUMBER_SYNTAX_COLOR    FG_BLUE
#define MATCH_SYNTAX_COLOR     FG_RED

#define DEFAULT_MSG_COLOR FG_BLACK
#define ACTION_MSG_COLOR  FG_MAGENTA
#define SUCCESS_MSG_COLOR FG_BLUE
#define ERROR_MSG_COLOR   FG_RED
#define HELP_MSG_COLOR    FG_BLACK

#define FG_STATUS_COLOR       FG_BLUE
#define BG_STATUS_COLOR       BG_WHITE
#define FG_LINE_NUM_COLOR     FG_BLUE
#define BG_LINE_NUM_COLOR     BG_WHITE
#define FG_CTRL_AND_HEX_COLOR FG_BLUE
#define BG_CTRL_AND_HEX_COLOR BG_WHITE

#define FG_NORMAL_MODE_COLOR FG_BLACK
#define BG_NORMAL_MODE_COLOR BG_GREEN
#define FG_INSERT_MODE_COLOR FG_BLACK
#define BG_INSERT_MODE_COLOR BG_MAGENTA
#define FG_VISUAL_MODE_COLOR FG_BLACK
#define BG_VISUAL_MODE_COLOR BG_YELLOW

#define FG_PATH_COLOR      FG_BLUE
#define BG_PATH_COLOR      BG_WHITE
#define FG_SHORTCUT_COLOR  FG_BLUE
#define BG_SHORTCUT_COLOR  BG_WHITE
#define FG_NOTICE_COLOR    FG_BLACK
#define BG_NOTICE_COLOR    BG_WHITE
#define FG_ERROR_COLOR     FG_RED
#define BG_ERROR_COLOR     BG_WHITE
#define FG_SELECTED_COLOR  FG_BLUE
#define BG_SELECTED_COLOR  BG_WHITE

#define BACKSPACE           127
#define RESIZE_KEY         1000
#define ARROW_UP           1001
#define ARROW_DOWN         1002
#define ARROW_RIGHT        1003
#define ARROW_LEFT         1004
#define DEL_KEY            1005
#define INSERT_KEY         1006
#define HOME_KEY           1007
#define END_KEY            1008
#define PAGE_UP            1009
#define PAGE_DOWN          1010
#define MOUSE_WHEEL_UP     1011
#define MOUSE_WHEEL_DOWN   1012
#define MOUSE_LEFT_PRESS   1013
#define MOUSE_LEFT_DRAG    1014
#define MOUSE_LEFT_RELEASE 1015
#define MOUSE_MIDDLE_CLICK 1016
#define MOUSE_RIGHT_PRESS  1017
#define BRACKETED_PASTE    1018

#define H_NORMAL    0
#define H_COMMENT   1
#define H_M_COMMENT 2
#define H_KEYWORD_1 3
#define H_KEYWORD_2 4
#define H_KEYWORD_3 5
#define H_STRING    6
#define H_NUMBER    7
#define H_MATCH     8
#define H_CTRL      9
#define H_HEX      10

#define MODE_NORMAL 0
#define MODE_INSERT 1

#define SELECT_NONE 0
#define SELECT_CHAR 1
#define SELECT_ROW  2

#define USER_ACTION_INSERT_CHAR    0
#define USER_ACTION_DEL_CHAR       1
#define USER_ACTION_INSERT_NEWLINE 2
#define USER_ACTION_JOIN_LINES     3
#define USER_ACTION_ROW_INSERT     4
#define USER_ACTION_ROW_DELETE     5
#define USER_ACTION_RANGE_INSERT   6
#define USER_ACTION_RANGE_DELETE   7

#define ASCII_CHAR_LIMIT 128

#define KB(n) ((uint64_t)(n) << 10)
#define MB(n) ((uint64_t)(n) << 20)
#define GB(n) ((uint64_t)(n) << 30)

#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

#define ALIGN_UP_POW_OF_2(n,p) (((uint64_t)(n)+((uint64_t)(p)-1)) & (~((uint64_t)(p)-1)))
#define ARENA_BASE_POS (sizeof(mem_arena))
#define ARENA_ALIGN (sizeof(void*))
#define ROW_ARENA_COMPACT_THRESHOLD ((uint64_t)(128*1024))
#define ROW_RENDER_MAX_EXPANSION (TAB_STOP > 6 ? TAB_STOP : 6)

#define CTRL_KEY(k) ((k) & 0x1f)

#define BROWSE_FLAG_SHOW_HIDDEN (1 << 0)
#define BROWSE_FLAG_LONG_FORMAT (1 << 1)

#ifdef _WIN32
 #ifndef _WIN32_WINNT
  #define _WIN32_WINNT 0x0A00
 #endif
 #ifndef WINVER
  #define WINVER 0x0A00
 #endif
#else
 #define _DEFAULT_SOURCE
#endif

#ifndef _POSIX_C_SOURCE
 #define _POSIX_C_SOURCE 200809L
#endif

#ifdef __MINGW32__
 #define __USE_MINGW_ANSI_STDIO 1
#endif

/*** includes ***/
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdarg.h>
#include<string.h>
#include<signal.h>
#include<errno.h>
#include<ctype.h>
#include<time.h>
#include<fcntl.h>
#include<sys/types.h>
#include<inttypes.h>

#ifdef _WIN32
 #include<windows.h>
 #include<io.h>
 #ifndef _WIN32_WINNT_WIN10
  WINBOOL WINAPI SetConsoleInputCP(UINT wCodePageID);
  ULONGLONG WINAPI GetTickCount64(void);
 #endif
 #define STDIN_FILENO  0
 #define STDOUT_FILENO 1
 #define write _write
 #define open _open
 #define close _close
 #define ftruncate _chsize
 #define strdup _strdup

 #ifndef _SSIZE_T_DEFINED
  typedef intptr_t ssize_t;
  #define _SSIZE_T_DEFINED
 #endif

 #ifndef CP_UTF8
  #define CP_UTF8 65001
 #endif

 #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
  #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
 #endif
#else
 #include<termios.h>
 #include<unistd.h>
 #include<dirent.h>
 #include<pwd.h>
 #include<grp.h>
 #include<locale.h>
 #include<langinfo.h>
 #include<sys/ioctl.h>
 #include<sys/stat.h>
 #include<sys/mman.h>
#endif

/*** file types and keywords ***/
const char* const C_H_extensions[]={".c",".h",".i",NULL};
const char* const C_H_keywords[]=
{
 "%:%:","%:","<%","%>","<:",":>","?\?<","?\?>","?\?(","?\?)","?\?!","?\?'","?\?-","?\?/","?\?=",
 "_Alignas","alignas","_Alignof","alignof","asm","__asm","__asm__","_Atomic","__alignas_is_defined","__alignof_is_defined",
 "atomic_bool","atomic_char","atomic_char16_t","atomic_char32_t",
 "ATOMIC_BOOL_LOCK_FREE","ATOMIC_CHAR_LOCK_FREE","ATOMIC_CHAR8_T_LOCK_FREE","ATOMIC_CHAR16_T_LOCK_FREE","ATOMIC_CHAR32_T_LOCK_FREE",
 "atomic_compare_exchange_strong","atomic_compare_exchange_strong_explicit","atomic_compare_exchange_weak",
 "atomic_compare_exchange_weak_explicit","atomic_exchange","atomic_exchange_explicit","atomic_fetch_add",
 "atomic_fetch_add_explicit","atomic_fetch_and","atomic_fetch_and_explicit","atomic_fetch_or","atomic_fetch_or_explicit",
 "atomic_fetch_sub","atomic_fetch_sub_explicit","atomic_fetch_xor","atomic_fetch_xor_explicit","atomic_flag",
 "atomic_flag_clear","atomic_flag_clear_explicit","atomic_flag_test_and_set","atomic_flag_test_and_set_explicit","atomic_init",

 "atomic_signal_fence","atomic_store","atomic_store_explicit","atomic_thread_fence",
 "atomic_uchar","atomic_schar","atomic_short","atomic_int","atomic_int_fast8_t","atomic_int_fast16_t","atomic_int_fast32_t","atomic_int_fast64_t",
 "atomic_int_least8_t","atomic_int_least16_t","atomic_int_least32_t","atomic_int_least64_t","atomic_intmax_t","atomic_intptr_t",
 "atomic_uint","atomic_uint_fast8_t","atomic_uint_fast16_t","atomic_uint_fast32_t","atomic_uint_fast64_t",
 "atomic_uint_least8_t","atomic_uint_least16_t","atomic_uint_least32_t","atomic_uint_least64_t","atomic_uintmax_t",
 "atomic_wchar_t","atomic_ushort","atomic_ulong","atomic_ullong","atomic_uintptr_t","atomic_size_t",
 "atomic_is_lock_free","atomic_load","atomic_load_explicit","atomic_long","atomic_llong","atomic_ptrdiff_t",
 "ATOMIC_FLAG_INIT","ATOMIC_SHORT_LOCK_FREE","ATOMIC_INT_LOCK_FREE","ATOMIC_LONG_LOCK_FREE","ATOMIC_LLONG_LOCK_FREE","ATOMIC_POINTER_LOCK_FREE","ATOMIC_VAR_INIT",
 "ATOMIC_WCHAR_T_LOCK_FREE","auto",
 "_BitInt","_Bool","bool","break","__bool_true_false_are_defined","BOOL_WIDTH","BITINT_MAXWIDTH",
 "call_once","case","char","char8_t","char16_t","char32_t",
 "cnd_broadcast","cnd_destroy","cnd_init","cnd_signal","cnd_t","cnd_timedwait","cnd_wait","_Complex","complex","const","constexpr","continue",
 "CHAR_BIT","CHAR_WIDTH","CHAR_MIN","CHAR_MAX",
 "_Decimal32","_Decimal64","_Decimal128","default","#define","#defined","do","double","__DATE__",
 "DBL_HAS_SUBNORM","DBL_MANT_DIG","DBL_DECIMAL_DIG","DECIMAL_DIG","DBL_DIG","DBL_MIN_EXP","DBL_MIN_10_EXP","DBL_MAX_EXP","DBL_MAX_10_EXP","DBL_MAX","DBL_EPSILON","DBL_MIN","DBL_TRUE_MIN","DBL_SNAN",
 "#elif","#elifdef","#elifndef","#else","else","#embed","#endif","enum","#error","extern",
 "false","float","for","FLT_ROUNDS","FLT_EVAL_METHOD","FLT_HAS_SUBNORM","FLT_RADIX","FLT_MANT_DIG","FLT_DECIMAL_DIG","FLT_DIG","FLT_MIN_EXP","FLT_MIN_10_EXP","FLT_MAX_EXP","FLT_MAX_10_EXP","FLT_MAX",
 "FLT_EPSILON","FLT_MIN","FLT_TRUE_MIN","FLT_SNAN","__FILE__",
 "_Generic","goto",
 "__has_c_attribute","__has_embed","__has_include",
 "#if","if","#ifdef","#ifndef","_Imaginary","imaginary","_Imaginary_I","#include","inline","if_empty","__if_empty__",
 "int","int8_t","int16_t","int32_t","int64_t","int_fast8_t","int_fast16_t","int_fast32_t","int_fast64_t","int_least8_t","int_least16_t","int_least32_t","int_least64_t","intmax_t","intptr_t",
 "INT8_WIDTH","INT16_WIDTH","INT32_WIDTH","INT64_WIDTH","INT_FAST8_WIDTH","INT_FAST16_WIDTH","INT_FAST32_WIDTH","INT_FAST64_WIDTH","INT_LEAST8_WIDTH","INT_LEAST16_WIDTH","INT_LEAST32_WIDTH","INT_LEAST64_WIDTH",
 "INTMAX_WIDTH","INTPTR_WIDTH","INT8_MIN","INT16_MIN","INT32_MIN","INT64_MIN","INT_FAST8_MIN","INT_FAST16_MIN","INT_FAST32_MIN","INT_FAST64_MIN","INT_LEAST8_MIN","INT_LEAST16_MIN","INT_LEAST32_MIN","INT_LEAST64_MIN",
 "INTMAX_MIN","INTPTR_MIN","INT8_MAX","INT16_MAX","INT32_MAX","INT64_MAX","INT_FAST8_MAX","INT_FAST16_MAX","INT_FAST32_MAX","INT_FAST64_MAX","INT_LEAST8_MAX","INT_LEAST16_MAX","INT_LEAST32_MAX","INT_LEAST64_MAX",
 "INTMAX_MAX","INTPTR_MAX","INT_WIDTH","INT_MIN","INT_MAX","INFINITY",
 "kill_dependency",
 "#line","__LINE__","long","limit","__limit__","LONG_WIDTH","LONG_MIN","LONG_MAX","LLONG_WIDTH","LLONG_MIN","LLONG_MAX","LDBL_HAS_SUBNORM","LDBL_MANT_DIG","LDBL_DECIMAL_DIG",
 "LDBL_DIG","LDBL_MIN_EXP","LDBL_MIN_10_EXP","LDBL_MAX_EXP","LDBL_MAX_10_EXP","LDBL_MAX","LDBL_EPSILON","LDBL_MIN","LDBL_TRUE_MIN","LDBL_SNAN",
 "memory_order","mtx_destroy","mtx_init","mtx_lock","mtx_plain","mtx_recursive","mtx_t","mtx_timed","mtx_timedlock","mtx_trylock","mtx_unlock","max_align_t","MB_LEN_MAX",
 "_Noreturn","noreturn","NULL","nullptr","nullptr_t","NAN",
 "offsetof",
 "#pragma","_Pragma","ptrdiff_t","prefix","__prefix__","PTRDIFF_WIDTH","PTRDIFF_MIN","PTRDIFF_MAX",
 "register","restrict","return",
 "satomic_char8_t","short","signed","sizeof","static","size_t","ssize_t","suffix","__suffix__","_Static_assert","static_assert",
 "__STDC_NO_ATOMICS__","__STDC_NO_THREADS__","__STDC__","__STDC_VERSION__","__STDC_HOSTED__","__STDC_UTF_16__","__STDC_UTF_32__","__STDC_EMBED_NOT_FOUND__","__STDC_EMBED_FOUND__","__STDC_EMBED_EMPTY__",
 "__STDC_ISO_10646__","__STDC_IEC_559__","__STDC_IEC_559_COMPLEX__","__STDC_MB_MIGHT_NEQ_WC__","__STDC_ANALYZABLE__","__STDC_LIB_EXT1__",
 "__STDC_NO_COMPLEX__","__STDC_NO_VLA__","__STDC_IEC_60559_BFP__","__STDC_IEC_60559_DFP__","__STDC_IEC_60559_COMPLEX__","__STDC_IEC_60559_TYPES__",
 "struct","switch","SCHAR_WIDTH","SHRT_WIDTH","SCHAR_MIN","SCHAR_MAX","SHRT_MIN","SHRT_MAX","SIZE_WIDTH","SIZE_MIN","SIZE_MAX","SIG_ATOMIC_WIDTH","SIG_ATOMIC_MIN","SIG_ATOMIC_MAX",
 "thrd_busy","thrd_create","thrd_current","thrd_detach","thrd_equal","thrd_error","thrd_exit","thrd_join","thrd_nomem","thrd_sleep","thrd_start_t","thrd_success","__TIME__",
 "thrd_t","thrd_timedout","thrd_yield","_Thread_local","thread_local","true","tss_create","tss_delete","TSS_DTOR_ITERATIONS","tss_dtor_t","tss_get","tss_set","tss_t","typedef","typeof","typeof_unqual",
 "uint8_t","uint16_t","uint32_t","uint64_t","uint_fast8_t","uint_fast16_t","uint_fast32_t","uint_fast64_t","uint_least8_t","uint_least16_t","uint_least32_t","uint_least64_t","uintmax_t","uintptr_t",
 "#undef","union","unsigned","UINT8_WIDTH","UINT16_WIDTH","UINT32_WIDTH","UINT64_WIDTH","UINT_FAST8_WIDTH","UINT_FAST16_WIDTH","UINT_FAST32_WIDTH","UINT_FAST64_WIDTH",
 "UINT_LEAST8_WIDTH","UINT_LEAST16_WIDTH","UINT_LEAST32_WIDTH","UINT_LEAST64_WIDTH","UINTMAX_WIDTH","UINTPTR_WIDTH","UINT8_MAX","UINT16_MAX","UINT32_MAX","UINT64_MAX",
 "UINT_FAST8_MAX","UINT_FAST16_MAX","UINT_FAST32_MAX","UINT_FAST64_MAX","UINT_LEAST8_MAX","UINT_LEAST16_MAX","UINT_LEAST32_MAX","UINT_LEAST64_MAX","UINTMAX_MAX","UINTPTR_MAX",
 "INT8_C","INT16_C","INT32_C","INT64_C","INTMAX_C","UINT8_C","UINT16_C","UINT32_C","UINT64_C","UINTMAX_C","UCHAR_WIDTH","USHRT_WIDTH","UINT_WIDTH","ULONG_WIDTH","ULLONG_WIDTH",
 "UCHAR_MAX","USHRT_MAX","UINT_MAX","ULONG_MAX","ULLONG_MAX",
 "void","volatile",
 "#warning","while","WCHAR_WIDTH","WCHAR_MIN","WCHAR_MAX","WINT_WIDTH","WINT_MIN","WINT_MAX",
 NULL
};

const uint8_t C_H_keywords_len[]=
{
  4,  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3,  3,  3,  3,
  8,  7,  8,  7,  3,  5,  7,  7, 20, 20,
 11, 11, 15, 15,
 21, 21, 24, 25, 25,
 30, 39, 28,
 37, 15, 24, 16,
 25, 16, 25, 15, 24,
 16, 25, 16, 25, 11,
 17, 26, 24, 33, 11,
 19, 12, 21, 19,
 12, 12, 12, 10, 18, 19, 19, 19,
 19, 20, 20, 20, 15, 15,
 11, 19, 20, 20, 20,
 20, 21, 21, 21, 16,
 14, 13, 12, 13, 16, 13,
 19, 11, 20, 11, 12, 16,
 16, 22, 20, 21, 22, 24, 15,
 24,  4,
  7,  5,  4,  5, 29, 10, 15,
  9,  4,  4,  7,  8,  8,
 13, 11,  8, 10,  5, 13,  8,  8,  7,  5,  9,  8,
  8, 10,  8,  8,
 10, 10, 11,  7,  7,  8,  2,  6,  8,
 15, 12, 15, 11,  7, 11, 14, 11, 14,  7, 11,  7, 12,  8,
  5,  8,  9,  5,  4,  6,  6,  4,  6,  6,
  5,  5,  3, 10, 15, 15,  9, 12, 15,  7, 11, 14, 11, 14,  7,
 11,  7, 12,  8,  8,
  8,  4,
 17, 11, 13,
  3,  2,  6,  7, 10,  9, 12,  8,  6,  8, 12,
  3,  6,  7,  7,  7, 11, 12, 12, 12, 12, 13, 13, 13,  8,  8,
 10, 11, 11, 11, 15, 16, 16, 16, 16, 17, 17, 17,
 12, 12,  8,  9,  9,  9, 13, 14, 14, 14, 14, 15, 15, 15,
 10, 10,  8,  9,  9,  9, 13, 14, 14, 14, 14, 15, 15, 15,
 10, 10,  9,  7,  7,  8,
 15,
  5,  8,  4,  5,  9, 10,  8,  8, 11,  9,  9, 16, 13, 16,
  8, 12, 15, 12, 15,  8, 12,  8, 13,  9,
 12, 11,  8,  8,  9, 13,  5,  9, 13, 11, 10, 11, 10,
  9,  8,  4,  7,  9,  3,
  8,
  7,  7,  9,  6, 10, 13, 11, 11,
  8,  8,  6,
 15,  5,  6,  6,  6,  6,  7,  6, 10, 14, 13,
 19, 19,  8, 16, 15, 15, 15, 24, 20, 20,
 18, 16, 24, 24, 19, 17,
 19, 15, 22, 22, 26, 24,
  6,  6, 11, 10,  9,  9,  8,  8, 10,  8,  8, 16, 14, 14,
  9, 11, 12, 11, 10, 10,  9,  9, 10, 10, 12, 12,  8,
  6, 13, 10, 13, 12,  4, 10, 10, 19, 10,  7,  7,  5,  7,  6, 13,
  7,  8,  8,  8, 12, 13, 13, 13, 13, 14, 14, 14,  9,  9,
  6,  5,  8, 11, 12, 12, 12, 16, 17, 17, 17,
 17, 18, 18, 18, 13, 13,  9, 10, 10, 10,
 14, 15, 15, 15, 15, 16, 16, 16, 11, 11,
  6,  7,  7,  7,  8,  7,  8,  8,  8,  9, 11, 11, 10, 11, 12,
  9,  9,  8,  9, 10,
  4,  8,
  8,  5, 11,  9,  9, 10,  8,  8,
};

//1 H_KEYWORD_1
//2 H_KEYWORD_2
//3 H_KEYWORD_3

const uint8_t C_H_keywords_syntax_color[]=
{
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3,
 3, 3, 3, 3, 3,
 3, 3, 3,
 3, 3, 3, 3,
 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3,
 3, 3, 3, 3,
 3, 3, 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3, 3, 3,
 3, 3,
 3, 3, 2, 3, 3, 3, 3,
 3, 3, 2, 2, 2, 2,
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3,
 3, 3, 3, 3, 1, 1, 3, 2, 3,
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 1, 1, 1, 1, 3, 1, 1, 2, 1, 3,
 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3,
 3, 3,
 3, 3, 3,
 1, 3, 1, 1, 3, 3, 3, 1, 3, 3, 3,
 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3, 3,
 3,
 1, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 3, 2, 3, 3, 3,
 3,
 1, 3, 3, 3, 3, 3, 3, 3,
 3, 3, 3,
 3, 2, 2, 3, 3, 2, 2, 3, 3, 3, 3,
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3, 3,
 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
 1, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 3, 3, 3, 3,
 2, 3,
 1, 3, 3, 3, 3, 3, 3, 3,
};

/*** data ***/
typedef struct
{
 uint64_t reserve_size;
 uint64_t commit_size;
 uint64_t pos;
 uint64_t commit_pos;
}mem_arena;

typedef struct 
{
 char* b;
 uint32_t len;
 uint32_t cap;
}a_buf;

typedef struct
{
 char* characters;
 char* render;
 uint8_t* highlight;
 int32_t* wrap_starts;
 int32_t id;
 int32_t size;
 int32_t r_size;
 int32_t gap_start;
 int32_t gap_end;
 int32_t buf_size;
 int32_t wrap_seg_count;
 int32_t wrap_starts_cap;
 int32_t wrap_epoch;
 uint8_t h_open_comment;
 //you have space for 3x uint8_t
}e_row;

typedef struct
{
 const char* file_type;
 const char* const* file_ext;
 const char* const* keywords;
 const uint8_t* keywords_len;
 const uint8_t* keywords_syntax_color;
 const char* single_line_comment_start;
 const char* multi_line_comment_start;
 const char* multi_line_comment_end;
}syntax;

typedef struct
{
 char*    row_text;
 uint32_t row_len;
 int32_t  c_x;
 int32_t  c_y;
 int32_t  c_x_end;
 int32_t  c_y_end;
 int32_t  join_col;
 uint8_t  type;
 uint8_t  c_len;
 char     c[6];
}actions;

struct config
{
 char* file_name;
 e_row* row;
 syntax* syntax;
 actions* undo_stack;
 actions* redo_stack;
 time_t status_msg_time;
 int64_t last_known_mtime;
 int32_t c_x;
 int32_t c_y;
 int32_t r_x;
 int32_t saved_r_x;
 int32_t select_anchor_x;
 int32_t select_anchor_y;
 int32_t row_off;
 int32_t col_off;
 int32_t seg_col_off;
 int32_t wrap_generation;
 int32_t num_rows;
 int16_t screen_rows;
 int16_t screen_cols;
 int16_t term_rows;
 int16_t undo_top;
 int16_t redo_top;
 int16_t saved_undo_top;
 uint8_t line_num_width;
 uint8_t num_of_status_msg_lines;
 uint8_t msg_color;
 uint8_t select_mode;
 uint8_t mode;
 uint8_t dirty;
 uint8_t file_modified_externally;
 uint8_t utf8_output;
 char status_msg[512];
 #ifdef _WIN32
  DWORD orig_in_mode;
  DWORD orig_out_mode;
 #else
  struct termios original_termios;
 #endif
};

syntax H_DB[]=
{
 //use NULL for comments if you do not have them
 {"C",C_H_extensions,C_H_keywords,C_H_keywords_len,C_H_keywords_syntax_color,"//","/*","*/"}
};

#define H_DB_ENTRIES (uint8_t)((sizeof(H_DB)/sizeof(H_DB[0])))

typedef struct
{
 char name[256];
 uint8_t is_dir;
 //you have space for 7x uint8_t
}browse_entry;

browse_entry* browse_entries=NULL;
int32_t browse_entry_count=0;
int32_t browse_entry_cap=0;
uint8_t browse_flag=0;

#define BROWSE_MIN_LONG_COLS 80

#ifdef _WIN32
 #define BROWSE_SEP '\\'
#else
 #define BROWSE_SEP '/'
#endif

struct config E;

static volatile sig_atomic_t window_resized=0;

char* clipboard_buffer=NULL;
uint32_t clipboard_len=0;
uint8_t clipboard_row_mode=0;

char* paste_stream_buffer=NULL;
uint32_t paste_stream_len=0;

int32_t g_mouse_x=0;
int32_t g_mouse_y=0;

int32_t s_last_click_c_x=-1;
int32_t s_last_click_c_y=-1;
uint64_t s_last_click_ms=0;

uint32_t row_capacity=0;
mem_arena* render_arena=NULL;
mem_arena* highlight_arena=NULL;
uint64_t render_arena_wasted=0;
uint64_t highlight_arena_wasted=0;

int32_t* wrap_starts_buf=NULL;
int32_t wrap_starts_cap=0;

int32_t* seg_start_buf=NULL;
uint8_t* seg_type_buf=NULL;
int32_t seg_bufs_cap=0;

static int8_t find_direction=1;
static int32_t find_last_match_row=-1;
static int32_t find_last_match_col=-1;

/*** prototypes ***/
//helper
int8_t write_all(int32_t f_d,const char* buf,uint32_t len);
void die(char* s);
void a_buf_append(a_buf* a_buffer,char* s,uint32_t len);
void a_buf_free(a_buf* a_buffer);

//memory arena
uint32_t platform_get_page_size();
void* platform_mem_reserve(uint64_t size);
uint8_t platform_mem_commit(void* pointer,uint64_t size);
uint8_t platform_mem_decommit(void* pointer,uint64_t size);
uint8_t platform_mem_release(void* pointer,uint64_t size);
mem_arena* arena_create(uint64_t reserve_size,uint64_t commit_size);
void arena_destroy(mem_arena* arena);
void* arena_push(mem_arena* arena,uint64_t size,uint8_t zero);
void arena_pop(mem_arena* arena,uint64_t size);
void arena_pop_to(mem_arena* arena,uint64_t pos);
void arena_clear(mem_arena* arena);
static void compact_row_arenas();

//init
uint8_t detect_utf8_output();
void init_editor();

//terminal
void enable_raw_mode();
void disable_raw_mode();
int8_t get_window_size(int16_t* rows,int16_t* cols);
void handle_sigwinch(int unused);
void update_line_num_width();
int8_t get_cursor_position(int16_t* rows,int16_t* cols);
uint64_t get_ms_ticks();
uint16_t read_key();

//syntax highlighting
uint8_t syntax_to_color(uint8_t highlight);
void select_syntax_highlight();
uint8_t is_separator(int16_t c);
void update_syntax(e_row* row);

//row operations
uint8_t get_utf8_char_placement_length(e_row* row,int32_t c_x);
int32_t snap_to_utf8_start(e_row* row,int32_t c_x);
uint8_t utf8_seq_len_valid(e_row* row,int32_t c_x);
int32_t utf8_safe_trunc_len(const char* s,int32_t max_len);
static uint8_t get_render_control_type(unsigned char c);
int32_t row_c_x_to_r_x(e_row* row,int32_t c_x);
int32_t row_r_x_to_c_x(e_row* row,int32_t r_x);
static void row_gap_move_to(e_row* row,int32_t pos);
static void row_gap_reserve(e_row* row,int32_t extra);
static void row_gap_flatten(e_row* row);
static void row_truncate(e_row* row,int32_t new_size);
void seg_bufs_ensure(int32_t needed);
void update_row(e_row* row);
void insert_row(int32_t n,char* s,uint32_t len);
void row_append_string(e_row* row,char* s,uint32_t len);
static void row_delete_range(e_row* row,int32_t from,int32_t to);
void del_row(int32_t n);
void del_row_range(int32_t low,int32_t high_inclusive);
void row_insert_char(e_row* row,int32_t n,int16_t c);
void row_del_char(e_row* row,int32_t n);
void row_insert_string(e_row* row,int32_t n,char* s,uint32_t len);
void free_row(e_row* row);

//editor operations
void insert_char(int16_t c);
void insert_utf8_char(char* bytes, int len);
void insert_new_line();
void insert_text_range(char* text,uint32_t len);
void del_char();
void delete_char_range(int32_t x_1,int32_t y_1,int32_t x_2,int32_t y_2);
void action_free(actions* action);
void undo_push(actions* action);
void undo();
void redo();
void get_selection_bounds(int32_t* x_1,int32_t* y_1,int32_t* x_2,int32_t* y_2);
uint8_t is_selected(int32_t row,int32_t col);
void osc52_copy(const char* text,uint32_t len);
void copy_selection();
void delete_selection();
void paste_clipboard();

//file browser
void reset_editor_for_new_file();
int8_t path_is_directory(const char* path);
int browse_compare_entries(const void* a,const void* b);
static void browse_push_entry(const char* name,uint8_t is_dir);
void browse_free_entries();
int8_t browse_load_entries(const char* path);
void format_size(char *buf,uint64_t buf_size,uint64_t size);
void browse_build_long_line(const char* dir,const char* name,char* out,uint64_t out_size);
int32_t browse_mouse_to_index(int32_t list_rows,int32_t scroll_off);
char* browse_for_file(const char* start_path);

//file I/O
int8_t get_file_mtime(const char* path,int64_t* out_mtime);
void update_known_mtime();
void check_file_modified_externally();
int8_t file_is_binary(const char* path);
void open_file(char* file_name);
char* rows_to_string(uint32_t* buffer_placement_len);
void save_file();

//find
static int32_t find_last_in_row_before(e_row* row,char* query,int32_t before_col);
static int32_t find_next_match(int32_t start_row,int32_t start_col,char* query,int8_t direction,int32_t* out_row);
static void count_matches(char* query,int32_t cur_row,int32_t cur_col,int32_t* rank,int32_t* total);
void find_callback(char* query,uint16_t key);
void find();
void go_to_line();
static uint8_t is_render_boundary(e_row* row,int32_t r_x);
static uint8_t map_render_range_to_raw(e_row*row,int32_t r_start,int32_t r_len,int32_t* c_start,int32_t* c_len);
static uint8_t replace_one_match(int32_t r,int32_t r_x,char* query,char* replacement);
static int32_t replace_all_matches(char* query,char* replacement);
void search_and_replace();

//input
char* prompt(uint8_t color,char* prompt,void (*callback)(char*,uint16_t));
void move_cursor(uint16_t key);
void mouse_to_cursor(int32_t m_x,int32_t m_y,int32_t* c_x_out,int32_t* c_y_out);
void select_word_at(int32_t c_x,int32_t c_y);
void process_keypress();

//output
uint32_t utf8_decode_buf(const char* buffer,int32_t i,int32_t len,uint8_t seq_len);
uint8_t code_point_is_wide(uint32_t c_p);
int32_t token_step(e_row* row,int32_t i,uint8_t* out_width);
uint8_t rendered_char_width(const char* buffer,int32_t i,int32_t len);
static int32_t compute_wrap_segments(e_row* row,int32_t* seg_render_starts,int32_t max_segs);
static void ensure_wrap_cache(e_row* row);
uint8_t row_should_wrap(int32_t file_row);
int32_t* wrap_seg_buf(int32_t needed);
int32_t get_wrap_segments(int32_t file_row,int32_t* seg_render_starts,int32_t max_segs);
int32_t count_screen_rows(int32_t file_row);
int32_t get_cursor_segment_info(int32_t file_row,int32_t r_x,int32_t* seg_vis_start);
void scroll();
void draw_rows(a_buf* a_buffer);
void draw_status_bar(a_buf* a_buffer);
void set_status_message(uint8_t color,const char* format,...);
void draw_message_bar(a_buf* a_buffer);
void draw_external_mod_warning(a_buf* a_buffer);
void refresh_screen();

int main(int arg_c,char* arg_v[])
{
 if(arg_c >= 2)
 {
  if(strcmp(arg_v[1],"-v") == 0 || strcmp(arg_v[1],"--version") == 0)
  {
   printf("rwx editor version %s\n",RWX_VERSION);
   return 0;
  }

  if(strcmp(arg_v[1],"-h") == 0 || strcmp(arg_v[1],"--help") == 0)
  {
   printf("\n");
   printf("rrrrr   rrrrrrrrr  wwwwwww           wwwww           wwwwwww  xxxxxxx      xxxxxxx\n");
   printf("r::::rrr:::::::::r  w:::::w         w:::::w         w:::::w    x:::::x    x:::::x \n");
   printf("r:::::::::::::::::r  w:::::w       w:::::::w       w:::::w      x:::::x  x:::::x  \n");
   printf("rr::::::rrrrr::::::r  w:::::w     w:::::::::w     w:::::w        x:::::xx:::::x   \n");
   printf(" r:::::r     r:::::r   w:::::w   w:::::w:::::w   w:::::w          x::::::::::x    \n");
   printf(" r:::::r     rrrrrrr    w:::::w w:::::w w:::::w w:::::w            x::::::::x     \n");
   printf(" r:::::r                 w:::::w:::::w   w:::::w:::::w             x::::::::x     \n");
   printf(" r:::::r                  w:::::::::w     w:::::::::w             x::::::::::x    \n");
   printf(" r:::::r                   w:::::::w       w:::::::w             x:::::xx:::::x   \n");
   printf(" r:::::r                    w:::::w         w:::::w             x:::::x  x:::::x  \n");
   printf(" r:::::r                     w:::w           w:::w             x:::::x    x:::::x \n");
   printf(" rrrrrrr                      www             www             xxxxxxx      xxxxxxx\n");
   printf("\nrwx is a terminal text editor\n\n");
   printf("Usage: %s [OPTION] [FILE]\n\n",arg_v[0]);
   printf("Options:\n");
   printf(" -v, --version show the rwx version\n");
   printf(" -h, --help    show this help message\n\n");
   printf("Editor shortcuts:\n\n");
   printf("HELP: Ctrl+h=Help (Prints this)\n");
   printf("----------------------------------\n");
   printf("| Ctrl+s=Save   | Ctrl+q=Quit    |\n");
   printf("| Ctrl+i=Insert | Ctrl+e=Select  |\n");
   printf("| Ctrl+z=Undo   | Ctrl+r=Redo    |\n");
   printf("| Ctrl+o=Open   | Ctrl+p=Reopen  |\n");
   printf("| Ctrl+g=Go to  | Ctrl+x=Cut     |\n");
   printf("| Ctrl+c=Copy   | Ctrl+v=Paste   |\n");
   printf("| Ctrl+f=Find   | Ctrl+w=Replace |\n");
   printf("----------------------------------\n");
   printf("\n");
   return 0;
  }
 }

 enable_raw_mode();
 init_editor();

 #ifndef _WIN32
  struct sigaction s_a;

  s_a.sa_handler=handle_sigwinch;
  sigemptyset(&s_a.sa_mask);
  s_a.sa_flags=0;

  if(sigaction(SIGWINCH,&s_a,NULL) == -1)
  {
   die("sigaction [main]");
  }
 #endif

 if(arg_c >= 2)
 {
  if(path_is_directory(arg_v[1]) == 1)
  {
   char* selected=browse_for_file(arg_v[1]);

   if(selected != NULL)
   {
    open_file(selected);
    free(selected);
   }
  }
  else
  {
   open_file(arg_v[1]);
  }
 }

 while(1)
 {
  if(window_resized)
  {
   window_resized=0;
   get_window_size(&E.term_rows,&E.screen_cols);
  }
  check_file_modified_externally();
  refresh_screen();
  process_keypress();
 }
 return 0;
}

/*** helper ***/
int8_t write_all(int32_t f_d,const char* buf,uint32_t len)
{
 uint32_t written_total=0;

 while(written_total < len)
 {
  ssize_t written=write(f_d,buf+written_total,len-written_total);

  if(written <= 0)
  {
   if(written == -1 && errno == EINTR)
   {
    continue;
   }
   return -1;
  }
  written_total+=(uint32_t)written;
 }
 return 0;
}

void die(char* s)
{
 write_all(STDOUT_FILENO,"\x1b[?1006l",8);
 write_all(STDOUT_FILENO,"\x1b[?1002l",8);
 write_all(STDOUT_FILENO,"\x1b[2J",4);
 write_all(STDOUT_FILENO,"\x1b[H",3);

 perror(s);
 exit(1);
}

void a_buf_append(a_buf* a_buffer,char* s,uint32_t len)
{
 if(a_buffer->len+len > a_buffer->cap)
 {
  uint32_t new_cap=a_buffer->cap ? a_buffer->cap*2 : 256;

  while(new_cap < a_buffer->len+len) 
  {
   new_cap*=2;
  }

  char* new_buffer=realloc(a_buffer->b,new_cap);

  if(!new_buffer)
  {
   die("realloc [a_buf_append]");
  }

  a_buffer->b=new_buffer;
  a_buffer->cap=new_cap;
 }
 memcpy(a_buffer->b+a_buffer->len,s,len);
 a_buffer->len+=len;
}

void a_buf_free(a_buf* a_buffer)
{
 free(a_buffer->b);
 a_buffer->b=NULL;
 a_buffer->len=0;
 a_buffer->cap=0;
}

/*** memory arena ***/
#ifdef _WIN32
 uint32_t platform_get_page_size()
 {
  SYSTEM_INFO sys_info={0};
  GetSystemInfo(&sys_info);

  return sys_info.dwPageSize;
 }

 void* platform_mem_reserve(uint64_t size)
 {
  return VirtualAlloc(NULL,size,MEM_RESERVE,PAGE_READWRITE);
 }

 uint8_t platform_mem_commit(void* pointer,uint64_t size)
 {
  void* return_pointer=VirtualAlloc(pointer,size,MEM_COMMIT,PAGE_READWRITE);
  return return_pointer != NULL;
 }

 uint8_t platform_mem_decommit(void* pointer,uint64_t size)
 {
  return VirtualFree(pointer,size,MEM_DECOMMIT);
 }

 uint8_t platform_mem_release(void* pointer,uint64_t size)
 {
  (void)size;
  return VirtualFree(pointer,0,MEM_RELEASE);
 }
#else
 uint32_t platform_get_page_size()
 {
  return (uint32_t)sysconf(_SC_PAGESIZE);
 }

 void* platform_mem_reserve(uint64_t size)
 {
  void* pointer=mmap(NULL,size,PROT_NONE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);

  if(pointer == MAP_FAILED)
  {
   return NULL;
  }

  return pointer;
 }

 uint8_t platform_mem_commit(void* pointer,uint64_t size)
 {
  return mprotect(pointer,size,PROT_READ|PROT_WRITE) == 0;
 }

 uint8_t platform_mem_decommit(void* pointer,uint64_t size)
 {
  madvise(pointer,size,MADV_DONTNEED);
  return mprotect(pointer,size,PROT_NONE) == 0;
 }

 uint8_t platform_mem_release(void* pointer,uint64_t size)
 {
  return munmap(pointer,size) == 0;
 }

#endif

mem_arena* arena_create(uint64_t reserve_size,uint64_t commit_size)
{
 uint32_t page_size=platform_get_page_size();

 reserve_size=ALIGN_UP_POW_OF_2(reserve_size,page_size);
 commit_size=ALIGN_UP_POW_OF_2(commit_size,page_size);

 if(commit_size > reserve_size)
 {
  die("commit_size must be <= reserve_size [arena_create]");
 }

 mem_arena* arena=platform_mem_reserve(reserve_size);

 if(arena == NULL)
 {
  die("arena reserve (platform_mem_reserve) [arena_create]");
 }

 if(!platform_mem_commit(arena,commit_size))
 {
  die("arena commit (platform_mem_commit) [arena_create]");
 }

 arena->reserve_size=reserve_size;
 arena->commit_size=commit_size;
 arena->pos=ARENA_BASE_POS;
 arena->commit_pos=commit_size;

 return arena;
}

void arena_destroy(mem_arena* arena)
{
 platform_mem_release(arena,arena->reserve_size);
}

void* arena_push(mem_arena* arena,uint64_t size,uint8_t zero)
{
 uint64_t pos_aligned=ALIGN_UP_POW_OF_2(arena->pos,ARENA_ALIGN);
 uint64_t new_pos=pos_aligned+size;

 if(new_pos > arena->reserve_size)
 {
  die("arena is out of reserved space [arena_push]");
 }

 if(new_pos > arena->commit_pos)
 {
  uint64_t new_commit_pos=new_pos;

  new_commit_pos+=arena->commit_size-1;
  new_commit_pos-=new_commit_pos % arena->commit_size;
  new_commit_pos=MIN(new_commit_pos,arena->reserve_size);

  uint8_t* mem=(uint8_t*)arena+arena->commit_pos;
  uint64_t commit_size=new_commit_pos-arena->commit_pos;

  if(!platform_mem_commit(mem,commit_size))
  {
   die("arena commit (platform_mem_commit) [arena_push]");
  }

  arena->commit_pos=new_commit_pos;
 }

 arena->pos=new_pos;
 uint8_t* out=(uint8_t*)arena+pos_aligned;

 if(zero)
 {
  memset(out,0,size);
 }

 return out;
}

void arena_pop(mem_arena* arena,uint64_t size)
{
 size=MIN(size,arena->pos-ARENA_BASE_POS);
 arena->pos-=size;
}

void arena_pop_to(mem_arena* arena,uint64_t pos)
{
 uint64_t size=pos < arena->pos ? arena->pos-pos : 0;
 arena_pop(arena,size);
}

void arena_clear(mem_arena* arena)
{
 arena_pop_to(arena,ARENA_BASE_POS);
}

static void compact_row_arenas()
{
 mem_arena* new_render=arena_create(render_arena->reserve_size,render_arena->commit_size);
 mem_arena* new_highlight=arena_create(highlight_arena->reserve_size,highlight_arena->commit_size);

 int32_t i=0;

 for(i=0;i < E.num_rows;++i)
 {
  e_row* row=&E.row[i];

  if(row->render != NULL)
  {
   char* fresh=arena_push(new_render,(uint64_t)row->r_size+1,0);
   memcpy(fresh,row->render,(size_t)row->r_size+1);
   row->render=fresh;
  }

  if(row->highlight != NULL)
  {
   uint8_t* fresh=arena_push(new_highlight,(uint64_t)row->r_size,0);
   memcpy(fresh,row->highlight,(size_t)row->r_size);
   row->highlight=fresh;
  }
 }

 arena_destroy(render_arena);
 arena_destroy(highlight_arena);

 render_arena=new_render;
 highlight_arena=new_highlight;

 render_arena_wasted=0;
 highlight_arena_wasted=0;
}

/*** init ***/
uint8_t detect_utf8_output()
{
 #ifdef _WIN32
  if(SetConsoleOutputCP(CP_UTF8) && SetConsoleCP(CP_UTF8))
  {
   setvbuf(stdout,NULL,_IONBF,0);
   return 1;
  }
  return 0;
 #else
  if(!isatty(STDOUT_FILENO))
  {
   return 0;
  }

  char* term=getenv("TERM");

  if(term != NULL && strcmp(term,"linux") == 0)
  {
   return 0; 
  }

  setlocale(LC_ALL,"");

  char* code_set=nl_langinfo(CODESET);

  if(code_set == NULL)
  {
   return 0;
  }

  return (strstr(code_set,"UTF-8") != NULL || strstr(code_set,"utf8") != NULL) ? 1 : 0;
 #endif
}

void init_editor()
{
 E.file_name=NULL;
 E.row=NULL;
 E.syntax=NULL;
 E.undo_stack=NULL;
 E.redo_stack=NULL;
 E.status_msg_time=0;
 E.last_known_mtime=0;
 E.c_x=0;
 E.c_y=0;
 E.r_x=0;
 E.saved_r_x=-1;
 E.select_anchor_x=0;
 E.select_anchor_y=0;
 E.row_off=0;
 E.col_off=0;
 E.seg_col_off=0;
 E.wrap_generation=0;
 E.num_rows=0;
 E.screen_rows=0;
 E.screen_cols=0;
 E.term_rows=0;
 E.undo_top=-1;
 E.redo_top=-1;
 E.saved_undo_top=-1;
 E.line_num_width=0;
 E.num_of_status_msg_lines=0;
 E.msg_color=DEFAULT_MSG_COLOR;
 E.select_mode=SELECT_NONE;
 E.mode=MODE_NORMAL;
 E.dirty=0;
 E.file_modified_externally=0;
 E.utf8_output=detect_utf8_output();
 E.status_msg[0]='\0';

 render_arena=arena_create(MB(256),KB(64));
 highlight_arena=arena_create(MB(128),KB(64));

 if(sizeof(RWX_VERSION)-1 == 0 || sizeof(RWX_VERSION)-1 > 12)
 {
  die("RWX_VERSION is invalid length [init_editor]");
 }

 if(!(TAB_STOP > 0 && (TAB_STOP & (TAB_STOP-1)) == 0))
 {
  die("TAB_STOP is invalid value [init_editor]");
 }

 if(SIZE_LIMIT < 1 || SIZE_LIMIT > 32767)
 {
  die("SIZE_LIMIT is invalid value [init_editor]");
 }

 E.undo_stack=malloc(sizeof(actions)*SIZE_LIMIT);
 E.redo_stack=malloc(sizeof(actions)*SIZE_LIMIT);

 if(E.undo_stack == NULL || E.redo_stack == NULL)
 {
  die("malloc undo/redo stack [init_editor]");
 }

 if(get_window_size(&E.term_rows,&E.screen_cols) == -1)
 {
  die("get_window_size [init_editor]");
 }

 E.screen_rows=E.term_rows-1;
 update_line_num_width();
}

/*** terminal ***/
void enable_raw_mode()
{
 #ifdef _WIN32
  HANDLE h_in=GetStdHandle(STD_INPUT_HANDLE);
  HANDLE h_out=GetStdHandle(STD_OUTPUT_HANDLE);
    
  if(h_in == INVALID_HANDLE_VALUE || h_out == INVALID_HANDLE_VALUE)
  {
   die("GetStdHandle [enable_raw_mode]");
  }

  if(!GetConsoleMode(h_in,&E.orig_in_mode))
  {
   die("GetConsoleMode input [enable_raw_mode]");
  }

  if(!GetConsoleMode(h_out,&E.orig_out_mode))
  {
   die("GetConsoleMode output [enable_raw_mode]");
  }

  atexit(disable_raw_mode);

  DWORD raw_in=E.orig_in_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_QUICK_EDIT_MODE);
  raw_in |= ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT;

  if(!SetConsoleMode(h_in,raw_in))
  {
   die("SetConsoleMode input flags [enable_raw_mode]");
  }

  DWORD mode_out=E.orig_out_mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;

  if(!SetConsoleMode(h_out,mode_out))
  {
   SetConsoleMode(h_in,E.orig_in_mode);
   die("ENABLE_VIRTUAL_TERMINAL_PROCESSING failed, requires Windows 10 v1511 or later [enable_raw_mode]");
  }
 #else
  if(tcgetattr(STDIN_FILENO,&E.original_termios) == -1)
  {
   die("tcgetattr [enable_raw_mode]");
  }

  write_all(STDOUT_FILENO,"\x1b[?1002h",8);
  write_all(STDOUT_FILENO,"\x1b[?1006h",8);
  write_all(STDOUT_FILENO,"\x1b[?2004h",8);

  atexit(disable_raw_mode);

  struct termios raw=E.original_termios;
 
  tcgetattr(STDIN_FILENO,&raw);

  raw.c_iflag &= ~(BRKINT|ICRNL|INPCK|ISTRIP|IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO|ICANON|IEXTEN|ISIG);
  raw.c_cc[VMIN]=0;
  raw.c_cc[VTIME]=1;

  if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw) == -1)
  {
   die("tcsetattr [enable_raw_mode]");
  }
 #endif
}

void disable_raw_mode()
{
 #ifdef _WIN32
  SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),E.orig_in_mode);
  SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE),E.orig_out_mode);
 #else
  write_all(STDOUT_FILENO,"\x1b[?2004l",8);
  write_all(STDOUT_FILENO,"\x1b[?1006l",8);
  write_all(STDOUT_FILENO,"\x1b[?1002l",8);

  if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&E.original_termios) == -1)
  {
   die("tcsetattr [disable_raw_mode]");
  }
 #endif
}

int8_t get_window_size(int16_t* rows,int16_t* cols)
{
 #ifdef _WIN32
  CONSOLE_SCREEN_BUFFER_INFO c_s_b_i;

  if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&c_s_b_i))
  {
   *cols=c_s_b_i.srWindow.Right-c_s_b_i.srWindow.Left+1;
   *rows=c_s_b_i.srWindow.Bottom-c_s_b_i.srWindow.Top+1;

   return 0;
  }
  return -1;
 #else
  struct winsize w_s;

  if(ioctl(STDOUT_FILENO,TIOCGWINSZ,&w_s) == -1 || w_s.ws_col == 0)
  {
   if(write_all(STDOUT_FILENO,"\x1b[999C\x1b[999B",12) == -1)
   {
    return -1;
   }
   return get_cursor_position(rows,cols);
  }
  else
  {
   *rows=w_s.ws_row;
   *cols=w_s.ws_col;
   return 0;
  }
 #endif
}

void handle_sigwinch(int unused)
{
 (void)unused;
 window_resized=1; 
}

void update_line_num_width()
{
 int32_t n=0;
 uint8_t digits=0;
 int32_t visible_bottom=E.row_off+E.screen_rows;

 if(visible_bottom > E.num_rows)
 {
  visible_bottom=E.num_rows;
 }

 if(visible_bottom > 0)
 {
  n=visible_bottom;
 }
 else
 {
  n=1;
 }

 while(n > 0)
 {
  n/=10;
  ++digits;
 }

 uint8_t new_width=digits+1;

 if(new_width < 2)
 {
  new_width=2;
 }

 if(new_width != E.line_num_width)
 {
  ++E.wrap_generation;
 }

 E.line_num_width=new_width;
}

int8_t get_cursor_position(int16_t* rows,int16_t* cols)
{
 char buffer[32];
 uint8_t i=0;
 
 if(write_all(STDOUT_FILENO,"\x1b[6n",4) == -1)
 {
  return -1;
 }

 while(i < sizeof(buffer)-1)
 {
  if(read(STDIN_FILENO,&buffer[i],1) != 1)
  {
   break;
  }

  if(buffer[i] == 'R')
  {
   break;
  }
  ++i;
 }
 buffer[i]='\0';

 if(i < 2 || buffer[0] != '\x1b' || buffer[1] != '[')
 {
  return -1;
 }

 if(sscanf(&buffer[2],"%hd;%hd",rows,cols) != 2) 
 {
  return -1;
 }

 return 0;
}

uint64_t get_ms_ticks()
{
 #ifdef _WIN32
  return (uint64_t)GetTickCount64();
 #else
  struct timespec t_s;
  clock_gettime(CLOCK_MONOTONIC,&t_s);
  return (uint64_t)t_s.tv_sec*1000+(uint64_t)(t_s.tv_nsec/1000000);
 #endif
}

uint16_t read_key()
{
 #ifdef _WIN32
  HANDLE h_in=GetStdHandle(STD_INPUT_HANDLE);
  INPUT_RECORD i_r;
  DWORD new_line;

  static char pending_utf8[8];
  static int pending_utf8_len=0;

  if(pending_utf8_len > 0)
  {
   char next_byte=pending_utf8[0];
   --pending_utf8_len;
   memmove(pending_utf8,pending_utf8+1,pending_utf8_len);
   return (uint16_t)(unsigned char)next_byte;
  }

  while(1)
  {
   if(!ReadConsoleInputW(h_in,&i_r,1,&new_line))
   {
    die("ReadConsoleInputW [read_key]");
   }

   if(i_r.EventType == WINDOW_BUFFER_SIZE_EVENT)
   {
    return RESIZE_KEY;
   }

   if(i_r.EventType == MOUSE_EVENT)
   {
    MOUSE_EVENT_RECORD* m_e=&i_r.Event.MouseEvent;
    g_mouse_x=m_e->dwMousePosition.X;
    g_mouse_y=m_e->dwMousePosition.Y;

    if(m_e->dwEventFlags == MOUSE_WHEELED)
    {
     if((int16_t)HIWORD(m_e->dwButtonState) > 0)
     {
      return MOUSE_WHEEL_UP;
     }
     else
     {
      return MOUSE_WHEEL_DOWN;
     }
    }
    if(m_e->dwEventFlags == MOUSE_MOVED)
    {
     if(m_e->dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
     {
      return MOUSE_LEFT_DRAG;
     }
     continue;
    }
    if(m_e->dwEventFlags == 0)
    {
     if(m_e->dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
     {
      return MOUSE_LEFT_PRESS;
     }
     else if(m_e->dwButtonState & RIGHTMOST_BUTTON_PRESSED)
     {
      return MOUSE_RIGHT_PRESS;
     }
     else if(m_e->dwButtonState & FROM_LEFT_2ND_BUTTON_PRESSED)
     {
      return MOUSE_MIDDLE_CLICK;
     }
     else
     {
      return MOUSE_LEFT_RELEASE;
     }
    }
    continue;
   }

   if(i_r.EventType != KEY_EVENT || !i_r.Event.KeyEvent.bKeyDown)
   {
    continue;
   }

   KEY_EVENT_RECORD* k_e=&i_r.Event.KeyEvent;
   WORD v_k=k_e->wVirtualKeyCode;

   WCHAR w_c=k_e->uChar.UnicodeChar;

   switch(v_k)
   {
    case VK_BACK:
    {
     return BACKSPACE;
    }
    break;

    case VK_UP:
    {
     return ARROW_UP;
    }
    break;

    case VK_DOWN:
    {
     return ARROW_DOWN;
    }
    break;

    case VK_RIGHT:
    {
     return ARROW_RIGHT;
    }
    break;

    case VK_LEFT:
    {
     return ARROW_LEFT;
    }
    break;

    case VK_DELETE:
    {
     return DEL_KEY;
    }
    break;

    case VK_INSERT:
    {
     return INSERT_KEY;
    }
    break;

    case VK_HOME:
    {
     return HOME_KEY;
    }
    break;

    case VK_END:
    {
     return END_KEY;
    }
    break;

    case VK_PRIOR:
    {
     return PAGE_UP;
    }
    break;

    case VK_NEXT:
    {
     return PAGE_DOWN;
    }
    break;
   }

   if(w_c >= 0xD800 && w_c <= 0xDFFF)
   {
    continue;
   }

   if(w_c > 0 && w_c < 0x80)
   {
    return (uint16_t)w_c;
   }
   else if(w_c >= 0x80 && w_c <= 0x7FF)
   {
    pending_utf8[0]=(char)(0xC0 | (w_c >> 6));
    pending_utf8[1]=(char)(0x80 | (w_c & 0x3F));
    pending_utf8_len=2;
   }
   else if(w_c >= 0x800)
   {
    pending_utf8[0]=(char)(0xE0 | (w_c >> 12));
    pending_utf8[1]=(char)(0x80 | ((w_c >> 6) & 0x3F));
    pending_utf8[2]=(char)(0x80 | (w_c & 0x3F));
    pending_utf8_len=3;
   }
   else
   {
    continue;
   }

   char first_byte=pending_utf8[0];
   --pending_utf8_len;
   memmove(pending_utf8,pending_utf8+1,pending_utf8_len);
   return (uint16_t)(unsigned char)first_byte;
  }
 #else
  if(window_resized)
  {
   return RESIZE_KEY;
  }

  ssize_t n_read=0;
  char c=0;

  while((n_read=read(STDIN_FILENO,&c,1)) != 1)
  {
   if(n_read == -1 && errno == EINTR)
   {
    if(window_resized)
    {
     return RESIZE_KEY;
    }
    continue;
   }

   if(n_read == -1 && errno != EAGAIN)
   {
    die("read [read_key]");
   }

   if(window_resized)
   {
    return RESIZE_KEY;
   }
  }
  if(c == '\x1b')
  {
   char seq[8];

   if(read(STDIN_FILENO,&seq[0],1) != 1)
   {
    return '\x1b';
   }
  
   if(read(STDIN_FILENO,&seq[1],1) != 1)
   {
    return '\x1b';
   }

   if(seq[0] == '[')
   {
    if(seq[1] == '<')
    {
     char m_buf[16];
     uint8_t m_i=0;
     char m_c=0;
     char terminator=0;

     while(m_i < sizeof(m_buf)-1)
     {
      if(read(STDIN_FILENO,&m_c,1) != 1)
      {
       return '\x1b';
      }

      if(m_c == 'M' || m_c == 'm')
      {
       terminator=m_c;
       break;
      }
      m_buf[m_i++]=m_c;
     }

     if(terminator == 0)
     {
      return '\x1b';
     }

     m_buf[m_i]='\0';

     char* p=m_buf;
     char* end_p=NULL;
     long button=strtol(p,&end_p,10);

     if(end_p == p)
     {
      return read_key();
     }

     p=end_p;

     if(*p == ';')
     {
      ++p;
     }

     long m_col=strtol(p,&end_p,10);
     p=end_p;

     if(*p == ';')
     {
      ++p;
     }

     long m_row=strtol(p,&end_p,10);

     if(m_col > 0)
     {
      g_mouse_x=(int32_t)(m_col-1);
     }

     if(m_row > 0)
     {
      g_mouse_y=(int32_t)(m_row-1);
     }

     long base=button & ~(4L|8L|16L);

     if(button == 64)
     {
      return MOUSE_WHEEL_UP;
     }

     if(button == 65)
     {
      return MOUSE_WHEEL_DOWN;
     }

     long button_num=base & 3;
     uint8_t is_drag=(base & 32) != 0;

     if(terminator == 'm')
     {
      if(button_num == 0)
      {
       return MOUSE_LEFT_RELEASE;
      }
      return read_key();
     }

     if(is_drag)
     {
      if(button_num == 0)
      {
       return MOUSE_LEFT_DRAG;
      }
      return read_key();
     }

     if(button_num == 0)
     {
      return MOUSE_LEFT_PRESS;
     }

     if(button_num == 1)
     {
      return MOUSE_MIDDLE_CLICK;
     }

     if(button_num == 2)
     {
      return MOUSE_RIGHT_PRESS;
     }

     return read_key();
    }
    else if(seq[1] == '2')
    {
     char tail[8];

     if(read(STDIN_FILENO,&tail[0],1)!=1){return '\x1b';}

     if(tail[0] == '~')
     {
      return INSERT_KEY;
     }

     if(read(STDIN_FILENO,&tail[1],1)!=1){return '\x1b';}
     if(read(STDIN_FILENO,&tail[2],1)!=1){return '\x1b';}

     if(tail[0]=='0' && tail[1]=='0' && tail[2]=='~')
     {
      free(paste_stream_buffer);
      paste_stream_buffer=NULL;
      paste_stream_len=0;

      uint32_t cap=1024;
      paste_stream_buffer=malloc(cap);

      if(paste_stream_buffer == NULL)
      {
       die("malloc paste_stream_buffer [read_key]");
      }

      while(1)
      {
       char p_c=0;
       ssize_t r=0;

       while((r=read(STDIN_FILENO,&p_c,1)) != 1)
       {
        if(r == -1 && errno != EAGAIN && errno != EINTR)
        {
         die("read [read_key]");
        }
       }

       if(paste_stream_len+1 >= cap)
       {
        cap*=2;
        char* temp=realloc(paste_stream_buffer,cap);

        if(temp == NULL)
        {
         die("realloc paste_stream_buffer [read_key]");
        }
        paste_stream_buffer=temp;
       }

       paste_stream_buffer[paste_stream_len++]=p_c;

       if(paste_stream_len >= 6)
       {
        static const char end_marker[]="\x1b[201~";

        if(memcmp(paste_stream_buffer+paste_stream_len-6,end_marker,6) == 0)
        {
         paste_stream_len-=6;
         break;
        }
       }
      }
      return BRACKETED_PASTE;
     }
    }
    else if(seq[1]>='0' && seq[1]<='9')
    {
     if(read(STDIN_FILENO,&seq[2],1) != 1)
     {
      return '\x1b';
     }

     if(seq[2] == '~')
     {
      switch(seq[1])
      {
       case '1':
       {
        return HOME_KEY;
       }
       break;

       case '3':
       {
        return DEL_KEY;
       }
       break;

       case '4':
       {
        return END_KEY;
       }
       break;

       case '5':
       {
        return PAGE_UP;
       }
       break;

       case '6':
       {
        return PAGE_DOWN;
       }
       break;

       case '7':
       {
        return HOME_KEY;
       }
       break;

       case '8':
       {
        return END_KEY;
       }
       break;
      }
     }
    }
    else
    {
     switch(seq[1])
     {
      case 'A':
      {
       return ARROW_UP;
      }
      break;

      case 'B':
      {
       return ARROW_DOWN;
      }
      break;

      case 'C':
      {
       return ARROW_RIGHT;
      }
      break;

      case 'D':
      {
       return ARROW_LEFT;
      }
      break;

      case 'H':
      {
       return HOME_KEY;
      }
      break;

      case 'F':
      {
       return END_KEY;
      }
      break;
     }
    }
   }
   else if(seq[0] == 'O')
   {
    switch(seq[1])
    {
     case 'H':
     {
      return HOME_KEY;
     }
     break;

     case 'F':
     {
      return END_KEY;
     }
     break;
    }
   }
   return '\x1b';
  }
  else
  {
   return (uint16_t)c;
  }
 #endif
}

/*** syntax highlighting ***/
uint8_t syntax_to_color(uint8_t highlight)
{
 switch(highlight)
 {
  case H_COMMENT:
  case H_M_COMMENT:
  {
   return COMMENT_SYNTAX_COLOR;
  }
  break;

  case H_KEYWORD_1:
  {
   return KEYWORD_1_SYNTAX_COLOR;
  }
  break;

  case H_KEYWORD_2:
  {
   return KEYWORD_2_SYNTAX_COLOR;
  }
  break;

  case H_KEYWORD_3:
  {
   return KEYWORD_3_SYNTAX_COLOR;
  }
  break;

  case H_STRING:
  {
   return STRING_SYNTAX_COLOR;
  }
  break;

  case H_NUMBER:
  {
   return NUMBER_SYNTAX_COLOR;
  }
  break;

  case H_MATCH:
  {
   return MATCH_SYNTAX_COLOR;
  }
  break;

  default:
  {
   return DEFAULT_SYNTAX_COLOR;
  }
  break;
 }
}

void select_syntax_highlight()
{
 E.syntax=NULL;

 if(E.file_name == NULL)
 {
  return;
 }

 char* extention=strrchr(E.file_name,'.');
 uint8_t i=0;
 
 for(i=0;i < H_DB_ENTRIES;++i)
 {
  syntax* s=&H_DB[i];
  uint8_t j=0;

  while(s->file_ext[j])
  {
   uint8_t is_extention=(s->file_ext[j][0] == '.');

   if((is_extention && extention && !strcmp(extention,s->file_ext[j])) || (!is_extention && strstr(E.file_name,s->file_ext[j])))
   {
    E.syntax=s;

    int32_t file_row=0;

    for(file_row=0;file_row < E.num_rows;++file_row)
    {
     update_syntax(&E.row[file_row]);
    }

    return;
   }
   ++j;
  }
 }
}

uint8_t is_separator(int16_t c)
{
 return isspace((unsigned char)c) || c == '\0' || strchr(",.()+-/*=~%<>[]{}:;",c) != NULL;
}

void update_syntax(e_row* row)
{
 while(1) 
 {
  if(row->r_size == 0)
  {
   row->highlight=NULL;
   row->h_open_comment=0;
  }
  else
  {
   if(row->highlight != NULL)
   {
    highlight_arena_wasted+=(uint64_t)row->r_size;
   }

   row->highlight=arena_push(highlight_arena,(uint64_t)row->r_size,0);
   memset(row->highlight,H_NORMAL,row->r_size);
  }

  if(render_arena_wasted+highlight_arena_wasted > ROW_ARENA_COMPACT_THRESHOLD)
  {
   compact_row_arenas();
  }

  if(E.syntax == NULL)
  {
   return;
  }

  const char* const* keywords=E.syntax->keywords;
  const uint8_t* keywords_len=E.syntax->keywords_len;
  const uint8_t* keywords_syntax_color=E.syntax->keywords_syntax_color;

  const char* s_l_c_s=E.syntax->single_line_comment_start;
  uint8_t s_l_c_s_len=0;

  if(s_l_c_s == NULL || s_l_c_s[0] == '\0')
  {
   s_l_c_s=NULL;
  }
  else
  {
   s_l_c_s_len=(uint8_t)strlen(s_l_c_s);
  }

  const char* m_l_c_s=E.syntax->multi_line_comment_start;
  uint8_t m_l_c_s_len=0;

  if(m_l_c_s == NULL || m_l_c_s[0] == '\0')
  {
   m_l_c_s=NULL;
  }
  else
  {
   m_l_c_s_len=(uint8_t)strlen(m_l_c_s);
  }

  const char* m_l_c_e=E.syntax->multi_line_comment_end;
  uint8_t m_l_c_e_len=0;

  if(m_l_c_e == NULL || m_l_c_e[0] == '\0')
  {
   m_l_c_e=NULL;
  }
  else
  {
   m_l_c_e_len=(uint8_t)strlen(m_l_c_e);
  }

  uint8_t prev_separator=1;
  uint8_t in_string=0;
  uint8_t in_comment=(row->id > 0 && E.row[row->id-1].h_open_comment);

  int32_t i=0;
  int32_t j=0;

  while(i < row->r_size)
  {
   char c=row->render[i];
   uint8_t prev_highlight=0;

   if(i > 0)
   {
    prev_highlight=row->highlight[i-1];
   }
   else
   {
    prev_highlight=H_NORMAL;
   }

   if(s_l_c_s_len && !in_string && !in_comment)
   {
    if(i+s_l_c_s_len <= row->r_size && !strncmp(&row->render[i],s_l_c_s,s_l_c_s_len))
    {
     memset(&row->highlight[i],H_COMMENT,row->r_size-i);
     break;
    }
   }

   if(m_l_c_s_len && m_l_c_e_len && !in_string)
   {
    if(in_comment)
    {
     row->highlight[i]=H_M_COMMENT;

     if(i+m_l_c_e_len <= row->r_size && !strncmp(&row->render[i],m_l_c_e,m_l_c_e_len))
     {
      memset(&row->highlight[i],H_M_COMMENT,m_l_c_e_len);
      i+=m_l_c_e_len;
      in_comment=0;
      prev_separator=0;
      continue;
     }
     else
     {
      ++i;
      continue;
     }
    }
    else if(i+m_l_c_s_len <= row->r_size && !strncmp(&row->render[i],m_l_c_s,m_l_c_s_len))
    {
     memset(&row->highlight[i],H_M_COMMENT,m_l_c_s_len);
     i+=m_l_c_s_len;
     in_comment=1;
     continue;
    }
   }

   if(in_string)
   {
    row->highlight[i]=H_STRING;

    if(c == '\\' && i+1 < row->r_size)
    {
     row->highlight[i+1]=H_STRING;
     i+=2;
     continue;
    }

    if(c == in_string)
    {
     in_string=0;
    }
    ++i;
    prev_separator=1;
    continue;
   }
   else
   {
    if(c == '"' || c == '\'')
    {
     in_string=c;
     row->highlight[i]=H_STRING;
     ++i;
     continue;
    }
   }

   uint8_t number_start=(isdigit((unsigned char)c) && prev_separator);
   uint8_t number_continue=(prev_highlight == H_NUMBER && (isdigit((unsigned char)c) || c == '.'));

   if(number_start || number_continue)
   {
    row->highlight[i]=H_NUMBER;
    ++i;
    prev_separator=0;
    continue;
   }

   if(prev_separator)
   {
    for(j=0;keywords[j];++j)
    {
     uint8_t k_len=keywords_len[j];

     if(k_len == 0)
     {
      continue;
     }

     if(i+k_len <= row->r_size && !strncmp(&row->render[i],keywords[j],k_len) && is_separator(row->render[i+k_len]))
     {
      uint8_t h_type;
      uint8_t color=keywords_syntax_color[j];

      if(color == 1)
      {
       h_type=H_KEYWORD_1;
      }
      else if(color == 2)
      {
       h_type=H_KEYWORD_2;
      }
      else
      {
       h_type=H_KEYWORD_3;
      }
      memset(&row->highlight[i],h_type,k_len);
      i+=k_len;
      break;
     }
    }

    if(keywords[j] != NULL)
    {
     prev_separator=0;
     continue;
    }
   }

   prev_separator=is_separator(c);
   ++i;
  }

  uint8_t changed=(row->h_open_comment != in_comment);

  row->h_open_comment=in_comment;

  if(changed && row->id+1 < E.num_rows)
  {
   row=&E.row[row->id+1];
  }
  else
  {
   break;
  }
 }
}

/*** row operations ***/
uint8_t get_utf8_char_placement_length(e_row* row,int32_t c_x)
{
 if(c_x >= row->size)
 {
  return 1;
 }
 unsigned char c=(unsigned char)row->characters[c_x];
 
 if(c < 0x80)
 {
  return 1;
 }
 else if((c & 0xE0) == 0xC0)
 {
  return 2;
 }
 else if((c & 0xF0) == 0xE0)
 {
  return 3;
 }
 else if((c & 0xF8) == 0xF0)
 {
  return 4;
 }
 else
 {
  return 1;
 }
}

int32_t snap_to_utf8_start(e_row* row,int32_t c_x)
{
 if(!row || c_x <= 0 || c_x >= row->size)
 {
  return c_x;
 }

 int32_t limit=c_x-3;

 if(limit < 0)
 {
  limit=0;
 }
 
 while(c_x > limit && ((unsigned char)row->characters[c_x] & 0xC0) == 0x80)
 {
  --c_x;
 }
 return c_x;
}

uint8_t utf8_seq_len_valid(e_row* row,int32_t c_x)
{
 uint8_t len=get_utf8_char_placement_length(row,c_x);

 if(len == 1)
 {
  return 1;
 }

 if(c_x+len > row->size)
 {
  return 0;
 }

 uint8_t i=1;

 for(i=1;i < len;++i)
 {
  if(((unsigned char)row->characters[c_x+i] & 0xC0) != 0x80)
  {
   return 0;
  }
 }

 return len;
}

int32_t utf8_safe_trunc_len(const char* s,int32_t max_len)
{
 int32_t len=(int32_t)strlen(s);

 if(max_len < 0)
 {
  return 0;
 }

 if(len <= max_len)
 {
  return len;
 }

 int32_t cut=max_len;

 while(cut > 0 && ((unsigned char)s[cut] & 0xC0) == 0x80)
 {
  --cut;
 }
 return cut;
}

static uint8_t get_render_control_type(unsigned char c)
{
 if(c < 0x20 || c == 0x7F)
 {
  return 1;
 }
 if(c >= 0x80 && c <= 0x9F)
 {
  return 2;
 }
 return 0;
}

int32_t row_c_x_to_r_x(e_row* row,int32_t c_x)
{
 int32_t r_x=0;
 int32_t i=0;

 while(i < c_x && i < row->size)
 {
  unsigned char c=(unsigned char)row->characters[i];
  uint8_t ctrl_type=get_render_control_type(c);

  if(c == '\t')
  {
   r_x |= (TAB_STOP-1);
   ++r_x;
   ++i;
  }
  else if(ctrl_type == 1)
  {
   r_x += 6;
   ++i;
  }
  else if(ctrl_type == 2)
  {
   r_x += 4;
   ++i;
  }
  else if(c > 127)
  {
   uint8_t seq_len=E.utf8_output ? utf8_seq_len_valid(row,i) : 0;
   uint8_t treat_as_hex=0;

   if(seq_len > 1)
   {
    uint32_t c_p=utf8_decode_buf(row->characters,i,row->size,seq_len);
    if(c_p >= 0x80 && c_p <= 0x9F)
    {
     treat_as_hex=1;
    }
   }

   if(seq_len > 1 && !treat_as_hex)
   {
    uint32_t c_p=utf8_decode_buf(row->characters,i,row->size,seq_len);
    r_x+=code_point_is_wide(c_p) ? 2 : 1;
    i+=seq_len;
   }
   else
   {
    r_x+=4;
    ++i;
   }
  }
  else
  {
   ++r_x;
   ++i;
  }
 }

 return r_x;
}

int32_t row_r_x_to_c_x(e_row* row,int32_t r_x)
{
 int32_t current_r_x=0;
 int32_t c_x=0;

 while(c_x < row->size)
 {
  int32_t step=1;
  unsigned char c=(unsigned char)row->characters[c_x];
  uint8_t ctrl_type=get_render_control_type(c);

  if(row->characters[c_x] == '\t')
  {
   current_r_x=(current_r_x | (TAB_STOP-1))+1;
  }
  else if(ctrl_type == 1)
  {
   current_r_x+=6;
  }
  else if(ctrl_type == 2)
  {
   current_r_x+=4;
  }
  else if((unsigned char)row->characters[c_x] > 127)
  {
   uint8_t seq_len=E.utf8_output ? utf8_seq_len_valid(row,c_x) : 0;
   uint8_t treat_as_hex=0;

   if(seq_len > 1)
   {
    uint32_t c_p=utf8_decode_buf(row->characters,c_x,row->size,seq_len);

    if(c_p >= 0x80 && c_p <= 0x9F)
    {
     treat_as_hex=1;
    }
   }
   if(seq_len > 1 && !treat_as_hex)
   {
    uint32_t cp=utf8_decode_buf(row->characters,c_x,row->size,seq_len);
    current_r_x+=code_point_is_wide(cp) ? 2 : 1;
    step=seq_len;
   }
   else
   {
    current_r_x+=4;
   }
  }
  else
  {
   ++current_r_x;
  }
  
  if(current_r_x > r_x)
  {
   return c_x;
  }

  c_x+=step;
 }

 return c_x;
}

static void row_gap_move_to(e_row* row,int32_t pos)
{
 if(pos == row->gap_start)
 {
  return;
 }

 if(pos < row->gap_start)
 {
  int32_t n=row->gap_start-pos;

  memmove(&row->characters[row->gap_end-n],&row->characters[pos],n);
  row->gap_start-=n;
  row->gap_end-=n;
 }
 else
 {
  int32_t n=pos-row->gap_start;

  memmove(&row->characters[row->gap_start],&row->characters[row->gap_end],n);
  row->gap_start+=n;
  row->gap_end+=n;
 }
}

static void row_gap_reserve(e_row* row,int32_t extra)
{
 if(row->gap_end-row->gap_start >= extra)
 {
  return;
 }

 uint64_t needed=(uint64_t)row->size+(uint64_t)extra;
 uint64_t new_buf_size=row->buf_size == 0 ? 16 : (uint64_t)row->buf_size;

 while(new_buf_size < needed)
 {
  new_buf_size<<=1;

  if(new_buf_size > (uint64_t)INT32_MAX)
  {
   new_buf_size=(uint64_t)INT32_MAX;
   break;
  }
 }

 if(new_buf_size < needed)
 {
  die("row buffer size limit exceeded [row_gap_reserve]");
 }

 char* new_buf=realloc(row->characters,new_buf_size);

 if(new_buf == NULL)
 {
  die("realloc [row_gap_reserve]");
 }

 int32_t tail_len=row->buf_size-row->gap_end;
 int32_t new_gap_end=(int32_t)new_buf_size-tail_len;

 memmove(&new_buf[new_gap_end],&new_buf[row->gap_end],(size_t)tail_len);

 row->characters=new_buf;
 row->gap_end=new_gap_end;
 row->buf_size=(int32_t)new_buf_size;
}

static void row_gap_flatten(e_row* row)
{
 row_gap_move_to(row,row->size);
}

static void row_truncate(e_row* row,int32_t new_size)
{
 row_gap_flatten(row);
 row->gap_start=new_size;
 row->size=new_size;
}

void seg_bufs_ensure(int32_t needed)
{
 if(needed > seg_bufs_cap)
 {
  int32_t new_cap=seg_bufs_cap == 0 ? SIZE_LIMIT : seg_bufs_cap;

  while(new_cap < needed)
  {
   new_cap<<=1;
  }

  int32_t* new_start=realloc(seg_start_buf,(size_t)new_cap*sizeof(int32_t));

  if(new_start == NULL)
  {
   die("realloc [seg_bufs_ensure] start");
  }

  uint8_t* new_type=realloc(seg_type_buf,(size_t)new_cap*sizeof(uint8_t));

  if(new_type == NULL)
  {
   die("realloc [seg_bufs_ensure] type");
  }

  seg_start_buf=new_start;
  seg_type_buf=new_type;
  seg_bufs_cap=new_cap;
 }
}

void update_row(e_row* row)
{
 int32_t i=0;
 int32_t index=0;
 uint8_t spaces_needed=0;

 row_gap_flatten(row);

 int32_t s_count=0;
 int32_t needed=row->size+1;

 seg_bufs_ensure(needed);

 int32_t* s_start=seg_start_buf;
 uint8_t* s_type=seg_type_buf;

 if(row->render != NULL)
 {
  render_arena_wasted+=(uint64_t)row->r_size+1;
 }

 uint64_t max_render_size=(uint64_t)row->size*ROW_RENDER_MAX_EXPANSION+1;

 row->render=arena_push(render_arena,max_render_size,0);

 for(i=0;i < row->size;++i)
 {
  unsigned char c=(unsigned char)row->characters[i];
  uint8_t ctrl_type=get_render_control_type(c);

  if(c == '\t')
  {
   row->render[index++]=' ';
   spaces_needed=(TAB_STOP-1)-((index-1) & (TAB_STOP-1));

   while(spaces_needed--)
   {
    row->render[index++]=' ';
   }
  }
  else if(ctrl_type == 1)
  {
   char symbol=0;

   if(c <= 26)
   {
    symbol='@'+c;
   }
   else
   {
    symbol='?';
   }

   s_start[s_count]=index;
   s_type[s_count]=H_CTRL;
   ++s_count;

   snprintf(&row->render[index],7,"Ctrl+%c",symbol);
   index+=6;
  }
  else if(ctrl_type == 2)
  {
   s_start[s_count]=index;
   s_type[s_count]=H_HEX;
   ++s_count;
   snprintf(&row->render[index],5,"<%02x>",c);
   index+=4;
  }
  else if(c > 127)
  {
   uint8_t seq_len=E.utf8_output ? utf8_seq_len_valid(row,i) : 0;

   if(seq_len > 1)
   {
    uint32_t c_p=utf8_decode_buf(row->characters,i,row->size,seq_len);

    if(c_p >= 0x80 && c_p <= 0x9F)
    {
     seq_len=0;
    }
   }

   if(seq_len > 1)
   {
    memcpy(&row->render[index],&row->characters[i],seq_len);
    index+=seq_len;
    i+=seq_len-1;
   }
   else
   {
    s_start[s_count]=index;
    s_type[s_count]=H_HEX;
    ++s_count;

    snprintf(&row->render[index],5,"<%02x>",c);
    index+=4;
   }
  }
  else
  {
   row->render[index++]=row->characters[i];
  }
 }
 row->render[index]='\0';
 row->r_size=index;

 update_syntax(row);

 for(i=0;i < s_count;++i)
 {
  uint8_t s_len=(s_type[i] == H_CTRL) ? 6 : 4;
  memset(&row->highlight[s_start[i]],s_type[i],s_len);
 }
 row->wrap_epoch=-1;
}

void insert_row(int32_t n,char* s,uint32_t len)
{
 if(n < 0 || n > E.num_rows)
 {
  return;
 }

 if((uint32_t)E.num_rows >= row_capacity)
 {
  uint32_t new_cap=0;

  if(row_capacity == 0)
  {
   new_cap=1;
  }
  else
  {
   new_cap=row_capacity<<1;
  }

  e_row* new_rows=realloc(E.row,sizeof(e_row)*new_cap);

  if(new_rows == NULL)
  {
   die("realloc [insert_row]");
  }

  E.row=new_rows;
  row_capacity=new_cap;
 }

 memmove(&E.row[n+1],&E.row[n],sizeof(e_row)*(E.num_rows-n));

 int32_t i=0;

 for(i=n+1;i <= E.num_rows;++i)
 {
  ++E.row[i].id;
 }

 E.row[n].id=n;
 E.row[n].size=len;
 E.row[n].buf_size=len < 16 ? 16 : len+1;
 E.row[n].characters=malloc(E.row[n].buf_size);

 if(E.row[n].characters == NULL)
 {
  die("malloc [insert_row]");
 }

 memcpy(E.row[n].characters,s,len);

 E.row[n].gap_start=len;
 E.row[n].gap_end=E.row[n].buf_size;

 E.row[n].render=NULL;
 E.row[n].highlight=NULL;
 E.row[n].wrap_starts=NULL;
 E.row[n].r_size=0;
 E.row[n].wrap_seg_count=0;
 E.row[n].wrap_starts_cap=0;
 E.row[n].wrap_epoch=-1;
 E.row[n].h_open_comment=0;

 ++E.num_rows;
 update_line_num_width();

 update_row(&E.row[n]);

 E.dirty=1;
}

void row_append_string(e_row* row,char* s,uint32_t len)
{
 row_gap_reserve(row,(int32_t)len);
 row_gap_move_to(row,row->size);

 memcpy(&row->characters[row->gap_start],s,len);

 row->gap_start+=len;
 row->size+=len;

 update_row(row);
 E.dirty=1;
}

static void row_delete_range(e_row* row,int32_t from,int32_t to)
{
 if(from < 0)
 {
  from=0;
 }

 if(to > row->size)
 {
  to=row->size;
 }

 if(from >= to)
 {
  return;
 }

 row_gap_flatten(row);

 int32_t tail_len=row->size-to;

 memmove(&row->characters[from],&row->characters[to],(size_t)tail_len);

 row->size-=(to-from);
 row->gap_start=row->size;

 update_row(row);
 E.dirty=1;
}

void del_row(int32_t n)
{
 if(n < 0 || n >= E.num_rows)
 {
  return;
 }

 free_row(&E.row[n]);

 memmove(&E.row[n],&E.row[n+1],sizeof(e_row)*(E.num_rows-n-1));

 int32_t i=0;

 for(i=n;i < E.num_rows-1;++i)
 {
  --E.row[i].id;
 }

 --E.num_rows;

 if(n < E.num_rows)
 {
  update_row(&E.row[n]);
 }

 update_line_num_width();
 E.dirty=1;
}

void del_row_range(int32_t low,int32_t high_inclusive)
{
 if(low < 0 || high_inclusive >= E.num_rows || low > high_inclusive)
 {
  return;
 }

 int32_t removed=high_inclusive-low+1;
 int32_t r=0;

 for(r=low;r <= high_inclusive;++r)
 {
  free_row(&E.row[r]);
 }

 int32_t tail_count=E.num_rows-high_inclusive-1;

 if(tail_count > 0)
 {
  memmove(&E.row[low],&E.row[high_inclusive+1],sizeof(e_row)*(size_t)tail_count);
 }

 E.num_rows-=removed;

 for(r=low;r < E.num_rows;++r)
 {
  E.row[r].id-=removed;
 }

 if(low < E.num_rows)
 {
  update_row(&E.row[low]);
 }

 update_line_num_width();
 E.dirty=1;
}

void row_insert_char(e_row* row,int32_t n,int16_t c)
{
 if(n < 0 || n > row->size)
 {
  n=row->size;
 }

 row_gap_reserve(row,1);
 row_gap_move_to(row,n);

 row->characters[row->gap_start]=(char)c;
 ++row->gap_start;
 ++row->size;

 update_row(row);
 E.dirty=1;
}

void row_del_char(e_row* row,int32_t n)
{
 if(n < 0 || n >= row->size)
 {
  return;
 }

 row_gap_move_to(row,n);
 ++row->gap_end;
 --row->size;

 update_row(row);
 E.dirty=1;
}

void row_insert_string(e_row* row,int32_t n,char* s,uint32_t len)
{
 if(n < 0 || n > row->size)
 {
  n=row->size;
 }

 row_gap_reserve(row,(int32_t)len);
 row_gap_move_to(row,n);

 memcpy(&row->characters[row->gap_start],s,len);

 row->gap_start+=len;
 row->size+=len;

 update_row(row);
 E.dirty=1;
}

void free_row(e_row* row)
{
 if(row->render != NULL)
 {
  render_arena_wasted+=(uint64_t)row->r_size+1;
 }

 if(row->highlight != NULL)
 {
  highlight_arena_wasted+=(uint64_t)row->r_size;
 }

 free(row->characters);
 free(row->wrap_starts);
}

/*** editor operations ***/
void insert_char(int16_t c)
{
 if(E.c_y == E.num_rows)
 {
  insert_row(E.num_rows,"",0);
 }

 row_insert_char(&E.row[E.c_y],E.c_x,c);

 ++E.c_x;
}

void insert_utf8_char(char* bytes, int len)
{
 if(len <= 0 || len > 4)
 {
  return;
 }

 actions action;
 memset(&action,0,sizeof(action));
 action.type=USER_ACTION_INSERT_CHAR;
 action.c_x=E.c_x;
 action.c_y=E.c_y;
 action.c_len=(uint8_t)len;
 memcpy(action.c,bytes,len);
 action.row_text=NULL;
 undo_push(&action);

 for(int i=0;i < len;++i)
 {
  insert_char((unsigned char)bytes[i]);
 }
}

void insert_new_line()
{
 if(E.c_y == E.num_rows)
 {
  insert_row(E.num_rows,"",0);
  E.c_x=0;
  return;
 }

 if(E.c_x == 0)
 {
  insert_row(E.c_y,"",0);
 }
 else
 {
  e_row* row=&E.row[E.c_y];
  insert_row(E.c_y+1,&row->characters[E.c_x],row->size-E.c_x);
  row=&E.row[E.c_y];
  row_truncate(row,E.c_x);
  update_row(row);
 }
 ++E.c_y;
 E.c_x=0;
}

void insert_text_range(char* text,uint32_t len)
{
 if(len == 0)
 {
  return;
 }

 if(E.c_y == E.num_rows)
 {
  insert_row(E.num_rows,"",0);
 }

 uint32_t i=0;
 uint32_t newline_count=0;

 for(i=0;i < len;++i)
 {
  if(text[i] == '\n')
  {
   ++newline_count;
  }
 }
 
 int32_t original_c_x=E.c_x;
 int32_t tail_len=E.row[E.c_y].size-original_c_x;
 char* tail_copy=NULL;

 if(tail_len > 0)
 {
  tail_copy=malloc((size_t)tail_len);

  if(tail_copy == NULL)
  {
   die("malloc (tail) [insert_text_range]");
  }

  memcpy(tail_copy,&E.row[E.c_y].characters[original_c_x],(size_t)tail_len);
 }

 row_truncate(&E.row[E.c_y],original_c_x);

 uint32_t seg_start=0;
 int32_t insert_y=E.c_y;
 int32_t last_row_index=E.c_y;

 for(i=0;i <= len;++i)
 {
  if(i < len && text[i] != '\n')
  {
   continue;
  }

  uint32_t seg_len=i-seg_start;

  if(insert_y == E.c_y)
  {
   row_append_string(&E.row[insert_y],&text[seg_start],seg_len);
   last_row_index=insert_y;
  }
  else
  {
   insert_row(insert_y,&text[seg_start],seg_len);
   last_row_index=insert_y;
  }
  seg_start=i+1;
  ++insert_y;
 }

 if(tail_len > 0)
 {
  e_row* last_row=&E.row[last_row_index];
  int32_t pos_before_tail=last_row->size;

  row_append_string(last_row,tail_copy,(uint32_t)tail_len);

  E.c_y=last_row_index;
  E.c_x=pos_before_tail;
 }
 else
 {
  e_row* last_row=&E.row[last_row_index];
  E.c_y=last_row_index;
  E.c_x=last_row->size;
 }

 free(tail_copy);
}

void del_char()
{
 if(E.c_y == E.num_rows)
 {
  return;
 }

 if(E.c_x == 0 && E.c_y == 0)
 {
  return;
 }

 e_row* row=&E.row[E.c_y];

 if(E.c_x > 0)
 {
  int32_t start_c_x=snap_to_utf8_start(row,E.c_x-1);
  int32_t bytes_to_delete=E.c_x-start_c_x;

  while(bytes_to_delete > 0)
  {
   row_del_char(row,start_c_x);
   --E.c_x;
   --bytes_to_delete;
  }
 }
 else
 {
  E.c_x=E.row[E.c_y-1].size;
  row_append_string(&E.row[E.c_y-1],row->characters,row->size);
  del_row(E.c_y);
  --E.c_y;
 }
}

void delete_char_range(int32_t x_1,int32_t y_1,int32_t x_2,int32_t y_2)
{
 if(y_1 == y_2)
 {
  row_delete_range(&E.row[y_1],x_1,x_2);
 }
 else
 {
  int32_t end_tail_len=E.row[y_2].size-x_2;
  char* end_tail_copy=NULL;

  if(end_tail_len > 0)
  {
   end_tail_copy=malloc((size_t)end_tail_len);

   if(end_tail_copy == NULL)
   {
    die("malloc (tail) [delete_char_range]");
   }

   memcpy(end_tail_copy,&E.row[y_2].characters[x_2],(size_t)end_tail_len);
  }

  del_row_range(y_1+1,y_2);

  row_truncate(&E.row[y_1],x_1);

  if(end_tail_len > 0)
  {
   row_append_string(&E.row[y_1],end_tail_copy,(uint32_t)end_tail_len);
  }
  else
  {
   update_row(&E.row[y_1]);
  }

  free(end_tail_copy);
 }

 E.c_x=x_1;
 E.c_y=y_1;
}

void action_free(actions* action)
{
 uint8_t action_type=(action->type == USER_ACTION_JOIN_LINES || action->type == USER_ACTION_RANGE_DELETE || action->type == USER_ACTION_ROW_DELETE || action->type == USER_ACTION_ROW_INSERT || action->type == USER_ACTION_RANGE_INSERT);

 if(action_type && action->row_text != NULL)
 {
  free(action->row_text);
  action->row_text=NULL;
 }
}

void undo_push(actions* action)
{
 if(E.undo_top == SIZE_LIMIT-1)
 {
  action_free(&E.undo_stack[0]);
  memmove(&E.undo_stack[0],&E.undo_stack[1],sizeof(actions)*(SIZE_LIMIT-1));
  --E.undo_top;
  E.saved_undo_top=-2;
 }

 E.undo_stack[++E.undo_top]=*action;

 while(E.redo_top >= 0)
 {
  action_free(&E.redo_stack[E.redo_top--]);
 }
}

void undo()
{
 uint32_t i=0;

 if(E.undo_top < 0)
 {
  set_status_message(ACTION_MSG_COLOR,"Nothing to undo");
  return;
 }

 actions* action=&E.undo_stack[E.undo_top];

 switch(action->type)
 {
  case USER_ACTION_INSERT_CHAR:
  {
   for(int i=action->c_len-1;i >= 0;--i)
   {
    row_del_char(&E.row[action->c_y],action->c_x);
   }
   E.c_x=action->c_x;
   E.c_y=action->c_y;
  }
  break;

  case USER_ACTION_DEL_CHAR:
  {
   int32_t insert_at=action->c_x-action->c_len;

   for(i=0;i < action->c_len;++i)
   {
    row_insert_char(&E.row[action->c_y],insert_at+i,(int16_t)(unsigned char)action->c[i]);
   }

   E.c_x=action->c_x;
   E.c_y=action->c_y;
  }
  break;

  case USER_ACTION_INSERT_NEWLINE:
  {
   if(action->c_x == 0)
   {
    del_row(action->c_y);

    if(action->c_y < E.num_rows)
    {
     update_row(&E.row[action->c_y]);
    }
   }
   else
   {
    row_append_string(&E.row[action->c_y],E.row[action->c_y+1].characters,E.row[action->c_y+1].size);
    del_row(action->c_y+1);
   }
   E.c_x=action->c_x;
   E.c_y=action->c_y;
  }
  break;

  case USER_ACTION_JOIN_LINES:
  {
   row_truncate(&E.row[action->c_y-1],action->join_col);

   update_row(&E.row[action->c_y-1]);
   insert_row(action->c_y,action->row_text != NULL ? action->row_text : "",action->row_len);

   E.c_x=0;
   E.c_y=action->c_y;
  }
  break;

  case USER_ACTION_ROW_INSERT:
  {
   del_row(action->c_y);

   if(action->c_y < E.num_rows)
   {
    update_row(&E.row[action->c_y]);
   }

   E.c_x=0;

   if(E.c_y >= E.num_rows && E.num_rows > 0)
   {
    E.c_y=E.num_rows-1;
   }
   else
   {
    E.c_y=action->c_y > 0 ? action->c_y-1 : 0;
   }
  }
  break;

  case USER_ACTION_ROW_DELETE:
  {
   insert_row(action->c_y,action->row_text != NULL ? action->row_text : "",action->row_len);

   E.c_x=0;
   E.c_y=action->c_y;
  }
  break;

  case USER_ACTION_RANGE_INSERT:
  {
   delete_char_range(action->c_x,action->c_y,action->c_x_end,action->c_y_end);
  }
  break;

  case USER_ACTION_RANGE_DELETE:
  {
   E.c_x=action->c_x;
   E.c_y=action->c_y;

   insert_text_range(action->row_text,action->row_len);

   E.c_x=action->c_x;
   E.c_y=action->c_y;
  }
  break;
 }

 if(E.redo_top < SIZE_LIMIT-1)
 {
  E.redo_stack[++E.redo_top]=*action;
  action->row_text=NULL;
 }
 else
 {
  action_free(action);
  action->row_text=NULL;
 }

 --E.undo_top;

 if(E.undo_top == E.saved_undo_top)
 {
  E.dirty=0;
 }
 else
 {
  E.dirty=1;
 }

 set_status_message(ACTION_MSG_COLOR,"Undo  u:%d/%d  r:%d/%d",E.undo_top+1,SIZE_LIMIT,E.redo_top+1,SIZE_LIMIT);
}

void redo()
{
 uint32_t i=0;

 if(E.redo_top < 0)
 {
  set_status_message(ACTION_MSG_COLOR,"Nothing to redo");
  return;
 }

 actions* action=&E.redo_stack[E.redo_top];

 switch(action->type)
 {
  case USER_ACTION_INSERT_CHAR:
  {
   if(action->c_y == E.num_rows)
   {
    insert_row(E.num_rows,"",0);
   }

   for(int i=0;i < action->c_len;++i)
   {
    row_insert_char(&E.row[action->c_y],action->c_x+i,(unsigned char)action->c[i]);
   }
   E.c_x=action->c_x+action->c_len;
   E.c_y=action->c_y;
  }
  break;

  case USER_ACTION_DEL_CHAR:
  {
   int32_t del_at=action->c_x-action->c_len;

   for(i=0;i < action->c_len;++i)
   {
    row_del_char(&E.row[action->c_y],del_at);
   }

   E.c_x=del_at;
   E.c_y=action->c_y;
  }
  break;

  case USER_ACTION_INSERT_NEWLINE:
  {
   E.c_x=action->c_x;
   E.c_y=action->c_y;
   insert_new_line();
  }
  break;

  case USER_ACTION_JOIN_LINES:
  {
   E.c_x=0;
   E.c_y=action->c_y;
   del_char();
  }
  break;

  case USER_ACTION_ROW_INSERT:
  {
   insert_row(action->c_y,action->row_text != NULL ? action->row_text : "",action->row_len);
   E.c_x=0;
   E.c_y=action->c_y;
  }
  break;

  case USER_ACTION_ROW_DELETE:
  {
   del_row(action->c_y);

   if(action->c_y < E.num_rows)
   {
    update_row(&E.row[action->c_y]);
   }

   E.c_x=0;

   if(E.c_y >= E.num_rows && E.num_rows > 0)
   {
    E.c_y=E.num_rows-1;
   }
  }
  break;

  case USER_ACTION_RANGE_INSERT:
  {
   E.c_x=action->c_x;
   E.c_y=action->c_y;

   insert_text_range(action->row_text,action->row_len);
  }
  break;

  case USER_ACTION_RANGE_DELETE:
  {
   delete_char_range(action->c_x,action->c_y,action->c_x_end,action->c_y_end);
  }
  break;
 }

 if(E.undo_top < SIZE_LIMIT-1)
 {
  E.undo_stack[++E.undo_top]=*action;
  action->row_text=NULL;
 }
 else
 {
  action_free(action);
  action->row_text=NULL;
 }

 --E.redo_top;

 if(E.undo_top == E.saved_undo_top)
 {
  E.dirty=0;
 }
 else
 {
  E.dirty=1;
 }

 set_status_message(ACTION_MSG_COLOR,"Redo  u:%d/%d  r:%d/%d",E.undo_top+1,SIZE_LIMIT,E.redo_top+1,SIZE_LIMIT);
}

void get_selection_bounds(int32_t* x_1,int32_t* y_1,int32_t* x_2,int32_t* y_2)
{
 int32_t a_x=E.select_anchor_x;
 int32_t a_y=E.select_anchor_y;
 int32_t c_x=E.c_x;
 int32_t c_y=E.c_y;
 int32_t l_x=a_x;
 int32_t l_y=a_y;
 int32_t r_x=c_x;
 int32_t r_y=c_y;

 if((a_x > c_x && a_y == c_y) || a_y > c_y)
 {
  l_x=c_x;
  l_y=c_y;
  r_x=a_x;
  r_y=a_y;
 }

 int32_t r_row_size=0;

 if(r_y < E.num_rows)
 {
  r_row_size=E.row[r_y].size;
 }

 if(r_x < r_row_size)
 {
  r_x+=get_utf8_char_placement_length(&E.row[r_y],r_x);
 }
 else
 {
  r_x=r_row_size;
 }

 *x_1=l_x;
 *y_1=l_y;
 *x_2=r_x;
 *y_2=r_y;
}

uint8_t is_selected(int32_t row,int32_t col)
{
 if(!E.select_mode)
 {
  return 0;
 }

 if(E.select_mode == SELECT_ROW)
 {
  return row == E.c_y;
 }

 int32_t x_1=0;
 int32_t y_1=0;
 int32_t x_2=0;
 int32_t y_2=0;

 get_selection_bounds(&x_1,&y_1,&x_2,&y_2);

 if(row < y_1 || row > y_2)
 {
  return 0;
 }

 if(row == y_1 && col < x_1)
 {
  return 0;
 }

 if(row == y_2 && col >= x_2)
 {
  return 0;
 }

 return 1;
}

void osc52_copy(const char* text,uint32_t len)
{
 if(len > 74000)
 {
  set_status_message(ERROR_MSG_COLOR,"Selection too large for OSC 52 clipboard");
  return;
 }

 static const char b64_table[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

 uint32_t out_len=4*((len+2)/3);
 char* encoded=malloc(out_len+1);

 if(encoded == NULL)
 {
  return;
 }

 uint32_t i=0;
 uint32_t j=0;

 while(i < len)
 {
  uint32_t a=i < len ? (unsigned char)text[i++] : 0;
  uint32_t b=i < len ? (unsigned char)text[i++] : 0;
  uint32_t c=i < len ? (unsigned char)text[i++] : 0;
  uint32_t triple=(a << 16)+(b << 8)+c;

  encoded[j++]=b64_table[(triple >> 18) & 0x3F];
  encoded[j++]=b64_table[(triple >> 12) & 0x3F];
  encoded[j++]=b64_table[(triple >> 6) & 0x3F];
  encoded[j++]=b64_table[triple & 0x3F];
 }

 uint32_t mod=len % 3;

 if(mod == 1)
 {
  encoded[out_len-1]='=';
  encoded[out_len-2]='=';
 }
 else if(mod == 2)
 {
  encoded[out_len-1]='=';
 }

 encoded[out_len]='\0';

 const char* clear_seq="\x1b]52;c;\x1b\\";
 uint32_t clear_len=9;

 write_all(STDOUT_FILENO,clear_seq,clear_len);

 char* seq=malloc(out_len+10);

 if(seq != NULL)
 {
  int32_t seq_len=snprintf(seq,out_len+10,"\x1b]52;c;%s\x1b\\",encoded);

  write_all(STDOUT_FILENO,seq,(uint32_t)seq_len);

  free(seq);
 }

 free(encoded);
}

void copy_selection()
{
 if(!E.select_mode)
 {
  return;
 }

 free(clipboard_buffer);
 clipboard_buffer=NULL;
 clipboard_len=0;

 if(E.select_mode == SELECT_ROW)
 {
  if(E.c_y >= E.num_rows)
  {
   return;
  }

  e_row* row=&E.row[E.c_y];
  clipboard_buffer=malloc(row->size+1);

  if(clipboard_buffer == NULL)
  {
   return;
  }

  memcpy(clipboard_buffer,row->characters,row->size);
  clipboard_buffer[row->size]='\n';
  clipboard_len=row->size+1;
  clipboard_row_mode=1;
  osc52_copy(clipboard_buffer,clipboard_len);
  return;
 }

 int32_t x_1=0;
 int32_t y_1=0;
 int32_t x_2=0;
 int32_t y_2=0;

 get_selection_bounds(&x_1,&y_1,&x_2,&y_2);

 e_row* row=NULL;
 uint32_t total=0;
 int32_t start=0;
 int32_t end=0;
 uint32_t pos=0;
 int32_t y=0;

 for(y=y_1;y <= y_2;++y)
 {
  row=&E.row[y];
  start=0;
  end=0;

  if(y == y_1)
  {
   start=x_1;
  }
  else
  {
   start=0;
  }

  if(y == y_2)
  {
   end=x_2;
  }
  else
  {
   end=row->size;
  }

  if(end > start)
  {
   total+=(end-start);
  }

  if(y < y_2)
  {
   total+=1;
  }
 }

 clipboard_buffer=malloc(total > 0 ? total : 1);

 if(clipboard_buffer == NULL)
 {
  return;
 }

 pos=0;

 for(y=y_1;y <= y_2;++y)
 {
  row=&E.row[y];
  start=0;

  if(y == y_1)
  {
   start=x_1;
  }
  else
  {
   start=0;
  }

  end=0;

  if(y == y_2)
  {
   end=x_2;
  }
  else
  {
   end=row->size;
  }

  if(end > start)
  {
   memcpy(clipboard_buffer+pos,&row->characters[start],end-start);
   pos+=(end-start);
  }
  if(y < y_2)
  {
   clipboard_buffer[pos]='\n';
   ++pos;
  }
 }

 clipboard_len=total;
 clipboard_row_mode=0;
 osc52_copy(clipboard_buffer,clipboard_len);
}

void delete_selection()
{
 if(!E.select_mode)
 {
  return;
 }

 if(E.select_mode == SELECT_ROW)
 {
  if(E.c_y >= E.num_rows)
  {
   return;
  }

  actions action;
  memset(&action,0,sizeof(action));
  e_row* row=&E.row[E.c_y];

  action.type=USER_ACTION_ROW_DELETE;
  action.c_x=0;
  action.c_y=E.c_y;
  action.row_len=row->size;
  action.row_text=row->size > 0 ? malloc(row->size) : NULL;

  if(action.row_text != NULL)
  {
   memcpy(action.row_text,row->characters,row->size);
   undo_push(&action);
  }
  else if(row->size == 0)
  {
   undo_push(&action);
  }
  else
  {
   set_status_message(ERROR_MSG_COLOR,"Low memory: row deleted, not added to undo history");
  }

  del_row(E.c_y);

  E.c_x=0;

  if(E.c_y >= E.num_rows && E.num_rows > 0)
  {
   E.c_y=E.num_rows-1;
  }

  E.dirty=1;
  return;
 }

 int32_t x_1=0;
 int32_t y_1=0;
 int32_t x_2=0;
 int32_t y_2=0;

 get_selection_bounds(&x_1,&y_1,&x_2,&y_2);

 e_row* row=NULL;
 uint32_t total=0;
 int32_t start=0;
 int32_t end=0;
 uint32_t pos=0;
 int32_t y=0;

 for(y=y_1;y <= y_2;++y)
 {
  row=&E.row[y];
  start=0;

  if(y == y_1)
  {
   start=x_1;
  }
  else
  {
   start=0;
  }

  end=0;

  if(y == y_2)
  {
   end=x_2;
  }
  else
  {
   end=row->size;
  }

  if(end > start)
  {
   total+=(end-start);
  }

  if(y<y_2)
  {
   total+=1;
  }
 }

 char* deleted_text=malloc(total > 0 ? total : 1);

 if(deleted_text == NULL)
 {
  return;
 }

 pos=0;

 for(y=y_1;y <= y_2;++y)
 {
  row=&E.row[y];
  start=0;

  if(y == y_1)
  {
   start=x_1;
  }
  else
  {
   start=0;
  }

  end=0;

  if(y == y_2)
  {
   end=x_2;
  }
  else
  {
   end=row->size;
  }

  if(end > start)
  {
   memcpy(deleted_text+pos,&row->characters[start],end-start);
   pos+=(end-start);
  }
  if(y < y_2)
  {
   deleted_text[pos]='\n';
   ++pos;
  }
 }

 actions action;
 memset(&action,0,sizeof(action));
 action.type=USER_ACTION_RANGE_DELETE;
 action.c_x=x_1;
 action.c_y=y_1;
 action.c_x_end=x_2;
 action.c_y_end=y_2;
 action.row_text=deleted_text;
 action.row_len=total;
 undo_push(&action);

 E.c_x=x_2;
 E.c_y=y_2;

 while((E.c_x > x_1 && E.c_y == y_1) || E.c_y > y_1)
 {
  if(E.c_x > 0 && (E.c_x > x_1 || E.c_y > y_1))
  {
   row_del_char(&E.row[E.c_y],E.c_x-1);
   --E.c_x;
  }
  else if(E.c_y > y_1)
  {
   int32_t prev_len=E.row[E.c_y-1].size;
   row_append_string(&E.row[E.c_y-1],E.row[E.c_y].characters,E.row[E.c_y].size);
   del_row(E.c_y);
   E.c_x=prev_len;
   --E.c_y;
  }
 }
 E.c_x=x_1;
 E.c_y=y_1;
 E.dirty=1;
}

void paste_clipboard()
{
 if(clipboard_buffer == NULL || clipboard_len == 0)
 {
  return;
 }

 if(clipboard_row_mode)
 {
  actions action;
  memset(&action,0,sizeof(action));

  int32_t insert_index=E.c_y+1;

  if(insert_index > E.num_rows)
  {
   insert_index=E.num_rows; 
  }

  action.type=USER_ACTION_ROW_INSERT;
  action.c_x=0;
  action.c_y=insert_index;
  action.row_len=clipboard_len-1;
  action.row_text=action.row_len > 0 ? malloc(action.row_len) : NULL;

  insert_row(insert_index,clipboard_buffer,clipboard_len-1);

  if(action.row_text != NULL)
  {
   memcpy(action.row_text,clipboard_buffer,action.row_len);
   undo_push(&action);
  }
  else if(action.row_len == 0)
  {
   undo_push(&action);
  }
  else
  {
   set_status_message(ERROR_MSG_COLOR,"Low memory: paste not added to undo history");
  }

  E.c_x=0;
  E.c_y=insert_index;
  E.dirty=1;
  return;
 }

 int32_t start_x=E.c_x;
 int32_t start_y=E.c_y;
 uint32_t i=0;

 for(i=0;i < clipboard_len;++i)
 {
  if(clipboard_buffer[i] == '\n')
  {
   insert_new_line();
  }
  else
  {
   insert_char((unsigned char)clipboard_buffer[i]);
  }
 }

 actions action;
 memset(&action,0,sizeof(action));

 action.type=USER_ACTION_RANGE_INSERT;
 action.c_x=start_x;
 action.c_y=start_y;
 action.c_x_end=E.c_x;
 action.c_y_end=E.c_y;
 action.row_len=clipboard_len;
 action.row_text=malloc(clipboard_len);

 if(action.row_text != NULL)
 {
  memcpy(action.row_text,clipboard_buffer,clipboard_len);
  action.row_len=clipboard_len;
  undo_push(&action);
 }
 else
 {
  set_status_message(ERROR_MSG_COLOR,"Low memory: paste not added to undo history");
 }
}

/*** file browser ***/
void reset_editor_for_new_file()
{
 int32_t i=0;

 for(i=0;i <= E.undo_top;++i)
 {
  action_free(&E.undo_stack[i]);
 }

 E.undo_top=-1;

 for(i=0;i <= E.redo_top;++i)
 {
  action_free(&E.redo_stack[i]);
 }

 E.redo_top=-1;
 E.saved_undo_top=-1;

 for(i=0;i < E.num_rows;++i)
 {
  free_row(&E.row[i]);
 }

 free(E.row);

 E.row=NULL;
 E.num_rows=0;
 row_capacity=0;

 free(E.file_name);

 E.file_name=NULL;
 E.syntax=NULL;
 E.status_msg_time=0;
 E.last_known_mtime=0;
 E.c_x=0;
 E.c_y=0;
 E.r_x=0;
 E.saved_r_x=-1;
 E.select_anchor_x=0;
 E.select_anchor_y=0;
 E.row_off=0;
 E.col_off=0;
 E.seg_col_off=0;
 E.wrap_generation=0;
 E.line_num_width=0;
 E.num_of_status_msg_lines=0;
 E.msg_color=DEFAULT_MSG_COLOR;
 E.select_mode=SELECT_NONE;
 E.mode=MODE_NORMAL;
 E.dirty=0;
 E.file_modified_externally=0;
 E.status_msg[0]='\0';
 arena_clear(render_arena);
 arena_clear(highlight_arena);
 render_arena_wasted=0;
 highlight_arena_wasted=0;
}

int8_t path_is_directory(const char* path)
{
 #ifdef _WIN32
  DWORD attributes=GetFileAttributesA(path);

  if(attributes == INVALID_FILE_ATTRIBUTES)
  {
   return -1;
  }

  if(attributes & FILE_ATTRIBUTE_DIRECTORY)
  {
   return 1;
  }
  else
  {
   return 0;
  }
 #else
  struct stat s;

  if(stat(path,&s) != 0)
  {
   return -1;
  }

  if(S_ISDIR(s.st_mode))
  {
   return 1;
  }
  else
  {
   return 0;
  }
 #endif
}

int browse_compare_entries(const void* a,const void* b)
{
 const browse_entry* e_a=(const browse_entry*)a;
 const browse_entry* e_b=(const browse_entry*)b;

 return strcmp(e_a->name,e_b->name);
}

static void browse_push_entry(const char* name,uint8_t is_dir)
{
 if(browse_entry_count == browse_entry_cap)
 {
  if(browse_entry_cap)
  {
   browse_entry_cap*=2;
  }
  else
  {
   browse_entry_cap=64;
  }

  browse_entry* new_entries=realloc(browse_entries,(size_t)browse_entry_cap*sizeof(browse_entry));

  if(new_entries == NULL)
  {
   die("realloc [browse_push_entry]");
  }
  browse_entries=new_entries;
 }

 snprintf(browse_entries[browse_entry_count].name,sizeof(browse_entries[browse_entry_count].name),"%s",name);
 browse_entries[browse_entry_count].is_dir=is_dir;
 ++browse_entry_count;
}

void browse_free_entries()
{
 free(browse_entries);
 browse_entries=NULL;
 browse_entry_count=0;
 browse_entry_cap=0;
}

int8_t browse_load_entries(const char* path)
{
 browse_free_entries();

 #ifdef _WIN32
  char pattern[4096];
  snprintf(pattern,sizeof(pattern),"%s\\*",path);

  WIN32_FIND_DATAA f;
  HANDLE h=FindFirstFileA(pattern,&f);

  if(h == INVALID_HANDLE_VALUE)
  {
   return -1;
  }

  do
  {
   if(!(browse_flag & BROWSE_FLAG_SHOW_HIDDEN) && f.cFileName[0] == '.')
   {
    continue;
   }
   browse_push_entry(f.cFileName,(f.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? 1 : 0);
  }
  while(FindNextFileA(h,&f));

  FindClose(h);
 #else
  DIR* dir=opendir(path);

  if(!dir)
  {
   return -1;
  }

  struct dirent* d;

  while((d=readdir(dir)) != NULL)
  {
   if(!(browse_flag & BROWSE_FLAG_SHOW_HIDDEN) && d->d_name[0] == '.')
   {
    continue;
   }

   uint8_t is_dir=0;
   char full_path[4096];

   struct stat s;

   snprintf(full_path,sizeof(full_path),"%s/%s",path,d->d_name);

   if(stat(full_path,&s) == 0 && S_ISDIR(s.st_mode))
   {
    is_dir=1;
   }

   browse_push_entry(d->d_name,is_dir);
  }

  closedir(dir);
 #endif

 qsort(browse_entries,(size_t)browse_entry_count,sizeof(browse_entry),browse_compare_entries);
 return 0;
}

void format_size(char *buf,uint64_t buf_size,uint64_t size)
{
 const char *units[]={"B","KB","MB","GB","TB","PB"};
 int32_t unit_index=0;
 uint64_t temp=size;

 while(temp >= 1024 && unit_index < 5)
 {
  temp=temp >> 10;
  ++unit_index;
 }

 snprintf(buf,buf_size,"%" PRIu64 "%s",temp,units[unit_index]);
}

void browse_build_long_line(const char* dir,const char* name,char* out,uint64_t out_size)
{
 char full_path[4096];
 snprintf(full_path,sizeof(full_path),"%s%c%s",dir,BROWSE_SEP,name);
 char size_buffer[32];

 #ifdef _WIN32
  WIN32_FILE_ATTRIBUTE_DATA f_a_d;

  if(!GetFileAttributesExA(full_path,GetFileExInfoStandard,&f_a_d))
  {
   snprintf(out,out_size,"%s (error reading attributes)",name);
   return;
  }

  SYSTEMTIME s_t_utc;
  SYSTEMTIME s_t_local;

  FileTimeToSystemTime(&f_a_d.ftLastWriteTime,&s_t_utc);
  SystemTimeToTzSpecificLocalTime(NULL,&s_t_utc,&s_t_local);

  if(f_a_d.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
  {
   snprintf(out,out_size,"%02d/%02d/%04d  %02d:%02d    <DIR>          %s",s_t_local.wDay,s_t_local.wMonth,s_t_local.wYear,s_t_local.wHour,s_t_local.wMinute,name);
  }
  else
  {
   LARGE_INTEGER size;
   size.HighPart=f_a_d.nFileSizeHigh;
   size.LowPart=f_a_d.nFileSizeLow;

   format_size(size_buffer,sizeof(size_buffer),(uint64_t)size.QuadPart);

   snprintf(out,out_size,"%02d/%02d/%04d  %02d:%02d %14s %s",s_t_local.wDay,s_t_local.wMonth,s_t_local.wYear,s_t_local.wHour,s_t_local.wMinute,size_buffer,name);
  }
 #else
  struct stat s_t;

  if(lstat(full_path,&s_t) < 0)
  {
   snprintf(out,out_size,"%s (error reading attributes)",name);
   return;
  }

  char modes[16];

  modes[0]=S_ISDIR(s_t.st_mode) ? 'd' : (S_ISLNK(s_t.st_mode) ? 'l' : '-');
  modes[1]=(s_t.st_mode & S_IRUSR) ? 'r' : '-';
  modes[2]=(s_t.st_mode & S_IWUSR) ? 'w' : '-';
  modes[3]=(s_t.st_mode & S_IXUSR) ? 'x' : '-';
  modes[4]=(s_t.st_mode & S_IRGRP) ? 'r' : '-';
  modes[5]=(s_t.st_mode & S_IWGRP) ? 'w' : '-';
  modes[6]=(s_t.st_mode & S_IXGRP) ? 'x' : '-';
  modes[7]=(s_t.st_mode & S_IROTH) ? 'r' : '-';
  modes[8]=(s_t.st_mode & S_IWOTH) ? 'w' : '-';
  modes[9]=(s_t.st_mode & S_IXOTH) ? 'x' : '-';
  modes[10]='\0';

  struct passwd* password=getpwuid(s_t.st_uid);
  struct group* group=getgrgid(s_t.st_gid);

  char time_buffer[32];
  struct tm* time_info=localtime(&s_t.st_mtime);

  strftime(time_buffer,sizeof(time_buffer),"%e %b %Y %H:%M",time_info);
  format_size(size_buffer,sizeof(size_buffer),(uint64_t)s_t.st_size);

  snprintf(out,out_size,"%s %2" PRIu64 " %-8s %-8s %8s %s %s",modes,(uint64_t)s_t.st_nlink,password ? password->pw_name : "?",group ? group->gr_name : "?",size_buffer,time_buffer,name);
 #endif
}

int32_t browse_mouse_to_index(int32_t list_rows,int32_t scroll_off)
{
 int32_t row_click=g_mouse_y-2;

 if(row_click < 0 || row_click >= list_rows)
 {
  return -1;
 }

 int32_t index=scroll_off+row_click;

 if(index >= browse_entry_count)
 {
  return -1;
 }

 return index;
}

char* browse_for_file(const char* start_path)
{
 char current_path[4096];
 snprintf(current_path,sizeof(current_path),"%s",start_path);

 if(browse_load_entries(current_path) != 0)
 {
  return NULL;
 }

 int32_t selected=0;
 int32_t scroll_off=0;
 char status_msg[512]="";
 char* result=NULL;
 a_buf a_buffer={NULL,0,0};
 int32_t last_click_index=-1;
 uint64_t last_click_ms=0;
 uint8_t status_is_notice=0;

 while(1)
 {
  int16_t rows=24;
  int16_t cols=80;

  get_window_size(&rows,&cols);

  int32_t list_rows=rows-7;

  if(list_rows < 1)
  {
   list_rows=1;
  }

  if(selected < scroll_off)
  {
   scroll_off=selected;
  }

  if(selected >= scroll_off+list_rows)
  {
   scroll_off=selected-list_rows+1;
  }

  uint8_t show_long_now=(browse_flag & BROWSE_FLAG_LONG_FORMAT) && (cols >= BROWSE_MIN_LONG_COLS);

  if((browse_flag & BROWSE_FLAG_LONG_FORMAT) && !show_long_now)
  {
   snprintf(status_msg,sizeof(status_msg),"Terminal is too narrow for long format (need >= %d cols, you have %d)",BROWSE_MIN_LONG_COLS,cols);
  }

  char buffer[1024];
  int32_t len=0;

  a_buf_append(&a_buffer,"\x1b[2J\x1b[H",7);

  char path_color[16];
  int8_t path_coloreplacement_len=snprintf(path_color,sizeof(path_color),"\x1b[%d;%dm",FG_PATH_COLOR,BG_PATH_COLOR);
  a_buf_append(&a_buffer,path_color,path_coloreplacement_len);

  len=snprintf(buffer,sizeof(buffer),"Path: %.*s ",cols > 8 ? cols-8 : 20,current_path);
  a_buf_append(&a_buffer,buffer,len);
  a_buf_append(&a_buffer,"\x1b[0m\x1b[K\r\n",9);
  a_buf_append(&a_buffer,"\x1b[K\r\n",5);

  int32_t i=0;
  int32_t last=scroll_off+list_rows;

  if(last > browse_entry_count)
  {
   last=browse_entry_count;
  }

  for(i=scroll_off;i < last;++i)
  {
   char line[1024];

   if(show_long_now)
   {
    browse_build_long_line(current_path,browse_entries[i].name,line,sizeof(line));
   }
   else
   {
    snprintf(line,sizeof(line),"%s%s",browse_entries[i].name,browse_entries[i].is_dir ? "/" : "");
   }

   if(i == selected)
   {
    char sel_color[16];
    int8_t sel_coloreplacement_len=snprintf(sel_color,sizeof(sel_color),"\x1b[%d;%dm",FG_SELECTED_COLOR,BG_SELECTED_COLOR);
    a_buf_append(&a_buffer,sel_color,sel_coloreplacement_len);

    len=snprintf(buffer,sizeof(buffer),"%.*s",cols,line);
    a_buf_append(&a_buffer,buffer,len);
    a_buf_append(&a_buffer,"\x1b[0m\x1b[K\r\n",9);
   }
   else
   {
    len=snprintf(buffer,sizeof(buffer),"%.*s\x1b[K\r\n",cols,line);
    a_buf_append(&a_buffer,buffer,len);
   }
  }

  int32_t drawn=last-scroll_off;
  int32_t blanks=list_rows-drawn;

  if(blanks < 0)
  {
   blanks=0;
  }

  for(i=0;i < blanks;++i)
  {
   a_buf_append(&a_buffer,"\x1b[K\r\n",5);
  }

  if(status_msg[0])
  {
   char color[16];
   int8_t color_replacement_len=snprintf(color,sizeof(color),"\x1b[%d;%dm",status_is_notice ? FG_NOTICE_COLOR : FG_ERROR_COLOR,status_is_notice ? BG_NOTICE_COLOR : BG_ERROR_COLOR);
   a_buf_append(&a_buffer,color,color_replacement_len);

   len=snprintf(buffer,sizeof(buffer),"%.*s",cols,status_msg);
   a_buf_append(&a_buffer,buffer,len);
   a_buf_append(&a_buffer,"\x1b[0m\x1b[K\r\n",9);
  }
  else
  {
   a_buf_append(&a_buffer,"\x1b[K\r\n",5);
  }

  char short_color[16];
  int8_t short_color_replacement_len=snprintf(short_color,sizeof(short_color),"\x1b[%d;%dm",FG_SHORTCUT_COLOR,BG_SHORTCUT_COLOR);
  a_buf_append(&a_buffer,short_color,short_color_replacement_len);

  len=snprintf(buffer,sizeof(buffer),"[w/s/Arrows/Scroll] move  [Esc/q] cancel");
  a_buf_append(&a_buffer,buffer,len);
  a_buf_append(&a_buffer,"\x1b[0m\x1b[K\r\n",9);

  a_buf_append(&a_buffer,short_color,short_color_replacement_len);
  len=snprintf(buffer,sizeof(buffer),"[h] hidden:%s  [l] long:%s",(browse_flag & BROWSE_FLAG_SHOW_HIDDEN) ? "on" : "off",(browse_flag & BROWSE_FLAG_LONG_FORMAT) ? "on" : "off");
  a_buf_append(&a_buffer,buffer,len);
  a_buf_append(&a_buffer,"\x1b[0m\x1b[K\r\n",9);

  a_buf_append(&a_buffer,short_color,short_color_replacement_len);
  len=snprintf(buffer,sizeof(buffer),"[enter] open/select  [backspace] up");
  a_buf_append(&a_buffer,buffer,len);
  a_buf_append(&a_buffer,"\x1b[0m\x1b[K\r\n",9);

  a_buf_append(&a_buffer,short_color,short_color_replacement_len);
  len=snprintf(buffer,sizeof(buffer),"[click] select  [double click] open  [right click] copy");
  a_buf_append(&a_buffer,buffer,len);
  a_buf_append(&a_buffer,"\x1b[0m\x1b[K",7);

  write_all(STDOUT_FILENO,a_buffer.b,a_buffer.len);

  a_buf_free(&a_buffer);

  uint16_t key=read_key();
  status_msg[0]='\0';
  status_is_notice=0;
  uint8_t activate=0;

  if(key == RESIZE_KEY)
  {
   window_resized=0;
   continue;
  }
  else if(key == ARROW_UP || key == 'w' || key == MOUSE_WHEEL_UP)
  {
   if(selected > 0)
   {
    --selected;
   }
  }
  else if(key == ARROW_DOWN || key == 's' || key == MOUSE_WHEEL_DOWN)
  {
   if(selected < browse_entry_count-1)
   {
    ++selected;
   }
  }
  else if(key == 'h')
  {
   browse_flag^=BROWSE_FLAG_SHOW_HIDDEN;
   browse_load_entries(current_path);

   if(selected >= browse_entry_count)
   {
    selected=browse_entry_count-1;
   }

   if(selected < 0)
   {
    selected=0;
   }

   scroll_off=0;
  }
  else if(key == 'l')
  {
   if(!(browse_flag & BROWSE_FLAG_LONG_FORMAT))
   {
    int16_t r=24,c=80;
    get_window_size(&r,&c);

    if(c < BROWSE_MIN_LONG_COLS)
    {
     snprintf(status_msg,sizeof(status_msg),"Terminal too narrow for long format (need >= %d cols, have %d)",BROWSE_MIN_LONG_COLS,c);
    }
    else
    {
     browse_flag|=BROWSE_FLAG_LONG_FORMAT;
    }
   }
   else
   {
    browse_flag&=~BROWSE_FLAG_LONG_FORMAT;
   }
  }
  else if(key == MOUSE_LEFT_PRESS || key == MOUSE_LEFT_DRAG)
  {
   int32_t index=browse_mouse_to_index(list_rows,scroll_off);

   if(index >= 0)
   {
    selected=index;

    if(key == MOUSE_LEFT_PRESS)
    {
     uint64_t now_ms=get_ms_ticks();

     if(last_click_index == index && (now_ms-last_click_ms) < 500)
     {
      activate=1;
     }

     last_click_index=index;
     last_click_ms=now_ms;
    }
   }
  }
  else if(key == MOUSE_RIGHT_PRESS)
  {
   int32_t index=browse_mouse_to_index(list_rows,scroll_off);

   if(index >= 0)
   {
    selected=index;
   }

    if(browse_entry_count > 0)
   {
    char copy_line[512];

    if((browse_flag & BROWSE_FLAG_LONG_FORMAT))
    {
     browse_build_long_line(current_path,browse_entries[selected].name,copy_line,sizeof(copy_line));
    }
    else
    {
     snprintf(copy_line,sizeof(copy_line),"%s",browse_entries[selected].name);
    }

    free(clipboard_buffer);
    clipboard_buffer=strdup(copy_line);
    clipboard_len=clipboard_buffer ? (uint32_t)strlen(clipboard_buffer) : 0;
    clipboard_row_mode=0;
    osc52_copy(clipboard_buffer,clipboard_len);
    int32_t max_copy_len=(int32_t)sizeof(status_msg)-10;
    snprintf(status_msg,sizeof(status_msg),"Copied '%.*s'",max_copy_len,copy_line);
    status_is_notice=1;
   }
  }

  if(key == '\r' || activate)
  {
   if(browse_entry_count > 0)
   {
    if(browse_entries[selected].is_dir)
    {
     char next_path[4352];

     snprintf(next_path,sizeof(next_path),"%s%c%s",current_path,BROWSE_SEP,browse_entries[selected].name);

     if(browse_load_entries(next_path) == 0)
     {
      snprintf(current_path,sizeof(current_path),"%.*s",(int32_t)sizeof(current_path)-1,next_path);
      selected=0;
      scroll_off=0;
     }
     else
     {
      snprintf(status_msg,sizeof(status_msg),"Cannot open '%s'",browse_entries[selected].name);
     }
    }
    else
    {
     char full_path[5120];
     snprintf(full_path,sizeof(full_path),"%s%c%s",current_path,BROWSE_SEP,browse_entries[selected].name);
     result=strdup(full_path);
     break;
    }
   }
  }
  else if(key == BACKSPACE || key == DEL_KEY)
  {
   char* slash=strrchr(current_path,BROWSE_SEP);

   if(slash)
   {
    if(BROWSE_SEP == '\\' && slash == current_path+2 && current_path[1] == ':')
    {
     continue;
    }
    else if(slash == current_path)
    {
     current_path[1]='\0';
    }
    else
    {
     *slash='\0';
    }
   }

   if(browse_load_entries(current_path) == 0)
   {
    selected=0;
    scroll_off=0;
   }
  }
  else if(key == '\x1b' || key == 'q')
  {
   result=NULL;
   break;
  }
 }

 browse_free_entries();

 write_all(STDOUT_FILENO,"\x1b[2J\x1b[H",7);

 return result;
}

/*** file I/O ***/
int8_t get_file_mtime(const char* path,int64_t* out_mtime)
{
 #ifdef _WIN32
  WIN32_FILE_ATTRIBUTE_DATA f_a_d;

  if(!GetFileAttributesExA(path,GetFileExInfoStandard,&f_a_d))
  {
   return -1;
  }

  ULARGE_INTEGER u_i;
  u_i.LowPart=f_a_d.ftLastWriteTime.dwLowDateTime;
  u_i.HighPart=f_a_d.ftLastWriteTime.dwHighDateTime;

  *out_mtime=(int64_t)u_i.QuadPart;
 #else
  struct stat s;

  if(stat(path,&s) != 0)
  {
   return -1;
  }

  *out_mtime=(int64_t)s.st_mtime;
 #endif

 return 0;
}

void update_known_mtime()
{
 if(E.file_name == NULL)
 {
  E.last_known_mtime=0;
  E.file_modified_externally=0;
  return;
 }

 if(get_file_mtime(E.file_name,&E.last_known_mtime) != 0)
 {
  E.last_known_mtime=0;
 }

 E.file_modified_externally=0;
}

void check_file_modified_externally()
{
 if(E.file_name == NULL || E.file_modified_externally)
 {
  return;
 }

 int64_t current_mtime=0;

 if(get_file_mtime(E.file_name,&current_mtime) != 0)
 {
  return;
 }

 if(current_mtime != E.last_known_mtime)
 {
  E.file_modified_externally=1;
 }
}

int8_t file_is_binary(const char* path)
{
 FILE* f_p=fopen(path,"rb");

 if(!f_p)
 {
  return -1;
 }

 uint8_t buf[4096];
 uint32_t total=0;
 uint32_t suspicious=0;
 uint32_t n_read=0;

 while((n_read=fread(buf,1,sizeof(buf),f_p)) > 0)
 {
  uint32_t i=0;

  for(i=0;i < n_read;++i)
  {
   unsigned char c=buf[i];

   if(c == 0 || (c < 32 && c != '\n' && c != '\r' && c != '\t'))
   {
    ++suspicious;
   }
  }
  total+=n_read;

  if(suspicious > (total>>4))
  {
   fclose(f_p);
   return 1;
  }
 }

 fclose(f_p);
 return 0;
}

void open_file(char* file_name)
{
 int8_t binary=file_is_binary(file_name);

 if(binary == 1)
 {
  set_status_message(ERROR_MSG_COLOR,"Can not open binary file");
  return;
 }
 else if(binary == -1)
 {
  die("file_is_binary can not open the file [open_file]");
 }

 free(E.file_name);
 E.file_name=strdup(file_name);

 FILE* f_p=fopen(file_name,"rb");

 if(!f_p)
 {
  if(errno == ENOENT)
  {
   select_syntax_highlight();
   E.dirty=0;
   E.saved_undo_top=-1;
   update_known_mtime();
   return;
  }
  die("fopen [open_file]");
 }

 select_syntax_highlight();

 size_t i=0;
 char chunk[4096];
 size_t chunk_len=0;
 char* line=NULL;
 uint32_t line_cap=0;
 uint32_t line_len=0;

 while((chunk_len=fread(chunk,1,sizeof(chunk),f_p)) > 0)
 {
  for(i=0;i < chunk_len;++i)
  {
   if(chunk[i] == '\n')
   {
    if(line_len > 0 && line[line_len-1] == '\r')
    {
     --line_len;
    }
    insert_row(E.num_rows,line ? line : (char*)"",line_len);
    line_len=0;
   }
   else
   {
    if(line_len >= line_cap)
    {
     uint32_t new_cap=0;

     if(line_cap == 0)
     {
      new_cap=4096;
     }
     else
     {
      new_cap=line_cap<<1;
     }

     char* new_line=realloc(line,new_cap+1);

     if(!new_line)
     {
      free(line);
      fclose(f_p);
      die("realloc line buffer [open_file]");
     }
     line=new_line;
     line_cap=new_cap;
    }
    line[line_len++]=chunk[i];
   }
  }
 }

 if(line_len > 0)
 {
  if(line[line_len-1] == '\r')
  {
   --line_len;
  }

  insert_row(E.num_rows,line,line_len);
 }

 free(line);
 fclose(f_p);
 E.dirty=0;
 E.saved_undo_top=-1;
 update_known_mtime();
 compact_row_arenas();
}

char* rows_to_string(uint32_t* buffer_placement_len)
{
 uint32_t total_len=0;
 int32_t i=0;

 for(i=0;i < E.num_rows;++i)
 {
  total_len+=E.row[i].size+1;
 }

 *buffer_placement_len=total_len;

 char* buffer=malloc(total_len > 0 ? total_len : 1);

 if(buffer == NULL)
 {
  die("malloc [rows_to_string]");
 }

 char* p=buffer;

 for(i=0;i < E.num_rows;++i)
 {
  memcpy(p,E.row[i].characters,E.row[i].size);
  p+=E.row[i].size;
  *p='\n';
  ++p;
 }

 return buffer;
}

void save_file()
{
 if(E.file_name == NULL)
 {
  E.file_name=prompt(ACTION_MSG_COLOR,"Save as: %s (Esc to cancel)",NULL);
  
  if(E.file_name == NULL)
  {
   set_status_message(ACTION_MSG_COLOR,"Save aborted");
   return;
  }
  select_syntax_highlight();
 }

 uint32_t len=0;
 char* buffer=rows_to_string(&len);
 int32_t file_desc=0;

 #ifdef _WIN32
  file_desc=(int32_t)open(E.file_name,_O_RDWR | _O_CREAT | _O_BINARY,0644);
 #else
  file_desc=(int32_t)open(E.file_name,O_RDWR | O_CREAT,0644);
 #endif

 if(file_desc != -1)
 {
  if(ftruncate(file_desc,len) != -1)
  {
   if(write_all(file_desc,buffer,len) == 0)
   {
    close(file_desc);
    free(buffer);
    E.dirty=0;
    E.saved_undo_top=E.undo_top;
    update_known_mtime();
    char size_buf[32];
    format_size(size_buf,sizeof(size_buf),len);
    set_status_message(SUCCESS_MSG_COLOR,"File is written to the disk (%s)",size_buf);
    return;
   }
  }
  close(file_desc);
 }
 free(buffer);
 set_status_message(ERROR_MSG_COLOR,"Can't save! I/O error: %s",strerror(errno));
}

/*** find ***/
static int32_t find_last_in_row_before(e_row* row,char* query,int32_t before_col)
{
 int32_t result=-1;
 int32_t offset=0;

 while(offset <= row->r_size)
 {
  char* match=strstr(row->render+offset,query);

  if(!match)
  {
   break;
  }

  int32_t pos=(int32_t)(match-row->render);

  if(pos >= before_col)
  {
   break;
  }

  result=pos;
  offset=pos+1;

 }
 return result;
}

static int32_t find_next_match(int32_t start_row,int32_t start_col,char* query,int8_t direction,int32_t* out_row)
{
 int32_t row_index=start_row;
 int32_t col_index=start_col;
 int32_t attempts=0;

 while(attempts <= E.num_rows)
 {
  e_row* row=&E.row[row_index];
  int32_t pos=-1;

  if(direction == 1)
  {
   if(col_index <= row->r_size)
   {
    char* match=strstr(row->render+col_index,query);

    if(match)
    {
     pos=(int32_t)(match-row->render);
    }
   }
  }
  else
  {
   pos=find_last_in_row_before(row,query,col_index);
  }

  if(pos != -1)
  {
   *out_row=row_index;
   return pos;
  }

  if(direction == 1)
  {
   row_index=(row_index+1) % E.num_rows;
   col_index=0;
  }
  else
  {
   row_index=(row_index-1+E.num_rows) % E.num_rows;
   col_index=E.row[row_index].r_size+1;
  }

  ++attempts;
 }

 return -1;
}

static void count_matches(char* query,int32_t current_row,int32_t current_col,int32_t* rank,int32_t* total)
{
 int32_t total_matches=0;
 int32_t match_rank=0;
 int32_t r=0;

 for(r=0;r < E.num_rows;++r)
 {
  int32_t offset=0;
  e_row* scan_row=&E.row[r];

  while(offset <= scan_row->r_size)
  {
   char* match=strstr(scan_row->render+offset,query);

   if(!match)
   {
    break;
   }

   int32_t pos=(int32_t)(match-scan_row->render);
   ++total_matches;

   if(r < current_row || (r == current_row && pos <= current_col))
   {
    ++match_rank;
   }

   offset=pos+1;
  }
 }

 *rank=match_rank;
 *total=total_matches;
}

void find_callback(char* query,uint16_t key)
{
 static int32_t saved_highlight_line=0;
 static char* saved_highlight=NULL;
 static int32_t saved_highlight_size=0;

 if(saved_highlight != NULL)
 {
  if(saved_highlight_line >= 0 && saved_highlight_line < E.num_rows && E.row[saved_highlight_line].r_size == saved_highlight_size)
  {
   memcpy(E.row[saved_highlight_line].highlight,saved_highlight,saved_highlight_size);
  }
  free(saved_highlight);
 }
 saved_highlight=NULL;
 saved_highlight_line=-1;
 saved_highlight_size=0;

 if(key == '\r' || key == '\x1b')
 {
  find_last_match_row=-1;
  find_last_match_col=-1;
  find_direction=1;
  return;
 }
 else if(key == ARROW_RIGHT || key == ARROW_DOWN)
 {
  find_direction=1;
 }
 else if(key == ARROW_LEFT || key == ARROW_UP)
 {
  find_direction=-1;
 }
 else
 {
  find_last_match_row=-1;
  find_last_match_col=-1;
  find_direction=1;
 }

 if(query[0] == '\0' || E.num_rows == 0)
 {
  set_status_message(ACTION_MSG_COLOR,"Search: %s (Use Esc/Arrows/Enter)",query);
  return;
 }

 int32_t found_row=-1;
 int32_t found_col=-1;
 int32_t start_row=0;
 int32_t start_col=0;

 if(find_direction == 1)
 {
  if(find_last_match_row == -1)
  {
   start_row=0;
  }
  else
  {
   start_row=find_last_match_row;
  }

  if(find_last_match_row == -1)
  {
   start_col=0;
  }
  else
  {
   start_col=find_last_match_col+1;
  }
 }
 else
 {
  if(find_last_match_row == -1)
  {
   start_row=E.num_rows-1;
  }
  else
  {
   start_row=find_last_match_row;
  }

  if(find_last_match_row == -1)
  {
   start_col=E.row[start_row].r_size+1;
  }
  else
  {
   start_col=find_last_match_col;
  }
 }

 found_col=find_next_match(start_row,start_col,query,find_direction,&found_row);

 if(found_col == -1)
 {
  set_status_message(ACTION_MSG_COLOR,"Search: %s (no match)",query);
  return;
 }

 find_last_match_row=found_row;
 find_last_match_col=found_col;

 e_row* row=&E.row[found_row];

 E.c_y=found_row;
 E.c_x=row_r_x_to_c_x(row,found_col);
 E.row_off=E.num_rows;

 saved_highlight_line=found_row;

 if(row->r_size > 0)
 {
  saved_highlight=malloc(row->r_size);

  if(saved_highlight == NULL)
  {
   die("malloc [find_callback]");
  }
  memcpy(saved_highlight,row->highlight,row->r_size);
  saved_highlight_size=row->r_size;
 }
 else
 {
  saved_highlight=NULL;
  saved_highlight_size=0;
 }

 memset(&row->highlight[found_col],H_MATCH,strlen(query));

 int32_t total_matches=0;
 int32_t match_rank=0;

 count_matches(query,found_row,found_col,&match_rank,&total_matches);

 set_status_message(ACTION_MSG_COLOR,"Search: %s  m:%d/%d",query,match_rank,total_matches);
}

void find()
{
 int32_t saved_c_x=E.c_x;
 int32_t saved_c_y=E.c_y;
 int32_t saved_row_off=E.row_off;
 int32_t saved_col_off=E.col_off;

 find_direction=1;
 find_last_match_row=-1;
 find_last_match_col=-1;

 char* query=prompt(ACTION_MSG_COLOR,"Search: %s (Use Esc/Arrows/Enter)",find_callback);
 
 if(query == NULL)
 {
  E.c_x=saved_c_x;
  E.c_y=saved_c_y;
  E.row_off=saved_row_off;
  E.col_off=saved_col_off;
  return;
 }

 if(query[0] == '\0' || E.num_rows == 0)
 {
  free(query);
  return;
 }

 if(E.c_y >= E.num_rows)
 {
  if(E.num_rows > 0)
  {
   E.c_y=E.num_rows-1;
  }
  else
  {
   free(query);
   return;
  }
 }
 int32_t match_row=E.c_y;
 int32_t match_col=row_c_x_to_r_x(&E.row[E.c_y],E.c_x);

 uint8_t running=1;

 while(running)
 {
  int32_t match_rank=0;
  int32_t total_matches=0;

  count_matches(query,match_row,match_col,&match_rank,&total_matches);

  set_status_message(ACTION_MSG_COLOR,"Search: %s  m:%d/%d (b=before | a=after | Esc=exit)",query,match_rank,total_matches);
  refresh_screen();

  uint16_t key=read_key();

  switch(key)
  {
   case '\x1b':
   {
    running=0;
   }
   break;

   case 'a':
   {
    int32_t found_row=match_row;
    int32_t found_col=find_next_match(match_row,match_col+1,query,1,&found_row);

    if(found_col != -1)
    {
     match_row=found_row;
     match_col=found_col;
     E.c_x=row_r_x_to_c_x(&E.row[found_row],found_col);
     E.c_y=found_row;
     E.row_off=E.num_rows;
    }
   }
   break;

   case 'b':
   {
    int32_t found_row=match_row;
    int32_t found_col=find_next_match(match_row,match_col,query,-1,&found_row);

    if(found_col != -1)
    {
     match_row=found_row;
     match_col=found_col;
     E.c_x=row_r_x_to_c_x(&E.row[found_row],found_col);
     E.c_y=found_row;
     E.row_off=E.num_rows;
    }
   }
   break;
  }
 }

 free(query);
}

void go_to_line()
{
 if(E.num_rows == 0)
 {
  return;
 }

 char* input=prompt(ACTION_MSG_COLOR,"Go to line: %s",NULL);

 if(input == NULL)
 {
  return;
 }

 int32_t target=0;
 char* endptr=NULL;
 errno=0;
 long value=strtol(input,&endptr,10);

 if(endptr == input || *endptr != '\0' || errno == ERANGE || value < INT32_MIN || value > INT32_MAX)
 {
  set_status_message(ERROR_MSG_COLOR,"Invalid line number value");
  target=0; 
 }
 else
 {
  target=(int32_t)value;
 }

 free(input);

 if(target < 1)
 {
  target=1;
 }
 else if(target > E.num_rows)
 {
  target=E.num_rows;
 }

 if(E.saved_r_x < 0)
 {
  E.saved_r_x=row_c_x_to_r_x(&E.row[E.c_y],E.c_x);
 }

 E.c_y=target-1;

 e_row* row=&E.row[E.c_y];

 E.c_x=row_r_x_to_c_x(row,E.saved_r_x);

 if(E.c_x > row->size)
 {
  E.c_x=row->size;
 }

 E.c_x=snap_to_utf8_start(row,E.c_x);
 E.row_off=E.num_rows;
}

static uint8_t is_render_boundary(e_row* row,int32_t r_x)
{
 if(r_x < 0 || r_x > row->r_size)
 {
  return 0;
 }

 if(r_x == row->r_size)
 {
  return 1;
 }

 int32_t c=row_r_x_to_c_x(row,r_x);
 int32_t r_start=row_c_x_to_r_x(row,c);

 return r_start == r_x;
}

static uint8_t map_render_range_to_raw(e_row* row,int32_t r_start,int32_t r_len,int32_t* c_start,int32_t* c_len)
{
 if(r_start < 0 || r_len < 0 || r_start+r_len > row->r_size)
 {
  return 0;
 }

 if(!is_render_boundary(row,r_start) || !is_render_boundary(row,r_start+r_len))
 {
  return 0;
 }

 int32_t raw_start=row_r_x_to_c_x(row,r_start);
 int32_t raw_end=row_r_x_to_c_x(row,r_start+r_len);

 *c_start=raw_start;
 *c_len=raw_end-raw_start;

 return 1;
}

static uint8_t replace_one_match(int32_t r,int32_t r_x,char* query,char* replacement)
{
 e_row* row=&E.row[r];
 uint32_t query_len=(uint32_t)strlen(query);
 uint32_t replacement_len=(uint32_t)strlen(replacement);
 int32_t c_start=0;
 int32_t c_len=0;
 uint32_t i=0;

 if(!map_render_range_to_raw(row,r_x,(int32_t)query_len,&c_start,&c_len))
 {
  set_status_message(ERROR_MSG_COLOR,"Cannot replace match (special characters)");
  return 0;
 }

 actions del_action;
 memset(&del_action,0,sizeof(del_action));
 del_action.type=USER_ACTION_RANGE_DELETE;
 del_action.c_x=c_start;
 del_action.c_y=r;
 del_action.c_x_end=c_start+c_len;
 del_action.c_y_end=r;
 del_action.row_len=c_len;
 del_action.row_text=c_len > 0 ? malloc(c_len) : NULL;

 if(c_len > 0 && del_action.row_text == NULL)
 {
  die("malloc del_action.row_text [replace_one_match]");
 }

 if(c_len > 0)
 {
  memcpy(del_action.row_text,&row->characters[c_start],c_len);
  undo_push(&del_action);
 }

 for(i=0;(int32_t)i < c_len;++i)
 {
  row_del_char(row,c_start);
 }

 for(i=0;i < replacement_len;++i)
 {
  row_insert_char(row,c_start+(int32_t)i,replacement[i]);
 }

 actions insert_action;
 memset(&insert_action,0,sizeof(insert_action));
 insert_action.type=USER_ACTION_RANGE_INSERT;
 insert_action.c_x=c_start;
 insert_action.c_y=r;
 insert_action.c_x_end=c_start+(int32_t)replacement_len;
 insert_action.c_y_end=r;
 insert_action.row_len=replacement_len;
 insert_action.row_text=replacement_len > 0 ? malloc(replacement_len) : NULL;

 if(replacement_len > 0 && insert_action.row_text == NULL)
 {
  die("malloc insert_action.row_text [replace_one_match]");
 }

 if(replacement_len > 0)
 {
  memcpy(insert_action.row_text,replacement,replacement_len);
 }

 undo_push(&insert_action);
 E.c_x=c_start+(int32_t)replacement_len;
 E.c_y=r;
 return 1;
}

static int32_t replace_all_matches(char* query,char* replacement)
{
 int32_t count=0;
 int32_t r=0;

 for(r=0;r < E.num_rows;++r)
 {
  e_row* row=&E.row[r];
  int32_t offset=0;

  while(offset <= row->r_size)
  {
   char* match=strstr(row->render+offset,query);

   if(!match)
   {
    break;
   }

   int32_t r_x=(int32_t)(match-row->render);

   if(!replace_one_match(r,r_x,query,replacement))
   {
    offset=r_x+(int32_t)strlen(query);
    continue;
   }

   ++count;

   offset=row_c_x_to_r_x(row,E.c_x);
  }
 }

 return count;
}

void search_and_replace()
{
 int32_t saved_c_x=E.c_x;
 int32_t saved_c_y=E.c_y;
 int32_t saved_row_off=E.row_off;
 int32_t saved_col_off=E.col_off;

 if(E.num_rows == 0)
 {
  return;
 }

 find_direction=1;
 find_last_match_row=-1;
 find_last_match_col=-1;

 char* query=prompt(ACTION_MSG_COLOR,"Search: %s (Use Esc/Arrows/Enter)",find_callback);

 if(query == NULL || query[0] == '\0')
 {
  free(query);
  E.c_x=saved_c_x;
  E.c_y=saved_c_y;
  E.row_off=saved_row_off;
  E.col_off=saved_col_off;
  return;
 }

 int32_t match_row=0;
 int32_t match_col=find_next_match(0,0,query,1,&match_row);

 if(match_col == -1)
 {
  set_status_message(ERROR_MSG_COLOR,"Search: %s (no match)",query);
  free(query);
  E.c_x=saved_c_x;
  E.c_y=saved_c_y;
  E.row_off=saved_row_off;
  E.col_off=saved_col_off;
  return;
 }

 E.c_y=match_row;
 E.c_x=row_r_x_to_c_x(&E.row[match_row],match_col);
 E.row_off=E.num_rows;

 char replace_format[256];
 snprintf(replace_format,sizeof(replace_format),"Search: %s\nReplace: %%s",query);

 char* replacement=prompt(ACTION_MSG_COLOR,replace_format,NULL);

 if(replacement == NULL)
 {
  free(query);
  E.c_x=saved_c_x;
  E.c_y=saved_c_y;
  E.row_off=saved_row_off;
  E.col_off=saved_col_off;
  return;
 }

 char info[64];
 info[0]='\0';
 uint8_t running=1;

 while(running)
 {
  int32_t match_rank=0;
  int32_t total_matches=0;

  count_matches(query,match_row,match_col,&match_rank,&total_matches);

  set_status_message(ACTION_MSG_COLOR,"Search: %s\nReplace: %s  m:%d/%d  %s (b=before | a=after | r=replace | d=replace all | Esc=exit)",query,replacement,match_rank,total_matches,info);
  refresh_screen();

  info[0]='\0';

  uint16_t key=read_key();

  switch(key)
  {
   case '\x1b':
   {
    running=0;
   }
   break;

   case 'a':
   {
    int32_t found_row=match_row;
    int32_t found_col=find_next_match(match_row,match_col+1,query,1,&found_row);

    if(found_col != -1)
    {
     match_row=found_row;
     match_col=found_col;
     E.c_x=row_r_x_to_c_x(&E.row[found_row],found_col);
     E.c_y=found_row;
     E.row_off=E.num_rows;
    }
   }
   break;

   case 'b':
   {
    int32_t found_row=match_row;
    int32_t found_col=find_next_match(match_row,match_col,query,-1,&found_row);

    if(found_col != -1)
    {
     match_row=found_row;
     match_col=found_col;
     E.c_x=row_r_x_to_c_x(&E.row[found_row],found_col);
     E.c_y=found_row;
     E.row_off=E.num_rows;
    }
   }
   break;

   case 'r':
   {

    if(replace_one_match(match_row,match_col,query,replacement))
    {
     snprintf(info,sizeof(info),"Replaced 1 occurrence");
    }
    else
    {
     snprintf(info,sizeof(info),"Replace failed");
     continue;
    }

    int32_t found_row=match_row;
    int32_t next_col=row_c_x_to_r_x(&E.row[match_row],E.c_x);
    int32_t found_col=find_next_match(match_row,next_col,query,1,&found_row);

    if(found_col != -1)
    {
     match_row=found_row;
     match_col=found_col;
     E.c_x=row_r_x_to_c_x(&E.row[found_row],found_col);
     E.c_y=found_row;
     E.row_off=E.num_rows;
    }
    else
    {
     match_col=next_col;
    }
   }
   break;

   case 'd':
   {
    int32_t count=replace_all_matches(query,replacement);

    snprintf(info,sizeof(info),"Replaced %d occurrence(s)",count);

    match_row=0;
    match_col=find_next_match(0,0,query,1,&match_row);

    if(match_col == -1)
    {
     match_row=E.c_y;
     match_col=0;
    }
    else
    {
     E.c_x=row_r_x_to_c_x(&E.row[match_row],match_col);
     E.c_y=match_row;
     E.row_off=E.num_rows;
    }
   }
   break;
  }
 }

 free(query);
 free(replacement);
}

/*** input ***/
char* prompt(uint8_t color,char* prompt,void (*callback)(char*,uint16_t))
{
 uint16_t buffer_size=256;
 char* buffer=malloc(buffer_size);

 if(buffer == NULL)
 {
  die("malloc [prompt]");
 }

 uint16_t buffereplacement_len=0;
 buffer[0]='\0';

 set_status_message(color,prompt,buffer);
 refresh_screen();

 while(1)
 {
  uint16_t c=read_key();

  if(c == RESIZE_KEY)
  {
   window_resized=0;

   if(get_window_size(&E.term_rows,&E.screen_cols) == -1)
   {
    die("get_window_size [prompt]");
   }
   ++E.wrap_generation;
   refresh_screen();
   continue;
  }

  if(c == DEL_KEY || c == BACKSPACE)
  {
   if(buffereplacement_len != 0)
   {
    buffer[--buffereplacement_len]='\0';
   }
  }
  else if(c == '\x1b')
  {
   set_status_message(DEFAULT_MSG_COLOR,"");
   
   if(callback)
   {
    callback(buffer,c);
   }

   free(buffer);
   return NULL;
  }
  else if(c == '\r')
  {
   if(buffereplacement_len != 0)
   {
    set_status_message(DEFAULT_MSG_COLOR,"");

    if(callback)
    {
     callback(buffer,c);
    }

    return buffer;
   }
  }
  else if(!iscntrl(c) && c < ASCII_CHAR_LIMIT)
  {
   if(buffereplacement_len < buffer_size-1)
   {
    buffer[buffereplacement_len++]=c;
    buffer[buffereplacement_len]='\0';
   }
   else
   {
    set_status_message(ERROR_MSG_COLOR,"Filename size limit reached (255 chars)");
   }
  }

  if(callback)
  {
   callback(buffer,c);
  }
  else
  {
   set_status_message(color,prompt,buffer);
  }
  refresh_screen();
 }
}

void move_cursor(uint16_t key)
{
 e_row* row=NULL;

 if(E.c_y < E.num_rows)
 {
  row=&E.row[E.c_y];
 }

 switch(key)
 {
  case ARROW_UP:
  {
   if(E.c_y != 0)
   {
    if(E.saved_r_x < 0 && row)
    {
     E.saved_r_x=row_c_x_to_r_x(row,E.c_x);
    }
    --E.c_y;
   }
  }
  break;

  case ARROW_DOWN:
  {
   if(E.c_y < E.num_rows)
   {
    if(E.saved_r_x < 0 && row)
    {
     E.saved_r_x=row_c_x_to_r_x(row,E.c_x);
    }
    ++E.c_y;
   }
  }
  break;

  case ARROW_RIGHT:
  {
   E.saved_r_x=-1;

   if(row && E.c_x < row->size)
   {
    E.c_x+=get_utf8_char_placement_length(row,E.c_x);
   }
   else if(row && E.c_x == row->size)
   {
    ++E.c_y;
    E.c_x=0;
   }
  }
  break;

  case ARROW_LEFT:
  {
   E.saved_r_x=-1;

   if(E.c_x != 0)
   {
    --E.c_x;
    E.c_x=snap_to_utf8_start(row,E.c_x);
   }
   else if(E.c_y > 0)
   {
    --E.c_y;
    E.c_x=E.row[E.c_y].size;
   }
  }
  break;
 }

 if(E.c_y < E.num_rows)
 {
  row=&E.row[E.c_y];
 }

 int32_t row_len=0;

 if(row)
 {
  row_len=row->size;
 }
 else
 {
  row_len=0;
 }

 if(E.saved_r_x >= 0 && row && (key == ARROW_UP || key == ARROW_DOWN))
 {
  E.c_x=row_r_x_to_c_x(row,E.saved_r_x);
 }
 else if(E.c_x > row_len)
 {
  E.c_x=row_len;
 }

 if(row)
 {
  E.c_x=snap_to_utf8_start(row,E.c_x);
 }
}

void mouse_to_cursor(int32_t m_x,int32_t m_y,int32_t* c_x_out,int32_t* c_y_out)
{
 if(E.num_rows == 0)
 {
  *c_x_out=0;
  *c_y_out=0;
  return;
 }

 int32_t remaining=m_y;

 if(remaining < 0)
 {
  remaining=0;
 }

 int32_t file_row=E.row_off;
 int32_t segment=0;
 uint8_t found=0;

 while(file_row < E.num_rows)
 {
  int32_t segs=count_screen_rows(file_row);

  if(remaining < segs)
  {
   segment=remaining;
   found=1;
   break;
  }

  remaining-=segs;
  ++file_row;
 }

 if(!found)
 {
  *c_x_out=E.row[E.num_rows-1].size;
  *c_y_out=E.num_rows-1;
  return;
 }

 e_row* row=&E.row[file_row];
 int32_t cap=row->r_size+1;
 int32_t* starts=wrap_seg_buf(cap);
 int32_t seg_count=get_wrap_segments(file_row,starts,cap);

 if(segment >= seg_count)
 {
  segment=seg_count-1;
 }

 int32_t seg_vis_start=0;
 int32_t r_i=0;

 r_i=0;
 while(r_i < starts[segment])
 {
  uint8_t step_w=0;
  int32_t step=token_step(row,r_i,&step_w);

  if(row->render[r_i] == '\t')
  {
   step_w=(TAB_STOP-(seg_vis_start & (TAB_STOP-1)));
  }

  seg_vis_start+=step_w;
  r_i+=step;
 }

 int32_t offset=0;

 if(row_should_wrap(file_row))
 {
  offset=seg_vis_start+E.seg_col_off;
 }
 else
 {
  offset=E.col_off;
 }

 int32_t r_x=(m_x-E.line_num_width)+offset;

 if(r_x < 0)
 {
  r_x=0;
 }

 int32_t c_x=row_r_x_to_c_x(row,r_x);

 if(c_x > row->size)
 {
  c_x=row->size;
 }

 c_x=snap_to_utf8_start(row,c_x);

 *c_x_out=c_x;
 *c_y_out=file_row;
}

void select_word_at(int32_t c_x,int32_t c_y)
{
 if(c_y >= E.num_rows)
 {
  return;
 }

 e_row* row=&E.row[c_y];

 if(row->size == 0)
 {
  return;
 }

 int32_t pos=c_x;

 if(pos >= row->size)
 {
  pos=row->size-1;
 }

 pos=snap_to_utf8_start(row,pos);

 if(is_separator((unsigned char)row->characters[pos]))
 {
  return;
 }

 int32_t start=pos;
 int32_t end=pos;

 while(start > 0 && !is_separator((unsigned char)row->characters[start-1]))
 {
  --start;
 }

 while(end < row->size-1 && !is_separator((unsigned char)row->characters[end+1]))
 {
  ++end;
 }

 E.select_mode=SELECT_CHAR;
 E.select_anchor_x=start;
 E.select_anchor_y=c_y;
 E.saved_r_x=-1;
 E.c_x=end;
 E.c_y=c_y;
}

void process_keypress()
{
 static int8_t quit_times=QUIT_TIMES;
 static int8_t open_times=QUIT_TIMES;
 static int8_t refresh_times=QUIT_TIMES;
 static char utf8_buf[4];
 static int utf8_len=0;
 static int utf8_expected=0;
 actions action;
 memset(&action,0,sizeof(action));
 uint16_t c=read_key();

  if(c >= 1000 || c < 32 || c == 127)
  {
   utf8_len=0;
   utf8_expected=0;
  }

 switch(c)
 {
  case RESIZE_KEY:
  {
   window_resized=0;

   if(get_window_size(&E.term_rows,&E.screen_cols) == -1)
   {
    die("get_window_size [process_keypress]");
   }
   ++E.wrap_generation;
   return;
  }
  break;

  case '\r':
  {
   if(E.mode != MODE_INSERT)
   {
    return;
   }

   action.type=USER_ACTION_INSERT_NEWLINE;
   action.c_x=E.c_x;
   action.c_y=E.c_y;
   action.row_text=NULL;
   undo_push(&action);
   insert_new_line();
  }
  break;

  case CTRL_KEY('q'):
  {
   if(E.dirty && quit_times > 0)
   {
    set_status_message(ERROR_MSG_COLOR,"WARNING, File has unsaved changes, press Ctrl+q %d more times to quit.",quit_times);
    --quit_times;
    return;
   }

   write_all(STDOUT_FILENO,"\x1b[2J",4);
   write_all(STDOUT_FILENO,"\x1b[H",3);

   exit(0);
  }
  break;

  case CTRL_KEY('s'):
  {
   save_file();
  }
  break;

  case CTRL_KEY('o'):
  {
   if(E.dirty && open_times > 0)
   {
    set_status_message(ERROR_MSG_COLOR,"WARNING, File has unsaved changes, press Ctrl+o %d more times to discard and open another file.",open_times);
    --open_times;
    return;
   }

   char start_dir[4096]=".";

   if(E.file_name != NULL)
   {
    snprintf(start_dir,sizeof(start_dir),"%s",E.file_name);

    char* slash=strrchr(start_dir,BROWSE_SEP);

    if(slash)
    {
     *slash='\0';
    }
    else
    {
     snprintf(start_dir,sizeof(start_dir),".");
    }
   }

   char* selected=browse_for_file(start_dir);

   if(selected != NULL)
   {
    reset_editor_for_new_file();
    open_file(selected);
    free(selected);
   }
   return;
  }
  break;

  case CTRL_KEY('p'):
  {
   if(E.file_name == NULL)
   {
    set_status_message(ERROR_MSG_COLOR,"Nothing to refresh, file was never saved");
    return;
   }

   if(E.dirty && refresh_times > 0 && !E.file_modified_externally)
   {
    set_status_message(ERROR_MSG_COLOR,"WARNING, File has unsaved changes, press Ctrl+p %d more times to discard them and refresh.",refresh_times);
    --refresh_times;
    return;
   }

   char* current_file_name=strdup(E.file_name);
   reset_editor_for_new_file();
   open_file(current_file_name);
   free(current_file_name);
   set_status_message(SUCCESS_MSG_COLOR,"File content refreshed from disk");
   return;
  }
  break;

  case HOME_KEY:
  {
   E.saved_r_x=-1;
   E.c_x=0;
  }
  break;

  case END_KEY:
  {
   E.saved_r_x=-1;

   if(E.c_y < E.num_rows)
   {
    E.c_x=E.row[E.c_y].size;
   }
  }
  break;

  case CTRL_KEY('f'):
  {
   find();
  }
  break;

  case CTRL_KEY('w'):
  {
   search_and_replace();
  }
  break;

  case CTRL_KEY('g'):
  {
   go_to_line();
  }
  break;

  case CTRL_KEY('z'):
  {
   undo();
  }
  break;

  case CTRL_KEY('r'):
  {
   redo();
  }
  break;

  case CTRL_KEY('e'):
  {
   if(E.select_mode != SELECT_NONE)
   {
    E.select_mode=SELECT_NONE;
   }
   else
   {
    E.select_mode=SELECT_CHAR;
    E.select_anchor_x=E.c_x;
    E.select_anchor_y=E.c_y;
   }
   return;
  }
  break;

  case CTRL_KEY('i'):
  {
   if(E.mode == MODE_INSERT)
   {
    E.mode=MODE_NORMAL;
   }
   else
   {
    E.mode=MODE_INSERT;
   }
   return;
  }
  break;

  case CTRL_KEY('c'):
  {
   if(!E.select_mode)
   {
    E.select_mode=SELECT_ROW;
    E.select_anchor_x=E.c_x;
    E.select_anchor_y=E.c_y;
   }
   copy_selection();
   E.select_mode=SELECT_NONE;
   return;
  }
  break;

  case CTRL_KEY('x'):
  {
   if(!E.select_mode)
   {
    E.select_mode=SELECT_ROW;
    E.select_anchor_x=E.c_x;
    E.select_anchor_y=E.c_y;
   }
   copy_selection();
   delete_selection();
   E.select_mode=SELECT_NONE;
  }
  break;

  case CTRL_KEY('v'):
  {
   paste_clipboard();
  }
  break;

  case BRACKETED_PASTE:
  {
   if(paste_stream_buffer != NULL && paste_stream_len > 0)
   {
    int32_t start_x=E.c_x;
    int32_t start_y=E.c_y;
    uint32_t i=0;
    uint32_t clean_len=0;

    for(i=0;i < paste_stream_len;++i)
    {
     char p_c=paste_stream_buffer[i];

     if(p_c == '\n' || p_c == '\t' || ((unsigned char)p_c >= 32 && (unsigned char)p_c != 127))
     {
      paste_stream_buffer[clean_len++]=p_c;
     }
    }

    insert_text_range(paste_stream_buffer,clean_len);

    action.type=USER_ACTION_RANGE_INSERT;
    action.c_x=start_x;
    action.c_y=start_y;
    action.c_x_end=E.c_x;
    action.c_y_end=E.c_y;
    action.row_text=malloc(clean_len);

    if(action.row_text != NULL || clean_len == 0)
    {
     if(clean_len > 0)
     {
      memcpy(action.row_text,paste_stream_buffer,clean_len);
     }
     action.row_len=clean_len;
     undo_push(&action);
    }
    else
    {
     set_status_message(ERROR_MSG_COLOR,"Low memory: paste not added to undo history");
    }
   }

   free(paste_stream_buffer);
   paste_stream_buffer=NULL;
   paste_stream_len=0;
  }
  break;

  case BACKSPACE:
  case DEL_KEY:
  {
   if(E.mode != MODE_INSERT)
   {
    return;
   }

   if(c == DEL_KEY)
   {
    move_cursor(ARROW_RIGHT);
   }

   if(E.c_y < E.num_rows && !(E.c_x == 0 && E.c_y == 0))
   {
    action.row_text=NULL;

    if(E.c_x > 0)
    {
     e_row* row=&E.row[E.c_y];
     int32_t start_c_x=snap_to_utf8_start(row,E.c_x-1);

     action.type=USER_ACTION_DEL_CHAR;
     action.c_x=E.c_x;
     action.c_y=E.c_y;
     action.c_len=(uint8_t)(E.c_x-start_c_x);
     memcpy(action.c,&row->characters[start_c_x],action.c_len);
     undo_push(&action);
    }
    else
    {
     action.type=USER_ACTION_JOIN_LINES;
     action.c_x=0;
     action.c_y=E.c_y;
     action.join_col=E.row[E.c_y-1].size;
     action.row_len=E.row[E.c_y].size;
     action.row_text=action.row_len > 0 ? malloc(action.row_len) : NULL;

     if(action.row_text != NULL)
     {
      memcpy(action.row_text,E.row[E.c_y].characters,action.row_len);
      undo_push(&action);
     }
     else if(action.row_len == 0)
     {
      undo_push(&action);
     }
     else
     {
      set_status_message(ERROR_MSG_COLOR,"Low memory: join not added to undo history");
     }
    }
   }
   del_char();
  }
  break;

  case PAGE_UP:
  case PAGE_DOWN:
  {
   if(c == PAGE_UP)
   {
    E.c_y=E.row_off;
   }
   else if(c == PAGE_DOWN)
   {
    E.c_y=E.row_off+E.screen_rows-1;

    if(E.c_y > E.num_rows)
    {
     E.c_y=E.num_rows;
    }
   }

   int16_t times=E.screen_rows;

   while(times--)
   {
    if(c == PAGE_UP)
    {
     move_cursor(ARROW_UP);
    }
    else
    {
     move_cursor(ARROW_DOWN);
    }
   }
  }
  break;

  case MOUSE_WHEEL_UP:
  case MOUSE_WHEEL_DOWN:
  {
   uint8_t times=4;

   while(times--)
   {
    if(c == MOUSE_WHEEL_UP)
    {
     move_cursor(ARROW_UP);
    }
    else
    {
     move_cursor(ARROW_DOWN);
    }
   }
  }
  break;

  case MOUSE_LEFT_PRESS:
  {
   int32_t click_c_x=0;
   int32_t click_c_y=0;

   mouse_to_cursor(g_mouse_x,g_mouse_y,&click_c_x,&click_c_y);

   uint64_t now_ms=get_ms_ticks();
   uint8_t is_double=(s_last_click_c_x == click_c_x && s_last_click_c_y == click_c_y && (now_ms-s_last_click_ms) < 500);

   s_last_click_c_x=click_c_x;
   s_last_click_c_y=click_c_y;
   s_last_click_ms=now_ms;

   E.saved_r_x=-1;
   E.c_x=click_c_x;
   E.c_y=click_c_y;

   if(is_double)
   {
    select_word_at(click_c_x,click_c_y);
   }
   else
   {
    E.select_mode=SELECT_CHAR;
    E.select_anchor_x=click_c_x;
    E.select_anchor_y=click_c_y;
   }
  }
  break;

  case MOUSE_LEFT_DRAG:
  {
   int32_t drag_c_x=0;
   int32_t drag_c_y=0;

   mouse_to_cursor(g_mouse_x,g_mouse_y,&drag_c_x,&drag_c_y);

   E.saved_r_x=-1;

   if(E.select_mode == SELECT_NONE)
   {
    E.select_mode=SELECT_CHAR;
    E.select_anchor_x=drag_c_x;
    E.select_anchor_y=drag_c_y;
   }

   E.c_x=drag_c_x;
   E.c_y=drag_c_y;
  }
  break;

  case MOUSE_LEFT_RELEASE:
  {
   if(E.select_mode == SELECT_CHAR && E.select_anchor_x == E.c_x && E.select_anchor_y == E.c_y)
   {
    E.select_mode=SELECT_NONE;
   }
  }
  break;

  case MOUSE_MIDDLE_CLICK:
  {
   int32_t paste_c_x=0;
   int32_t paste_c_y=0;

   mouse_to_cursor(g_mouse_x,g_mouse_y,&paste_c_x,&paste_c_y);

   E.saved_r_x=-1;
   E.c_x=paste_c_x;
   E.c_y=paste_c_y;

   paste_clipboard();
  }
  break;

  case MOUSE_RIGHT_PRESS:
  {
   if(E.select_mode != SELECT_NONE)
   {
    copy_selection();
    E.select_mode=SELECT_NONE;
   }
  }
  break;

  case 'w':
  {
   if(E.mode == MODE_NORMAL)
   {
    move_cursor(ARROW_UP);
   }
   else
   {
    E.saved_r_x=-1;
    action.type=USER_ACTION_INSERT_CHAR;
    action.c_x=E.c_x;
    action.c_y=E.c_y;
    action.c[0]=(char)c;
    action.c_len=1;
    action.row_text=NULL;
    undo_push(&action);
    insert_char(c);
   }
  }
  break;

  case 'a':
  {
   if(E.mode == MODE_NORMAL)
   {
    move_cursor(ARROW_LEFT);
   }
   else
   {
    E.saved_r_x=-1;
    action.type=USER_ACTION_INSERT_CHAR;
    action.c_x=E.c_x;
    action.c_y=E.c_y;
    action.c[0]=(char)c;
    action.c_len=1;
    action.row_text=NULL;
    undo_push(&action);
    insert_char(c);
   }
  }
  break;

  case 's':
  {
   if(E.mode == MODE_NORMAL)
   {
    move_cursor(ARROW_DOWN);
   }
   else
   {
    E.saved_r_x=-1;
    action.type=USER_ACTION_INSERT_CHAR;
    action.c_x=E.c_x;
    action.c_y=E.c_y;
    action.c[0]=(char)c;
    action.c_len=1;
    action.row_text=NULL;
    undo_push(&action);
    insert_char(c);
   }
  }
  break;

  case 'd':
  {
   if(E.mode == MODE_NORMAL)
   {
    move_cursor(ARROW_RIGHT);
   }
   else
   {
    E.saved_r_x=-1;
    action.type=USER_ACTION_INSERT_CHAR;
    action.c_x=E.c_x;
    action.c_y=E.c_y;
    action.c[0]=(char)c;
    action.c_len=1;
    action.row_text=NULL;
    undo_push(&action);
    insert_char(c);
   }
  }
  break;

  case ARROW_UP:
  case ARROW_DOWN:
  case ARROW_RIGHT:
  case ARROW_LEFT:
  {
   move_cursor(c);
  }
  break;

  case CTRL_KEY('h'):
  {
   /*
    HELP: Ctrl+h=Help (Prints this)
    ----------------------------------
    | Ctrl+s=Save   | Ctrl+q=Quit    |
    | Ctrl+i=Insert | Ctrl+e=Select  |
    | Ctrl+z=Undo   | Ctrl+r=Redo    |
    | Ctrl+o=Open   | Ctrl+p=Reopen  |
    | Ctrl+g=Go to  | Ctrl+x=Cut     |
    | Ctrl+c=Copy   | Ctrl+v=Paste   |
    | Ctrl+f=Find   | Ctrl+w=Replace |
    ----------------------------------
   */
   set_status_message(HELP_MSG_COLOR,"HELP: Ctrl+h=Help (Prints this)\n----------------------------------\n| Ctrl+s=Save   | Ctrl+q=Quit    |\n| Ctrl+i=Insert | Ctrl+e=Select  |\n| Ctrl+z=Undo   | Ctrl+r=Redo    |\n| Ctrl+o=Open   | Ctrl+p=Reopen  |\n| Ctrl+g=Go to  | Ctrl+x=Cut     |\n| Ctrl+c=Copy   | Ctrl+v=Paste   |\n| Ctrl+f=Find   | Ctrl+w=Replace |\n----------------------------------");
  }
  break;

  case '\x1b':
  {
   if(E.select_mode)
   {
    E.select_mode=SELECT_NONE;
   }

   if(E.mode == MODE_INSERT)
   {
    E.mode=MODE_NORMAL;
   }
  }
  break;

  default:
  {
   if(E.mode != MODE_INSERT)
   {
    return;
   }


   if(c != '\t' && (c < 32 || c == 127))
   {
    return;
   }

   if(E.utf8_output)
   {
    if(utf8_expected > 0)
    {
     if((c & 0xC0) == 0x80)
     {
      utf8_buf[utf8_len++]=(char)c;

      if(utf8_len == utf8_expected)
      {
       insert_utf8_char(utf8_buf,utf8_len);
       utf8_len=0;
       utf8_expected=0;
      }
      return;
     }
     else
     {
      insert_utf8_char(utf8_buf,1);
      utf8_len=0;
      utf8_expected=0;
     }
    }

    if(c >= 0xC2 && c <= 0xDF)
    {
     utf8_buf[0]=(char)c;
     utf8_len=1;
     utf8_expected=2;
     return;
    }
    else if(c >= 0xE0 && c <= 0xEF)
    {
     utf8_buf[0]=(char)c;
     utf8_len=1;
     utf8_expected=3;
     return;
    }
    else if(c >= 0xF0 && c <= 0xF4)
    {
     utf8_buf[0]=(char)c;
     utf8_len=1;
     utf8_expected=4;
     return;
    }
   }

   E.saved_r_x=-1;
   action.type=USER_ACTION_INSERT_CHAR;
   action.c_x=E.c_x;
   action.c_y=E.c_y;
   action.c[0]=(char)c;
   action.c_len=1;
   action.row_text=NULL;
   undo_push(&action);
   insert_char(c);
  }
  break;
 }

 if(c != CTRL_KEY('q'))
 {
  quit_times=QUIT_TIMES;
 }

 if(c != CTRL_KEY('o'))
 {
  open_times=QUIT_TIMES;
 }

 if(c != CTRL_KEY('p'))
 {
  refresh_times=QUIT_TIMES;
 }
}

/*** output ***/
uint32_t utf8_decode_buf(const char* buffer,int32_t i,int32_t len,uint8_t seq_len)
{
 unsigned char lead=(unsigned char)buffer[i];
 uint32_t c_p=0;

 if(seq_len == 2)
 {
  c_p=lead & 0x1F;
 }
 else if(seq_len == 3)
 {
  c_p=lead & 0x0F;
 }
 else if(seq_len == 4)
 {
  c_p=lead & 0x07;
 }
 else
 {
  return lead;
 }

 uint8_t k=1;

 for(k=1;k < seq_len;++k)
 {
  if(i+k >= len || ((unsigned char)buffer[i+k] & 0xC0) != 0x80)
  {
   return lead;
  }
  c_p=(c_p << 6) | ((unsigned char)buffer[i+k] & 0x3F);
 }
 return c_p;
}

uint8_t code_point_is_wide(uint32_t c_p)
{
 if(c_p >= 0x1100 && c_p <= 0x115F)
 {
  return 1;
 }
 if(c_p == 0x2329 || c_p == 0x232A)
 {
  return 1;
 }
 if(c_p >= 0x2600 && c_p <= 0x27BF)
 {
  return 1;
 }
 if(c_p >= 0x2E80 && c_p <= 0xA4CF && c_p != 0x303F)
 {
  return 1;
 }
 if(c_p >= 0xAC00 && c_p <= 0xD7A3)
 {
  return 1;
 }
 if(c_p >= 0xF900 && c_p <= 0xFAFF)
 {
  return 1;
 }
 if(c_p >= 0xFE30 && c_p <= 0xFE6F)
 {
  return 1;
 }
 if(c_p >= 0xFF00 && c_p <= 0xFF60)
 {
  return 1;
 }
 if(c_p >= 0xFFE0 && c_p <= 0xFFE6)
 {
  return 1;
 }
 if(c_p >= 0x1F300 && c_p <= 0x1FAFF)
 {
  return 1;
 }
 if(c_p >= 0x20000 && c_p <= 0x3FFFD)
 {
  return 1;
 }
 return 0;
}

int32_t token_step(e_row* row,int32_t i,uint8_t* out_width)
{
 uint8_t h=row->highlight[i];

 if(h == H_CTRL)
 {
  *out_width=6;
  return 6;
 }
 if(h == H_HEX)
 {
  *out_width=4;
  return 4;
 }

 unsigned char c=(unsigned char)row->render[i];

 if(c < 0x80)
 {
  *out_width=1;
  return 1;
 }
 else if(E.utf8_output && (c & 0xE0) == 0xC0)
 {
  if(i+1 < row->r_size && ((unsigned char)row->render[i+1] & 0xC0) == 0x80)
  {
   uint32_t c_p=utf8_decode_buf(row->render,i,row->r_size,2);
   *out_width=code_point_is_wide(c_p) ? 2 : 1;
   return 2;
  }
 }
 else if(E.utf8_output && (c & 0xF0) == 0xE0)
 {
  if(i+2 < row->r_size && ((unsigned char)row->render[i+1] & 0xC0) == 0x80 && ((unsigned char)row->render[i+2] & 0xC0) == 0x80)
  {
   uint32_t c_p=utf8_decode_buf(row->render,i,row->r_size,3);
   *out_width=code_point_is_wide(c_p) ? 2 : 1;
   return 3;
  }
 }
 else if(E.utf8_output && (c & 0xF8) == 0xF0)
 {
  if(i+3 < row->r_size && ((unsigned char)row->render[i+1] & 0xC0) == 0x80 && ((unsigned char)row->render[i+2] & 0xC0) == 0x80 && ((unsigned char)row->render[i+3] & 0xC0) == 0x80)
  {
   uint32_t c_p=utf8_decode_buf(row->render,i,row->r_size,4);
   *out_width=code_point_is_wide(c_p) ? 2 : 1;
   return 4;
  }
 }

 *out_width=rendered_char_width(row->render,i,row->r_size);
 return 1;
}

uint8_t rendered_char_width(const char* buffer,int32_t i,int32_t len)
{
 unsigned char c=(unsigned char)buffer[i];

 if(iscntrl(c))
 {
  return 6;
 }
 else if(c > 127)
 {
  if(E.utf8_output)
  {
   if((c & 0xC0) == 0x80)
   {
    return 0;
   }

   uint8_t seq_len=1;

   if((c & 0xE0) == 0xC0)
   {
    seq_len=2;
   }
   else if((c & 0xF0) == 0xE0)
   {
    seq_len=3;
   }
   else if((c & 0xF8) == 0xF0)
   {
    seq_len=4;
   }

   if(seq_len == 1 || i+seq_len > len)
   {
    return 1;
   }

   uint8_t k=1;

   for(k=1;k < seq_len;++k)
   {
    if(((unsigned char)buffer[i+k] & 0xC0) != 0x80)
    {
     return 1;
    }
   }

   uint32_t c_p=utf8_decode_buf(buffer,i,len,seq_len);

   return code_point_is_wide(c_p) ? 2 : 1;
  }
  return 4;
 }
 else
 {
  return 1;
 }
}

static int32_t compute_wrap_segments(e_row* row,int32_t* seg_render_starts,int32_t max_segs)
{
 if(max_segs < 1)
 {
  return 0;
 }

 seg_render_starts[0]=0;

 int32_t available=E.screen_cols-E.line_num_width;

 if(available <= 0)
 {
  return 1;
 }

 int32_t total=0;
 int32_t i=0;

 for(i=0;i < row->r_size;++i)
 {
  total+=rendered_char_width(row->render,i,row->r_size);
 }

 if(total <= available)
 {
  return 1;
 }

 int32_t first_n_w_space=0;

 while(first_n_w_space < row->r_size && (row->render[first_n_w_space] == ' ' || row->render[first_n_w_space] == '\t'))
 {
  ++first_n_w_space;
 }

 int32_t last_n_w_space=row->r_size-1;

 while(last_n_w_space > first_n_w_space && (row->render[last_n_w_space] == ' ' || row->render[last_n_w_space] == '\t'))
 {
  --last_n_w_space;
 }

 uint8_t has_break=0;

 for(i=first_n_w_space;i <= last_n_w_space;++i)
 {
  if(row->render[i] == ' ' || row->render[i] == '\t')
  {
   has_break=1;
   break;
  }
 }

 if(!has_break)
 {
  return 1;
 }

 int32_t count=1;
 int32_t pos=0;

 while(pos < row->r_size && count < max_segs)
 {
  int32_t cols=0;
  int32_t l_w_e=-1;
  int32_t n_f_w_s=-1;
  int32_t s_p=pos;

  while(s_p < row->r_size)
  {
   unsigned char c=(unsigned char)row->render[s_p];
   uint8_t step_w=0;
   int32_t step=token_step(row,s_p,&step_w);
   int32_t next_cols=cols+step_w;

   if(next_cols > available)
   {
    break;
   }

   if(c==' ')
   {
    l_w_e=s_p;
    n_f_w_s=s_p+step;
   }
   else if(row->highlight[s_p] == H_CTRL || row->highlight[s_p] == H_HEX)
   {
    l_w_e=s_p;
    n_f_w_s=s_p+step;
   }

   cols=next_cols;
   s_p+=step;
  }

  if(s_p >= row->r_size)
  {
   break;
  }

  int32_t n_pos=0;

  if(l_w_e >= 0) 
  {
   n_pos=n_f_w_s;
  } 
  else 
  {
   while(s_p < row->r_size && row->render[s_p] != ' ' && row->render[s_p] != '\t') 
   {
    ++s_p;
   }

   if(E.utf8_output && s_p > 0 && ((unsigned char)row->render[s_p] & 0xC0) == 0x80)
   {
    while(s_p > 0 && ((unsigned char)row->render[s_p] & 0xC0) == 0x80)
    {
     --s_p;
    }
   }

   n_pos=s_p;
  }

  if(n_pos <= pos)
  {
   break;
  }

  if(n_pos >= row->r_size)
  {
   break;
  }

  pos=n_pos;
  seg_render_starts[count++]=pos;
 }
 return count;
}

static void ensure_wrap_cache(e_row* row)
{
 if(row->wrap_epoch == E.wrap_generation)
 {
  return;
 }

 int32_t cap=row->r_size+1;

 if(cap > row->wrap_starts_cap)
 {
  int32_t* new_starts=realloc(row->wrap_starts,(size_t)cap*sizeof(int32_t));

  if(new_starts == NULL)
  {
   die("realloc [ensure_wrap_cache]");
  }

  row->wrap_starts=new_starts;
  row->wrap_starts_cap=cap;
 }

 row->wrap_seg_count=compute_wrap_segments(row,row->wrap_starts,cap);
 row->wrap_epoch=E.wrap_generation;
}

uint8_t row_should_wrap(int32_t file_row)
{
 if(file_row >= E.num_rows)
 {
  return 0;
 }

 e_row* row=&E.row[file_row];

 ensure_wrap_cache(row);

 return row->wrap_seg_count > 1;
}

int32_t* wrap_seg_buf(int32_t needed)
{
 if(needed > wrap_starts_cap)
 {
  int32_t new_cap=wrap_starts_cap == 0 ? SIZE_LIMIT : wrap_starts_cap;

  while(new_cap < needed)
  {
   new_cap<<=1;
  }

  int32_t* new_buf=realloc(wrap_starts_buf,(size_t)new_cap*sizeof(int32_t));

  if(new_buf == NULL)
  {
   die("realloc [wrap_seg_buf]");
  }

  wrap_starts_buf=new_buf;
  wrap_starts_cap=new_cap;
 }
 return wrap_starts_buf;
}

int32_t get_wrap_segments(int32_t file_row,int32_t* seg_render_starts,int32_t max_segs)
{
 if(max_segs < 1)
 {
  return 0;
 }

 if(file_row >= E.num_rows)
 {
  seg_render_starts[0]=0;
  return 1;
 }

 e_row* row=&E.row[file_row];

 ensure_wrap_cache(row);

 int32_t count=row->wrap_seg_count < max_segs ? row->wrap_seg_count : max_segs;
 int32_t i=0;

 for(i=0;i < count;++i)
 {
  seg_render_starts[i]=row->wrap_starts[i];
 }

 return count;
}

int32_t count_screen_rows(int32_t file_row)
{
 if(file_row >= E.num_rows)
 {
  return 1;
 }

 e_row* row=&E.row[file_row];

 ensure_wrap_cache(row);

 return row->wrap_seg_count;
}

int32_t get_cursor_segment_info(int32_t file_row,int32_t r_x,int32_t* seg_visual_start)
{
 *seg_visual_start=0;

 if(file_row >= E.num_rows || !row_should_wrap(file_row))
 {
  return 0;
 }

 e_row* row=&E.row[file_row];
 int32_t cap=row->r_size+1;
 int32_t* starts=wrap_seg_buf(cap);
 int32_t count=get_wrap_segments(file_row,starts,cap);
 int32_t visual=0;
 int32_t r_i=0;
 int32_t seg=0;
 int32_t best_seg=0;
 int32_t best_visual=0;

 for(seg=0;seg < count;++seg)
 {
  while(r_i < starts[seg])
  {
   uint8_t step_w=0;
   int32_t step=token_step(row, r_i, &step_w);

   if(row->render[r_i] == '\t')
   {
    step_w=(TAB_STOP-(visual & (TAB_STOP-1)));
   }
   visual+=step_w;
   r_i+=step;
  }

  if(visual > r_x)
  {
   break;
  }

  best_seg=seg;
  best_visual=visual;
 }
 *seg_visual_start=best_visual;
 return best_seg;
}

void scroll()
{
 E.r_x=0;
 uint8_t padding=4;

 if(E.c_y < E.num_rows)
 {
  E.r_x=row_c_x_to_r_x(&E.row[E.c_y],E.c_x);
 }

 if(E.c_y < (E.row_off+padding))
 {
  E.row_off=E.c_y-padding;
 }

 if(E.row_off < 0)
 {
  E.row_off=0;
 }

 if(E.num_rows > 0)
 {
  if(E.row_off > E.num_rows-1)
  {
   E.row_off=E.num_rows-1;
  }
 }
 else
 {
  E.row_off=0;
 }

 int32_t c_s_row=0;
 int32_t r=0;

 for(r=E.row_off;r < E.c_y && r < E.num_rows;++r)
 {
  c_s_row+=count_screen_rows(r);
 }

 int32_t dummy=0;
 c_s_row+=get_cursor_segment_info(E.c_y,E.r_x,&dummy);
 int32_t max_row_off=(E.num_rows > 0) ? E.num_rows-1 : 0;
 int32_t scroll_limit=E.screen_rows > padding ? E.screen_rows-padding : E.screen_rows;

 while(c_s_row >= scroll_limit && E.row_off < max_row_off)
 {
  c_s_row-=count_screen_rows(E.row_off);
  ++E.row_off;
 }

 if(E.row_off < 0)
 {
  E.row_off=0;
 }

 if(E.num_rows > 0)
 {
  if(E.row_off > E.num_rows-1)
  {
   E.row_off=E.num_rows-1;
  }
 }
 else
 {
  E.row_off=0;
 }

 if(E.num_rows > 0)
 {
  int32_t total=1;
  int32_t current_row=E.num_rows-1;
  int32_t allowed_bottom_off=0;

  for(current_row=E.num_rows-1;current_row >= 0;--current_row)
  {
   total+=count_screen_rows(current_row);

   if(total >= E.screen_rows)
   {
    allowed_bottom_off=current_row;
    break;
   }
  }

  if(E.row_off > allowed_bottom_off)
  {
   E.row_off=allowed_bottom_off;
  }
 }
 else
 {
  E.row_off=0;
 }

 int32_t available=E.screen_cols-E.line_num_width;

 if(row_should_wrap(E.c_y) && E.c_y < E.num_rows)
 {
  E.col_off=0;
  int32_t s_visual=0;
  get_cursor_segment_info(E.c_y,E.r_x,&s_visual);
  int32_t p_in_seg=E.r_x-s_visual;

  if(p_in_seg < E.seg_col_off+padding)
  {
   E.seg_col_off=p_in_seg-padding;
  }
  if(p_in_seg >= E.seg_col_off+available-padding)
  {
   E.seg_col_off=p_in_seg-available+padding+1;
  }
  if(E.seg_col_off < 0)
  {
   E.seg_col_off=0;
  }
 }
 else
 {
  E.seg_col_off=0;

  if(E.r_x < E.col_off+padding)
  {
   E.col_off=E.r_x-padding;
  }

  if(E.r_x >= E.col_off+available-padding)
  {
   E.col_off=E.r_x-available+padding+1;
  }

  if(E.col_off < 0)
  {
   E.col_off=0;
  }

  if(E.col_off > 0 && E.c_y < E.num_rows)
  {
   e_row* snap_row=&E.row[E.c_y];
   int32_t v_col=0;
   int32_t r_i=0;

   while(r_i < snap_row->r_size)
   {
    uint8_t step_w=0;
    int32_t step=token_step(snap_row,r_i,&step_w);

    if(snap_row->render[r_i] == '\t')
    {
     step_w=(TAB_STOP-(v_col & (TAB_STOP-1)));
    }

    if(v_col+step_w > E.col_off)
    {
     break;
    }

    v_col+=step_w;
    r_i+=step;
   }
   E.col_off=v_col;
  }
 }
}

void draw_rows(a_buf* a_buffer)
{
 int32_t y=0;
 int32_t file_row=E.row_off;
 int32_t available=E.screen_cols-E.line_num_width;

 while(y < E.screen_rows)
 {
  char line_num_buf[256];
  char line_num_color[16];
  int8_t line_num_coloreplacement_len=snprintf(line_num_color,sizeof(line_num_color),"\x1b[%d;%dm",FG_LINE_NUM_COLOR,BG_LINE_NUM_COLOR);

  if(file_row >= E.num_rows)
  {
   snprintf(line_num_buf,sizeof(line_num_buf),"~%-*s",E.line_num_width-1,"");
   a_buf_append(a_buffer,line_num_color,line_num_coloreplacement_len);
   a_buf_append(a_buffer,line_num_buf,E.line_num_width);
   a_buf_append(a_buffer,"\x1b[0m",4);

   if(E.num_rows == 0)
   {
    char logo_lines[12][88]={
     "rrrrr   rrrrrrrrr  wwwwwww           wwwww           wwwwwww  xxxxxxx      xxxxxxx",
     "r::::rrr:::::::::r  w:::::w         w:::::w         w:::::w    x:::::x    x:::::x ",
     "r:::::::::::::::::r  w:::::w       w:::::::w       w:::::w      x:::::x  x:::::x  ",
     "rr::::::rrrrr::::::r  w:::::w     w:::::::::w     w:::::w        x:::::xx:::::x   ",
     " r:::::r     r:::::r   w:::::w   w:::::w:::::w   w:::::w          x::::::::::x    ",
     " r:::::r     rrrrrrr    w:::::w w:::::w w:::::w w:::::w            x::::::::x     ",
     " r:::::r                 w:::::w:::::w   w:::::w:::::w             x::::::::x     ",
     " r:::::r                  w:::::::::w     w:::::::::w             x::::::::::x    ",
     " r:::::r                   w:::::::w       w:::::::w             x:::::xx:::::x   ",
     " r:::::r                    w:::::w         w:::::w             x:::::x  x:::::x  ",
     " r:::::r                     w:::w           w:::w             x:::::x    x:::::x ",
     " rrrrrrr                      www             www             xxxxxxx      xxxxxxx"
    };

    int32_t version_row=E.screen_rows>>2;
    int32_t logo_row=version_row-14;
    int8_t show_logo=(logo_row >= 2 && available >= 84);

    if(show_logo && y >= logo_row && y < logo_row+12)
    {
     int32_t index=y-logo_row;
     int32_t l_len=(int32_t)strlen(logo_lines[index]);

     if(l_len > available)
     {
      l_len=available;
     }

     int32_t padding_1=(available-l_len)>>1;

     while(padding_1-- > 0)
     {
      a_buf_append(a_buffer," ",1);
     }
     a_buf_append(a_buffer,logo_lines[index],l_len);
    }

    if(y == version_row)
    {
     char version[32];
     int32_t v_len=snprintf(version,sizeof(version),"rwx editor version %s",RWX_VERSION);

     if(v_len > available)
     {
      v_len=available;
     }

     int32_t padding_2=(available-v_len)>>1;

     while(padding_2-- > 0)
     {
      a_buf_append(a_buffer," ",1);
     }
     a_buf_append(a_buffer,version,v_len);
    }
    else if(y == version_row+2)
    {
     char help[16]="Ctrl+h=Help";
     int8_t h_len=11;

     if(h_len > available)
     {
      h_len=available;
     }

     int32_t padding_3=(available-h_len)>>1;

     while(padding_3-- > 0)
     {
      a_buf_append(a_buffer," ",1);
     }
     a_buf_append(a_buffer,help,h_len);
    }
    else if(y == version_row+4)
    {
     char open[16]="Ctrl+o=Open";
     int8_t o_len=11;

     if(o_len > available)
     {
      o_len=available;
     }

     int32_t padding_4=(available-o_len)>>1;

     while(padding_4-- > 0)
     {
      a_buf_append(a_buffer," ",1);
     }
     a_buf_append(a_buffer,open,o_len);
    }
    else if(y == version_row+6)
    {
     char quit[16]="Ctrl+q=Quit";
     int8_t q_len=11;

     if(q_len > available)
     {
      q_len=available;
     }

     int32_t padding_5=(available-q_len)>>1;

     while(padding_5-- > 0)
     {
      a_buf_append(a_buffer," ",1);
     }
     a_buf_append(a_buffer,quit,q_len);
    }
   }
   a_buf_append(a_buffer,"\x1b[K",3);
   a_buf_append(a_buffer,"\r\n",2);

   ++y;
   ++file_row;

   continue;
  }

  e_row* row=&E.row[file_row];
  uint8_t wraps=row_should_wrap(file_row);
  int32_t cap=row->r_size+1;
  int32_t* seg_starts=wrap_seg_buf(cap);
  int32_t seg_count=1;
  seg_starts[0]=0;

  if(wraps)
  {
   seg_count=get_wrap_segments(file_row,seg_starts,cap);
  }

  int32_t seg_index=0;

  while(seg_index < seg_count && y < E.screen_rows)
  {
   uint8_t is_first=(seg_index == 0);

   if(is_first)
   {
    if(wraps)
    {
     snprintf(line_num_buf,sizeof(line_num_buf),"%*d|",E.line_num_width-1,file_row+1);
    }
    else
    {
     int32_t total_w=0;
     int32_t j=0;

     for(j=0;j < row->r_size;++j)
     {
      total_w+=rendered_char_width(row->render,j,row->r_size);
     }

     if(total_w > available)
     {
      snprintf(line_num_buf,sizeof(line_num_buf),"%*d>",E.line_num_width-1,file_row+1);
     }
     else
     {
      snprintf(line_num_buf,sizeof(line_num_buf),"%*d|",E.line_num_width-1,file_row+1);
     }
    }
   }
   else
   {
    snprintf(line_num_buf,sizeof(line_num_buf),"%*s#|",E.line_num_width-2,"");
   }

   a_buf_append(a_buffer,line_num_color,line_num_coloreplacement_len);
   a_buf_append(a_buffer,line_num_buf,E.line_num_width);
   a_buf_append(a_buffer,"\x1b[0m",4);

   int32_t render_start=0;
   int32_t render_end=0;

   if(wraps)
   {
    int32_t seg_end=0;

    if(seg_index+1 < seg_count)
    {
     seg_end=seg_starts[seg_index+1]-1;
    }
    else
    {
     seg_end=row->r_size;
    }

    render_start=seg_starts[seg_index];
    int32_t v_col_s=0;

    while(render_start < seg_end)
    {
     uint8_t r_c_w_1=0;
     int32_t step=token_step(row,render_start,&r_c_w_1);

     if(v_col_s+r_c_w_1 > E.seg_col_off)
     {
      break;
     }

     v_col_s+=r_c_w_1;
     render_start+=step;
    }
    render_end=seg_end;
   }
   else
   {
    render_start=0;
    int32_t v_col=0;

    while(render_start < row->r_size)
    {
     uint8_t r_c_w_2=0;
     int32_t step=token_step(row,render_start,&r_c_w_2);

     if(v_col+r_c_w_2 > E.col_off)
     {
      break;
     }

     v_col+=r_c_w_2;
     render_start+=step;
    }
    render_end=row->r_size;
   }

   int32_t r_i=render_start;
   int32_t cols_used=0;

   while(r_i < render_end)
   {
    uint8_t r_c_w_3=0;
    int32_t step=token_step(row,r_i,&r_c_w_3);

    if(cols_used+r_c_w_3 > available)
    {
     break;
    }

    cols_used+=r_c_w_3;
    r_i+=step;
   }

   int32_t i=0;
   int8_t current_color=-1;
   int32_t absolute_v_col=0;
   int32_t len_chars=r_i-render_start;

   if(wraps)
   {
    int32_t j=0;
    while(j < render_start)
    {
     uint8_t step_w=0;
     int32_t step=token_step(row,j,&step_w);

     if(row->render[j] == '\t')
     {
      step_w=(TAB_STOP-(absolute_v_col & (TAB_STOP-1)));
     }

     absolute_v_col+=step_w;
     j+=step;
    }
   }
   else
   {
    absolute_v_col=E.col_off;
   }

   int32_t c_x_running=row_r_x_to_c_x(row,absolute_v_col);

   for(i=0;i < len_chars;++i)
   {
    unsigned char c_i=(unsigned char)row->render[render_start+i];
    uint8_t h_i=row->highlight[render_start+i];
    int32_t c_x_advance=1;

    if(h_i == H_CTRL)
    {
     char color_cmd_1[16];
     int8_t cmd_len_1=snprintf(color_cmd_1,sizeof(color_cmd_1),"\x1b[%d;%dm",FG_CTRL_AND_HEX_COLOR,BG_CTRL_AND_HEX_COLOR);
     uint8_t selected_1=!(file_row == E.c_y && c_x_running == E.c_x) && is_selected(file_row,c_x_running);

     a_buf_append(a_buffer,color_cmd_1,cmd_len_1);

     if(selected_1)
     {
      a_buf_append(a_buffer,"\x1b[7m",4);
     }

     a_buf_append(a_buffer,&row->render[render_start+i],6);

     if(selected_1)
     {
      a_buf_append(a_buffer,"\x1b[27m",5);
     }

     a_buf_append(a_buffer,"\x1b[0m",4);

     if(current_color != -1)
     {
      char buffer_2[16];
      int8_t s_len_2=snprintf(buffer_2,sizeof(buffer_2),"\x1b[%dm",current_color);
      a_buf_append(a_buffer,buffer_2,s_len_2);
     }
     i+=5;
    }
    else if(h_i == H_HEX)
    {
     char color_cmd_2[16];
     int8_t cmd_len_2=snprintf(color_cmd_2,sizeof(color_cmd_2),"\x1b[%d;%dm",FG_CTRL_AND_HEX_COLOR,BG_CTRL_AND_HEX_COLOR);
     uint8_t selected_2=!(file_row == E.c_y && c_x_running == E.c_x) && is_selected(file_row,c_x_running);

     a_buf_append(a_buffer,color_cmd_2,cmd_len_2);

     if(selected_2)
     {
      a_buf_append(a_buffer,"\x1b[7m",4);
     }

     a_buf_append(a_buffer,&row->render[render_start+i],4);

     if(selected_2)
     {
      a_buf_append(a_buffer,"\x1b[27m",5);
     }

     a_buf_append(a_buffer,"\x1b[0m",4);

     if(current_color != -1)
     {
      char buffer_3[16];
      int8_t s_len_3=snprintf(buffer_3,sizeof(buffer_3),"\x1b[%dm",current_color);
      a_buf_append(a_buffer,buffer_3,s_len_3);
     }
     i+=3;
    }
    else if(c_i > 127)
    {
     uint8_t seq_len=0;

     if(E.utf8_output)
     {
      if((c_i & 0xE0) == 0xC0)
      {
       seq_len=2;
      }
      else if((c_i & 0xF0) == 0xE0)
      {
       seq_len=3;
      }
      else if((c_i & 0xF8) == 0xF0)
      {
       seq_len=4;
      }
     }

     if(seq_len > 1 && i+seq_len <= len_chars)
     {
      if(h_i != H_NORMAL)
      {
       int8_t color=syntax_to_color(h_i);

       if(color != current_color)
       {
        current_color=color;
        char buffer_5[16];
        int8_t s_len_5=snprintf(buffer_5,sizeof(buffer_5),"\x1b[%dm",color);
        a_buf_append(a_buffer,buffer_5,s_len_5);
       }
      }
      else if(current_color != -1)
      {
       a_buf_append(a_buffer,"\x1b[39m",5);
       current_color=-1;
      }

      if(is_selected(file_row,c_x_running) && !(file_row == E.c_y && c_x_running == E.c_x))
      {
       a_buf_append(a_buffer,"\x1b[7m",4);
       a_buf_append(a_buffer,&row->render[render_start+i],seq_len);
       a_buf_append(a_buffer,"\x1b[27m",5);
      }
      else
      {
       a_buf_append(a_buffer,&row->render[render_start+i],seq_len);
      }
      i+=seq_len-1;
      c_x_advance=seq_len;
     }
    }
    else if(h_i == H_NORMAL)
    {
     if(current_color != -1)
     {
      a_buf_append(a_buffer,"\x1b[39m",5);
      current_color=-1;
     }

     if(is_selected(file_row,c_x_running) && !(file_row == E.c_y && c_x_running == E.c_x))
     {
      a_buf_append(a_buffer,"\x1b[7m",4);
      a_buf_append(a_buffer,&row->render[render_start+i],1);
      a_buf_append(a_buffer,"\x1b[27m",5);
     }
     else
     {
      a_buf_append(a_buffer,&row->render[render_start+i],1);
     }
    }
    else
    {
     int8_t color=syntax_to_color(h_i);

     if(color != current_color)
     {
      current_color=color;
      char buffer_4[16];
      int8_t s_len_4=snprintf(buffer_4,sizeof(buffer_4),"\x1b[%dm",color);
      a_buf_append(a_buffer,buffer_4,s_len_4);
     }

     if(is_selected(file_row,c_x_running) && !(file_row == E.c_y && c_x_running == E.c_x))
     {
      a_buf_append(a_buffer,"\x1b[7m",4);
      a_buf_append(a_buffer,&row->render[render_start+i],1);
      a_buf_append(a_buffer,"\x1b[27m",5);
     }
     else
     {
      a_buf_append(a_buffer,&row->render[render_start+i],1);
     }
    }
    c_x_running+=c_x_advance;
   }
   a_buf_append(a_buffer,"\x1b[39m",5);
   a_buf_append(a_buffer,"\x1b[K",3);
   a_buf_append(a_buffer,"\r\n",2);

   ++y;
   ++seg_index;
  }
  ++file_row;
 }
}

void draw_status_bar(a_buf* a_buffer)
{
 char* mode_word;
 uint8_t mode_fg;
 uint8_t mode_bg;

 if(E.select_mode != SELECT_NONE)
 {
  mode_word=" VISUAL ";
  mode_fg=FG_VISUAL_MODE_COLOR;
  mode_bg=BG_VISUAL_MODE_COLOR;
 }
 else if(E.mode == MODE_INSERT)
 {
  mode_word=" INSERT ";
  mode_fg=FG_INSERT_MODE_COLOR;
  mode_bg=BG_INSERT_MODE_COLOR;
 }
 else
 {
  mode_word=" NORMAL ";
  mode_fg=FG_NORMAL_MODE_COLOR;
  mode_bg=BG_NORMAL_MODE_COLOR;
 }

 char mode_color[16];
 int8_t mode_cmd_len=snprintf(mode_color,sizeof(mode_color),"\x1b[%d;%dm",mode_fg,mode_bg);
 int8_t mode_len=(int8_t)strlen(mode_word);

 a_buf_append(a_buffer,mode_color,mode_cmd_len);
 a_buf_append(a_buffer,mode_word,mode_len);
 a_buf_append(a_buffer,"\x1b[0m",4);

 char color_cmd[16];

 int8_t cmd_len=snprintf(color_cmd,sizeof(color_cmd),"\x1b[%d;%dm",FG_STATUS_COLOR,BG_STATUS_COLOR);

 a_buf_append(a_buffer,color_cmd,cmd_len);
 a_buf_append(a_buffer,"\x1b[K",3);
 a_buf_append(a_buffer," ",1);

 char status[256];
 char rstatus[128];

 int16_t used=mode_len+1;
 int16_t name_room=E.screen_cols-used-1-(E.dirty ? 10 : 0);

 if(name_room < 0)
 {
  name_room=0;
 }
 if(name_room > (int16_t)sizeof(status)-1)
 {
  name_room=(int16_t)sizeof(status)-1;
 }

 char* full_name=E.file_name ? E.file_name : "[No Name]";
 int32_t name_len=utf8_safe_trunc_len(full_name,name_room);

 int16_t len=snprintf(status,sizeof(status),"%.*s %s",(int)name_len,full_name,E.dirty ? "(modified)" : "");
                                                                                                           
 int16_t rlen=snprintf(rstatus,sizeof(rstatus),"%.22s u:%d/%d r:%d/%d | %d/%d | %d/%d",E.syntax ? E.syntax->file_type : "unknown",E.undo_top+1,SIZE_LIMIT,E.redo_top+1,SIZE_LIMIT,E.c_x+1,(E.c_y < E.num_rows) ? E.row[E.c_y].r_size : 0,E.c_y+1,E.num_rows);

 if(len > E.screen_cols-used)
 {
  len=E.screen_cols-used;
 }

 if(len < 0)
 {
  len=0;
 }

 a_buf_append(a_buffer,status,len);

 while(used+len < E.screen_cols)
 {
  if(E.screen_cols-used-len == rlen)
  {
   a_buf_append(a_buffer,rstatus,rlen);
   break;
  }
  else
  {
   a_buf_append(a_buffer," ",1);
   ++len;
  }
 }
 a_buf_append(a_buffer,"\x1b[0m",4);
}

void set_status_message(uint8_t color,const char* format,...)
{
 E.msg_color=color;
 va_list a_p;
 va_start(a_p,format);
 vsnprintf(E.status_msg,sizeof(E.status_msg),format,a_p);
 va_end(a_p);
 E.status_msg_time=time(NULL);
 E.num_of_status_msg_lines=1;

 uint16_t i=0;

 for(i=0;E.status_msg[i] != '\0';++i)
 {
  if(E.status_msg[i] == '\n')
  {
   ++E.num_of_status_msg_lines;
  }
 }
}

void draw_message_bar(a_buf* a_buffer)
{
 char color_cmd[16];

 int8_t cmd_len=snprintf(color_cmd,sizeof(color_cmd),"\x1b[%d;%dm",E.msg_color,BG_STATUS_COLOR);

 char* p=E.status_msg;
 uint8_t num_of_lines=0;

 while(num_of_lines < E.num_of_status_msg_lines)
 {
  a_buf_append(a_buffer,color_cmd,cmd_len);
  a_buf_append(a_buffer,"\x1b[K",3);

  char* next=strchr(p,'\n');
  uint16_t msg_len=0;

  if(next)
  {
   msg_len=next-p;
  }
  else
  {
   msg_len=(uint16_t)strlen(p);
  }

  if(msg_len > E.screen_cols)
  {
   msg_len=E.screen_cols;
  }

  a_buf_append(a_buffer,p,msg_len);
  a_buf_append(a_buffer,"\x1b[0m",4);
  a_buf_append(a_buffer,"\r\n",2);

  if(next)
  {
   p=next+1;
  }
  else
  {
   p="";
  }
  ++num_of_lines;
 }
}

void draw_external_mod_warning(a_buf* a_buffer)
{
 char color_cmd[16];

 int8_t cmd_len=snprintf(color_cmd,sizeof(color_cmd),"\x1b[%d;%dm",ERROR_MSG_COLOR,BG_STATUS_COLOR);
 char* msg="WARNING: File was modified by another program (Ctrl+s to overwrite, Ctrl+p to reload)";
 uint16_t msg_len=(uint16_t)strlen(msg);

 if(msg_len > E.screen_cols)
 {
  msg_len=E.screen_cols;
 }

 a_buf_append(a_buffer,color_cmd,cmd_len);
 a_buf_append(a_buffer,"\x1b[K",3);
 a_buf_append(a_buffer,msg,msg_len);
 a_buf_append(a_buffer,"\x1b[0m",4);
 a_buf_append(a_buffer,"\r\n",2);
}

void refresh_screen()
{
 uint8_t has_msg=(strlen(E.status_msg) > 0 && time(NULL)-E.status_msg_time < 5);

 if(has_msg)
 {
  E.screen_rows=E.term_rows-(1+E.num_of_status_msg_lines+(E.file_modified_externally ? 1 : 0));
 }
 else
 {
  E.screen_rows=E.term_rows-(1+(E.file_modified_externally ? 1 : 0));
 }

 if(E.screen_rows < 0)
 {
  E.screen_rows=1;
 }

 update_line_num_width();
 scroll();

 a_buf a_buffer={NULL,0,0};

 a_buf_append(&a_buffer,"\x1b[?25l",6);
 a_buf_append(&a_buffer,"\x1b[H",3);
 
 draw_rows(&a_buffer);

 if(E.file_modified_externally)
 {
  draw_external_mod_warning(&a_buffer);
 }

 if(has_msg)
 {
  draw_message_bar(&a_buffer);
 }

 draw_status_bar(&a_buffer);

 int32_t cursor_screen_row=0;
 int32_t r=0;

 for(r=E.row_off;r < E.c_y && r < E.num_rows;++r)
 {
  cursor_screen_row+=count_screen_rows(r);
 }

 int32_t seg_vis_start=0;
 cursor_screen_row+=get_cursor_segment_info(E.c_y,E.r_x,&seg_vis_start);

 int32_t cursor_col=0;

 if(row_should_wrap(E.c_y))
 {
  cursor_col=(E.r_x-seg_vis_start-E.seg_col_off)+E.line_num_width+1;
 }
 else
 {
  cursor_col=E.r_x-E.col_off+E.line_num_width+1;
 }

 char buffer[32];

 snprintf(buffer,sizeof(buffer),"\x1b[%d;%dH",cursor_screen_row+1,cursor_col);

 a_buf_append(&a_buffer,buffer,strlen(buffer));

 a_buf_append(&a_buffer,"\x1b[?25h",6);

 write_all(STDOUT_FILENO,a_buffer.b,a_buffer.len);

 a_buf_free(&a_buffer);
}

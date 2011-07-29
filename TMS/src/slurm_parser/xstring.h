
#ifndef _XSTRING_H
#define _XSTRING_H	1

#include "macros.h"

#define xstrcat(__p, __q)		_xstrcat(&(__p), __q)
#define xstrncat(__p, __q, __l)		_xstrncat(&(__p), __q, __l)
#define xstrcatchar(__p, __c)		_xstrcatchar(&(__p), __c)
#define xslurm_strerrorcat(__p)		_xslurm_strerrorcat(&(__p))
#define xstrftimecat(__p, __fmt)	_xstrftimecat(&(__p), __fmt)
#define xstrfmtcat(__p, __fmt, args...)	_xstrfmtcat(&(__p), __fmt, ## args)
#define xmemcat(__p, __s, __e)          _xmemcat(&(__p), __s, __e)
#define xstrsubstitute(__p, __pat, __rep) _xstrsubstitute(&(__p), __pat, __rep)

/*
** The following functions take a ptr to a string and expand the
** size of that string as needed to append the requested data.
** the macros above are provided to automatically take the
** address of the first argument, thus simplifying the interface
**
** space is allocated with xmalloc/xrealloc, so caller must use
** xfree to free.
**
*/

/*
** cat str2 onto str1, expanding str1 as necessary
*/
void _xstrcat(char **str1, const char *str2);

/*
** cat len of str2 onto str1, expanding str1 as necessary
*/
void _xstrncat(char **str1, const char *str2, size_t len);

/*
** concatenate one char, `c', onto str1, expanding str1 as needed
*/
void _xstrcatchar(char **str1, char c);

/*
** concatenate stringified errno onto str
*/
void _xslurm_strerrorcat(char **str);

/*
** concatenate current time onto str, using fmt if it is non-NUL
** see strftime(3) for the usage of the format string
*/
void _xstrftimecat(char **str, const char *fmt);

/*
** concatenate printf-style formatted string onto str
** return value is result from vsnprintf(3)
*/
int _xstrfmtcat(char **str, const char *fmt, ...)
  __attribute__ ((format (printf, 2, 3)));

/*
** concatenate range of memory from start to end (not including end)
** onto str.
*/
void _xmemcat(char **str, char *start, char *end);

/*
** strdup which uses xmalloc routines
*/
char *xstrdup(const char *str);

/*
** strdup formatted which uses xmalloc routines
*/
char *xstrdup_printf(const char *fmt, ...)
  __attribute__ ((format (printf, 1, 2)));

/*
** strndup which uses xmalloc routines
*/
char *xstrndup(const char *str, size_t n);

/*
** strtol which only reads 'n' number of chars in the str to get the number
*/
long int xstrntol(const char *str, char **endptr, size_t n, int base);

/*
** replacement for libc basename
*/
char *xbasename(char *path);

/*
** Find the first instance of a sub-string "pattern" in the string "str",
** and replace it with the string "replacement".
*/
void _xstrsubstitute(char **str, const char *pattern, const char *replacement);

/*
 * Remove all quotes that surround a string in the string "str",
 *   str (IN)	        target string (pointer to in case of expansion)
 *   increased (IN/OUT)	current position in "str"
 *   RET char *         str returned without quotes in it. needs to be xfreed
 */
char *xstrstrip(char *str);

/* xshort_hostname
 *   Returns an xmalloc'd string containing the hostname
 *   of the local machine.  The hostname contains only
 *   the short version of the hostname (e.g. "linux123.foo.bar"
 *   becomes "linux123")
 *
 *   Returns NULL on error.
 */
char *xshort_hostname(void);

/*
 * Return true if all characters in a string are whitespace characters,
 * otherwise return false.  ("str" must be terminated by a null character)
 */
bool xstring_is_whitespace(const char *str);

/*
 * If str make everything lowercase.  Should not be called on static char *'s
 * Returns the lowered string which is the same pointer that is sent in.
 */
char *xstrtolower(char *str);

#endif /* !_XSTRING_H */
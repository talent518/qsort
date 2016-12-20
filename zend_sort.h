/*
   +----------------------------------------------------------------------+
   | Zend Engine                                                          |
   +----------------------------------------------------------------------+
   | Copyright (c) 1998-2016 Zend Technologies Ltd. (http://www.zend.com) |
   +----------------------------------------------------------------------+
   | This source file is subject to version 2.00 of the Zend license,     |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.zend.com/license/2_00.txt.                                |
   | If you did not receive a copy of the Zend license and are unable to  |
   | obtain it through the world-wide-web, please send a note to          |
   | license@zend.com so we can mail you a copy immediately.              |
   +----------------------------------------------------------------------+
   | Authors: Xinchen Hui <laruence@php.net>                              |
   |          Sterling Hughes <sterling@php.net>                          |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef ZEND_SORT_H
#define ZEND_SORT_H

#define ZEND_API

#if defined(__x86_64__) || defined(__LP64__) || defined(_LP64) || defined(_WIN64)
# define Z_L(val) val##LL
#else
# define Z_L(val) val##I
#endif

#ifdef __builtin_expect
# define EXPECTED(condition)   __builtin_expect(!!(condition), 1)
# define UNEXPECTED(condition) __builtin_expect(!!(condition), 0)
#else
# define EXPECTED(condition)   (condition)
# define UNEXPECTED(condition) (condition)
#endif

typedef void (*swap_func_t)(void *, void *);
typedef int  (*compare_func_t)(const void *, const void *);
ZEND_API void zend_qsort(void *base, size_t nmemb, size_t siz, compare_func_t cmp, swap_func_t swp);
ZEND_API void zend_sort(void *base, size_t nmemb, size_t siz, compare_func_t cmp, swap_func_t swp);
ZEND_API void zend_insert_sort(void *base, size_t nmemb, size_t siz, compare_func_t cmp, swap_func_t swp);

#endif       /* ZEND_SORT_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */

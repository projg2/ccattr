/* Portable wrappers around CC extended attributes
 * (c) 2011 Michał Górny
 * 2-clause BSD-licensed
 */

#pragma once
#ifndef _CCATTR_H
#define _CCATTR_H

#ifdef __has_attribute /* clang */
#	if __has_attribute(constant) /* XXX: we can't use const... */
#		define _CCATTR_HAVE_CONST
#	endif
#	if __has_attribute(noreturn)
#		define _CCATTR_HAVE_NORETURN
#	endif
#	if __has_attribute(returns_twice)
#		define _CCATTR_HAVE_RETURNS_TWICE
#	endif
#	if __has_attribute(unused)
#		define _CCATTR_HAVE_UNUSED
#	endif
#	if __has_attribute(used)
#		define _CCATTR_HAVE_USED
#	endif
#	if __has_attribute(pure)
#		define _CCATTR_HAVE_PURE
#	endif
#	if __has_attribute(malloc)
#		define _CCATTR_HAVE_MALLOC
#	endif
#	if __has_attribute(warn_unused_result)
#		define _CCATTR_HAVE_WARN_UNUSED_RESULT
#	endif
#	if __has_attribute(sentinel)
#		define _CCATTR_HAVE_SENTINEL
#	endif
#	if __has_attribute(format)
#		define _CCATTR_HAVE_FORMAT
#	endif
#	if __has_attribute(format_arg)
#		define _CCATTR_HAVE_FORMAT_ARG
#	endif
#	if __has_attribute(alloc_size)
#		define _CCATTR_HAVE_ALLOC_SIZE
#	endif
#else /* !__has_attribute -- gcc */
#	if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 5)
#		define _CCATTR_HAVE_CONST
#		define _CCATTR_HAVE_NORETURN
#		define _CCATTR_HAVE_RETURNS_TWICE /* XXX: check version */
#		define _CCATTR_HAVE_UNUSED
#		define _CCATTR_HAVE_USED
#		define _CCATTR_HAVE_FORMAT
#		define _CCATTR_HAVE_FORMAT_ARG
#	endif
#	if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 96)
#		define _CCATTR_HAVE_PURE
#		define _CCATTR_HAVE_MALLOC
#	endif
#	if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#		define _CCATTR_HAVE_WARN_UNUSED_RESULT
#	endif
#	if __GNUC__ >= 4
#		define _CCATTR_HAVE_SENTINEL
#	endif
#	if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
#		define _CCATTR_HAVE_ALLOC_SIZE
#	endif
#endif /* __has_attribute */

/**
 * SECTION: function-results
 * @short_description: macros to declare function result types
 * @include: ccattr.h
 *
 * Macros which declare specific function results and effects.
 */

/**
 * CCATTR_CONST
 *
 * Declare a function as `const'. This means that the function does not examine
 * any values except its parameters and has no effects except its return value.
 *
 * Const function must not access memory referenced by its arguments as well.
 * It must not call non-const functions (including malloc()).
 */
#ifdef _CCATTR_HAVE_CONST
#	define CCATTR_CONST __attribute__((const))
#else
#	define CCATTR_CONST
#endif

/**
 * CCATTR_PURE
 *
 * Declare a function as `pure'. This means that the function does not examine
 * any values except its parameters and global variables, and has no effects
 * except its return value.
 */
#ifdef _CCATTR_HAVE_PURE
#	define CCATTR_PURE __attribute__((pure))
#else
#	define CCATTR_PURE
#endif

/**
 * CCATTR_MALLOC
 *
 * Declare a function as `malloc'. This means that the function always returns
 * a pointer to memory which is guaranteed not to alias (IOW, a newly-allocated
 * memory) or %NULL.
 */
#ifdef _CCATTR_HAVE_MALLOC
#	define CCATTR_MALLOC __attribute__((malloc))
#else
#	define CCATTR_MALLOC
#endif

/**
 * CCATTR_WARN_UNUSED_RESULT
 *
 * Declare a function as `warn_unused_result'. This means that the compiler will
 * warn whenever the function result is not used.
 */
#ifdef _CCATTR_HAVE_WARN_UNUSED_RESULT
#	define CCATTR_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
#	define CCATTR_WARN_UNUSED_RESULT
#endif

/**
 * CCATTR_NORETURN
 *
 * Declare a function as `return'. This means that the function does not ever
 * return (e.g. uses exit(), exec*() or a similar function).
 */
#ifdef _CCATTR_HAVE_NORETURN
#	define CCATTR_NORETURN __attribute__((noreturn))
#else
#	define CCATTR_NORETURN
#endif

/**
 * CCATTR_RETURNS_TWICE
 *
 * Declare a function as `returns_twice'. This means that the function may
 * return more than once, e.g. setjmp(), fork().
 */
#ifdef _CCATTR_HAVE_RETURNS_TWICE
#	define CCATTR_RETURNS_TWICE __attribute__((returns_twice))
#else
#	define CCATTR_RETURNS_TWICE
#endif

/**
 * CCATTR_UNUSED
 *
 * Declare a function as `unused'. This means that the function may not be used
 * at all and compiler should not warn about it.
 */
#ifdef _CCATTR_HAVE_UNUSED
#	define CCATTR_UNUSED __attribute__((unused))
#else
#	define CCATTR_UNUSED
#endif

/**
 * CCATTR_USED
 *
 * Declare a function as `used'. This means that the function code must be
 * generated even if it appears to be unused.
 */
#ifdef _CCATTR_HAVE_USED
#	define CCATTR_USED __attribute__((used))
#else
#	define CCATTR_USED
#endif

/**
 * SECTION: function-params
 * @short_description: macros to declare function parameter types
 * @include: ccattr.h
 *
 * Macros which declare functions as taking specific parameters.
 */

/**
 * CCATTR_SENTINEL
 *
 * Declare a variadic function as `sentinel'. This means that the variadic
 * argument list must be terminated with an explicit %NULL.
 */
#ifdef _CCATTR_HAVE_SENTINEL
#	define CCATTR_SENTINEL __attribute__((sentinel))
#else
#	define CCATTR_SENTINEL
#endif

/**
 * CCATTR_PRINTF
 * @fstr_idx: index of format string argument
 * @args_idx: index of first variadic argument
 *
 * Declare a variadic function taking arguments similar to printf().
 * The format string is passed to the function as @fstr_idx-th argument,
 * and the variadic arguments start at @args_idx.
 */
#ifdef _CCATTR_HAVE_FORMAT
#	define CCATTR_PRINTF(fstr_idx, args_idx) \
		__attribute__((format(printf, fstr_idx, args_idx)))
#else
#	define CCATTR_PRINTF(fstr_idx, args_idx)
#endif

/**
 * CCATTR_SCANF
 * @fstr_idx: index of format string argument
 * @args_idx: index of first variadic argument
 *
 * Declare a variadic function taking arguments similar to scanf().
 * The format string is passed to the function as @fstr_idx-th argument,
 * and the variadic arguments start at @args_idx.
 */
#ifdef _CCATTR_HAVE_FORMAT
#	define CCATTR_SCANF(fstr_idx, args_idx) \
		__attribute__((format(scanf, fstr_idx, args_idx)))
#else
#	define CCATTR_SCANF(fstr_idx, args_idx)
#endif

/**
 * CCATTR_STRFTIME
 * @fstr_idx: index of format string argument
 *
 * Declare a variadic function taking arguments similar to strftime().
 * The format string is passed to the function as @fstr_idx-th argument.
 */
#ifdef _CCATTR_HAVE_FORMAT
#	define CCATTR_STRFTIME(fstr_idx) \
		__attribute__((format(strftime, fstr_idx, 0)))
#else
#	define CCATTR_STRFTIME(fstr_idx)
#endif

/**
 * CCATTR_STRFMON
 * @fstr_idx: index of format string argument
 * @args_idx: index of first variadic argument
 *
 * Declare a variadic function taking arguments similar to strfmon().
 * The format string is passed to the function as @fstr_idx-th argument,
 * and the variadic arguments start at @args_idx.
 */
#ifdef _CCATTR_HAVE_FORMAT
#	define CCATTR_STRFMON(fstr_idx, args_idx) \
		__attribute__((format(strfmon, fstr_idx, args_idx)))
#else
#	define CCATTR_STRFMON(fstr_idx, args_idx)
#endif

/**
 * CCATTR_FORMAT_ARG
 * @fstr_idx: index of format string argument
 *
 * Declare a variadic function possibly taking a format string argument
 * and returning a modified variant of it. Thus, the checks on format string
 * will be performed on arguments of the function to which result will
 * be passed.
 *
 * Used on gettext(), for example.
 */
#ifdef _CCATTR_HAVE_FORMAT_ARG
#	define CCATTR_FORMAT_ARG(fstr_idx) \
		__attribute__((format_arg(fstr_idx)))
#else
#	define CCATTR_FORMAT_ARG(fstr_idx)
#endif

/**
 * CCATTR_ALLOC_SIZE
 * @size_idx: index of size argument
 *
 * Declare a function returning memory block of size passed as an argument
 * at index @size_idx.
 */
#ifdef _CCATTR_HAVE_ALLOC_SIZE
#	define CCATTR_ALLOC_SIZE(size_idx) \
		__attribute__((alloc_size(size_idx)))
#else
#	define CCATTR_ALLOC_SIZE(size_idx)
#endif

/**
 * CCATTR_ALLOC_SIZE2
 * @nmemb_idx: index of nmemb argument
 * @size_idx: index of size argument
 *
 * Declare a function returning memory block of size being the product
 * of arguments passed at indexes @nmemb_idx and @size_idx (like with calloc()).
 */
#ifdef _CCATTR_HAVE_ALLOC_SIZE
#	define CCATTR_ALLOC_SIZE2(nmemb_idx, size_idx) \
		__attribute__((alloc_size(nmemb_idx, size_idx)))
#else
#	define CCATTR_ALLOC_SIZE2(nmemb_idx, size_idx)
#endif

#endif /*_CCATTR_H*/
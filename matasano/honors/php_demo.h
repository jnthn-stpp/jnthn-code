/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.11
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */

#ifndef PHP_DEMO_H
#define PHP_DEMO_H

extern zend_module_entry demo_module_entry;
#define phpext_demo_ptr &demo_module_entry

#ifdef PHP_WIN32
# define PHP_DEMO_API __declspec(dllexport)
#else
# define PHP_DEMO_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(demo);
PHP_MSHUTDOWN_FUNCTION(demo);
PHP_RINIT_FUNCTION(demo);
PHP_RSHUTDOWN_FUNCTION(demo);
PHP_MINFO_FUNCTION(demo);

ZEND_NAMED_FUNCTION(_wrap_demo_aes_e);
ZEND_NAMED_FUNCTION(_wrap_demo_aes_d);
ZEND_NAMED_FUNCTION(_wrap_demo_sha3_224);
ZEND_NAMED_FUNCTION(_wrap_demo_sha3_256);
ZEND_NAMED_FUNCTION(_wrap_demo_sha3_384);
ZEND_NAMED_FUNCTION(_wrap_demo_sha3_512);
ZEND_NAMED_FUNCTION(_wrap_demo_counter);
#endif /* PHP_DEMO_H */

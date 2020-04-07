

#ifndef TEABOT7_H
#define TEABOT7_H
    #define TEABOT_VERSION "7.4"

    #include "php.h"
    #include "teabot_struct.h"
    #include <pthread.h>

    #ifdef HAVE_CONFIG_H
        #include "config.h"
    #endif

    #ifdef ZTS
        #include "TSRM.h"
    #endif

    PHP_INI_BEGIN()
    PHP_INI_END()

    #ifndef TEABOT_MAIN
        extern zend_module_entry teabot7_module_entry;
    #endif

    ZEND_BEGIN_MODULE_GLOBALS(teabot7)
    ZEND_END_MODULE_GLOBALS(teabot7)
    ZEND_EXTERN_MODULE_GLOBALS(teabot7)
    #define TEABOTG(v) ZEND_MODULE_GLOBALS_ACCESSOR(teabot7, v)


    #if defined(ZTS) && defined(COMPILE_DL_SAMPLE)
        ZEND_TSRMLS_CACHE_EXTERN()
    #endif

    #define phpext_teabot7_ptr &teabot7_module_entry
#endif

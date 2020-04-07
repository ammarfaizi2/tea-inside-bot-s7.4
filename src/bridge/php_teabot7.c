
/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */
#define TEABOT_MAIN
#include "php_teabot7.h"
#ifdef COMPILE_DL_TEABOT7
    #ifdef ZTS
        ZEND_TSRMLS_CACHE_DEFINE()
    #endif
#endif

ZEND_DECLARE_MODULE_GLOBALS(teabot7);

extern zend_class_entry *teabot_daemon_ce;
extern const zend_function_entry teabot_daemon_class_methods[];

/**
 * Init.
 */
static PHP_MINIT_FUNCTION(teabot7)
{
    zend_class_entry ce0;

    INIT_NS_CLASS_ENTRY(ce0, "TeaBot", "Daemon", teabot_daemon_class_methods);
    teabot_daemon_ce = zend_register_internal_class(&ce0 TSRMLS_CC);

    REGISTER_INI_ENTRIES();

    return SUCCESS;
}

/**
 * Shutdown.
 */
static PHP_MSHUTDOWN_FUNCTION(teabot7)
{
    UNREGISTER_INI_ENTRIES();
    return SUCCESS;
}

/**
 * Global init.
 */
static PHP_GINIT_FUNCTION(teabot7)
{
    #if defined(COMPILE_DL_ASTKIT) && defined(ZTS)
        ZEND_TSRMLS_CACHE_UPDATE();
    #endif
}

zend_module_entry teabot7_module_entry = {
    STANDARD_MODULE_HEADER,
    "teabot7",
    NULL, /* functions */
    PHP_MINIT(teabot7),
    PHP_MSHUTDOWN(teabot7),
    NULL, /* RINIT */
    NULL, /* RSHUTDOWN */
    NULL, /* MINFO */
    TEABOT_VERSION,
    PHP_MODULE_GLOBALS(teabot7),
    PHP_GINIT(teabot7),
    NULL, /* GSHUTDOWN */
    NULL, /* RPOSTSHUTDOWN */
    STANDARD_MODULE_PROPERTIES_EX
};
ZEND_GET_MODULE(teabot7);

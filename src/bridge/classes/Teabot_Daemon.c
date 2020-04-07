
#include <stdio.h>
#include <stdlib.h>
#include "../php_teabot7.h"

teabot_struct teabot;
zend_class_entry *teabot_daemon_ce;
void init_daemon(char *);

/**
 * @param string $token
 *
 * Constructor.
 */
PHP_METHOD(TeaBot_Daemon, __construct)
{
	size_t token_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(teabot.token, token_len)
    ZEND_PARSE_PARAMETERS_END();

    zend_update_property_stringl(teabot_daemon_ce, getThis(), ZEND_STRL("token"),
        teabot.token, token_len TSRMLS_CC);
}

PHP_METHOD(TeaBot_Daemon, passPayload)
{
    size_t payload_len;
    char *pstr, *payload_str;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(payload_str, payload_len)
    ZEND_PARSE_PARAMETERS_END();

    pstr = (char *)malloc(payload_len + 1);
    strcpy(pstr, payload_str);
    init_daemon(pstr);
}

const zend_function_entry teabot_daemon_class_methods[] = {
    PHP_ME(TeaBot_Daemon, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(TeaBot_Daemon, passPayload, NULL, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

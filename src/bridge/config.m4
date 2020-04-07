dnl config.m4
PHP_ARG_ENABLE(teabot7, for teabot7 support,
[  --enable-teabot7            Include teabot7 support])

if test "$PHP_TEABOT7" != "no"; then
  PHP_NEW_EXTENSION(teabot7, php_teabot7.c classes/Teabot_Daemon.c, $ext_shared,, "-Wall -lpthread")
  PHP_SUBST(TEABOT7_SHARED_LIBADD)
fi

make;
cc -shared  .libs/php_teabot7.o classes/.libs/Teabot_Daemon.o \
-Wl,-soname \
-Wl,teabot7.so \
-o .libs/teabot7.so \
-Wl,-rpath=$(pwd)/../core -L$(pwd)/../core -lteabot7


BASEDIR = /home/ammarfaizi2/project/now/bot-s7.4/src/core
LIB_SHARED_BIN = libteabot7.so
COMPILER = g++
LINKER = g++
LIBS = -lpthread -lcurl `pcre2-config --libs8`
STD_FLAGS = -std=c++17 -Wall
CONSTANTS = -DTEA_INSIDE_BOT_VERSION=7.4

INCLUDE = -I${BASEDIR}/include/ -I${BASEDIR}/src/third_party `pcre2-config --cflags`
SOURCE_DIR = src/
ROOT_DEPDIR = .deps

ifeq (${RELEASE_MODE},1)
	LINKER_FLAGS = -fPIC -Wl,-R -Wl,${BASEDIR} ${INCLUDE} ${STD_FLAGS} -fno-stack-protector -Ofast ${CONSTANTS} -s
	COMPILER_FLAGS = -fPIC ${INCLUDE} ${STD_FLAGS} -fno-stack-protector -Ofast ${CONSTANTS} -s -c
else
	LINKER_FLAGS = -fPIC -Wl,-R -Wl,${BASEDIR} ${INCLUDE} ${STD_FLAGS} -fstack-protector-strong -ggdb3 -O0 -DICETEA_DEBUG ${CONSTANTS}
	COMPILER_FLAGS = -fPIC ${INCLUDE} ${STD_FLAGS} -fstack-protector-strong -ggdb3 -O0 -DICETEA_DEBUG ${CONSTANTS} -c
endif

SOURCES  = $(shell find ${SOURCE_DIR} -name '*.c')
SOURCES += $(shell find ${SOURCE_DIR} -name '*.cpp')
SOURCES += $(shell find ${SOURCE_DIR} -name '*.S')

OBJECTS = $(SOURCES:%=%.o)
SOURCES_DIR = $(shell find ${SOURCE_DIR} -type d)

DEPDIR = ${SOURCES_DIR:%=${ROOT_DEPDIR}/%}
DEPFLAGS = -MT $@ -MMD -MP -MF ${ROOT_DEPDIR}/$*.d
DEPFILES = ${SOURCES:%=${ROOT_DEPDIR}/%.d}

all: ${LIB_SHARED_BIN}

${ROOT_DEPDIR}:
	mkdir -p $@

${DEPDIR}: | ${ROOT_DEPDIR}
	mkdir -p $@

${OBJECTS}: | ${DEPDIR}
	${COMPILER} ${DEPFLAGS} ${COMPILER_FLAGS} -o $@ ${@:%.o=%}

${LIB_SHARED_BIN}: ${OBJECTS}
	${LINKER} -shared ${LINKER_FLAGS} -o ${LIB_SHARED_BIN} ${OBJECTS} ${LIBS}

-include ${DEPFILES}

clean:
	rm -rfv ${DEPFILES} ${OBJECTS} ${MAIN_BIN} ${LIB_SHARED_BIN}

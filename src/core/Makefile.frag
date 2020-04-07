
BASEDIR = ~$$BASEDIR$$~
MAIN_BIN = icetea
LIB_SHARED_BIN = libicetea-s7.so
COMPILER = g++
LINKER = g++
LIBS = -lpthread
STD_FLAGS = -std=c++17 -Wall
CONSTANTS = -DTEA_INSIDE_BOT_VERSION=7.0

INCLUDE = -I${BASEDIR}/include/ -I${BASEDIR}/src/third_party
SOURCE_DIR = src/
ROOT_DEPDIR = .deps

ifeq (${RELEASE_MODE},1)
	LINKER_FLAGS = -Wl,-R -Wl,${BASEDIR} ${INCLUDE} ${STD_FLAGS} -fno-stack-protector -Ofast ${CONSTANTS}
	COMPILER_FLAGS = ${INCLUDE} ${STD_FLAGS} -fno-stack-protector -Ofast ${CONSTANTS} -c
else
	LINKER_FLAGS = -Wl,-R -Wl,${BASEDIR} ${INCLUDE} ${STD_FLAGS} -fstack-protector-strong -ggdb3 -O0 -DICETEA_DEBUG ${CONSTANTS}
	COMPILER_FLAGS = ${INCLUDE} ${STD_FLAGS} -fstack-protector-strong -ggdb3 -O0 -DICETEA_DEBUG ${CONSTANTS} -c
endif

SOURCES  = $(shell find ${SOURCE_DIR} -name '*.c')
SOURCES += $(shell find ${SOURCE_DIR} -name '*.cpp')
SOURCES += $(shell find ${SOURCE_DIR} -name '*.S')

OBJECTS = $(SOURCES:%=%.o)
SOURCES_DIR = $(shell find ${SOURCE_DIR} -type d)

DEPDIR = ${SOURCES_DIR:%=${ROOT_DEPDIR}/%}
DEPFLAGS = -MT $@ -MMD -MP -MF ${ROOT_DEPDIR}/$*.d
DEPFILES = ${SOURCES:%=${ROOT_DEPDIR}/%.d}

all: ${MAIN_BIN}

${ROOT_DEPDIR}:
	mkdir -p $@

${DEPDIR}: | ${ROOT_DEPDIR}
	mkdir -p $@

${OBJECTS}: | ${DEPDIR}
	${COMPILER} ${DEPFLAGS} ${COMPILER_FLAGS} -o $@ ${@:%.o=%}

${LIB_SHARED_BIN}: ${OBJECTS}
	${LINKER} -shared ${LINKER_FLAGS} -o ${LIB_SHARED_BIN} ${OBJECTS}

${MAIN_BIN}: ${LIB_SHARED_BIN}
	${LINKER} ${LINKER_FLAGS} -o ${MAIN_BIN} main.cpp -licetea-s7 -L${BASEDIR}

-include ${DEPFILES}

clean:
	rm -rfv ${DEPFILES} ${OBJECTS} ${MAIN_BIN} ${LIB_SHARED_BIN}

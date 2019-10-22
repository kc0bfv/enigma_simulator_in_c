DEBUG := -DDEBUG
C_FLAGS := -Wall -Werror -static # ${DEBUG}
OBJECTS := main.o plugboard.o reflector.o rotor.o utils.o
ARCHES_SUPPORTED := x64 aarch64 x86 armel powerpc
ARCH := x64

all: enigma.${ARCH}

%.x64: CC=gcc
%.aarch64: CC=aarch64-linux-gnu-gcc
%.armel: CC=arm-linux-gnueabi-gcc
%.x86: CC=i686-linux-gnu-gcc
%.powerpc: CC=powerpc-linux-gnu-gcc

enigma.%: ${OBJECTS}
	${CC} ${C_FLAGS} -o $@ $^

%.o: %.c
	${CC} ${C_FLAGS} -c -o $@ $<

.PHONY: clean clean_all
clean:
	rm -f ${OBJECTS}
clean_all: clean
	rm -f $(patsubst %, enigma.%, ${ARCHES_SUPPORTED})

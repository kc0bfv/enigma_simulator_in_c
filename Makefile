DEBUG := -DDEBUG
C_FLAGS := -Wall -Werror # -static # ${DEBUG}
OBJECTS := main.o plugboard.o reflector.o rotor.o utils.o

all: enigma.x64

enigma.x64: ${OBJECTS}
	${CC} ${C_FLAGS} -o $@ $^

%.o: %.c
	${CC} ${C_FLAGS} -c -o $@ $<

.PHONY: clean
clean:
	rm enigma ${OBJECTS}

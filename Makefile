TARGET = game_of_life_sim
STD_LIBS = -lm
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Wformat -ggdb3 -O3
LFLAGS = -pedantic -Wall -Wextra 
CFLAGS_STRICT = -std=c99 -Wall -pedantic -ggdb3 \
-pedantic-errors -Wextra -Waggregate-return -Wcast-align \
-Wcast-qual -Wconversion \
-Wdisabled-optimization \
-Werror -Wfloat-equal -Wformat=2 \
-Wformat-nonliteral -Wformat-security  \
-Wformat-y2k \
-Wimplicit  -Wimport  -Winit-self  -Winline \
-Winvalid-pch   \
-Wlong-long \
-Wmissing-field-initializers -Wmissing-format-attribute   \
-Wmissing-include-dirs -Wmissing-noreturn \
-Wpacked  -Wpadded -Wpointer-arith \
-Wredundant-decls \
-Wshadow -Wstack-protector \
-Wstrict-aliasing=2 -Wswitch-default \
-Wswitch-enum \
-Wunreachable-code -Wunused \
-Wunused-parameter \
-Wvariadic-macros \
-Wwrite-strings

.PHONY: clean all default $(TARGET)

default: $(TARGET)
all: default

BASE_FILES = $(wildcard *.c)
SRC_FILES = $(wildcard src/*.c)

SRC_H_FILES = $(wildcard inc/*.h)


OBJECTS = $(patsubst %.c, %.o, $(BASE_FILES) $(SRC_FILES))
HEADERS = $(BASE_H_FILES) $(SRC_H_FILES)

# Compile
%.o: %.c $(HEADERS)
	@echo Compiling: $< ...
	$(CC) $(CFLAGS) -c $< -o $@

#.PRECIOUS: $(TARGET) $(OBJECTS)

#Link
$(TARGET): $(OBJECTS)
	@echo Linking files: $(OBJECTS) ...
	$(CC) $(OBJECTS) -o $@
	@echo Deleting .o files ...
	-rm -f $(OBJECTS)
	@echo Done

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)
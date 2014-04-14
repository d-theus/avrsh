SRC=main.c\
    lexer.c\
    parser.c\
    printer.c\
    avrsh.c
TARGET=avrsh
LDFLAGS=
CFLAGS=

ifeq ($(DEBUG),1)
	CFLAGS += -g
else
	CFLAGS +=
endif

CC=gcc

all:$(TARGET)

re:clean all

%.o: %.c
	$(CC) $(CFLAGS) $? -c

$(TARGET):$(SRC:.c=.o)
	$(CC) $(LDFLAGS) $? -o $@

.PHONY: clean

clean:
	rm -f *.o
	rm -f $(TARGET)

test:
	./test.sh

launch: test

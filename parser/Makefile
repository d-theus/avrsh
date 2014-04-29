SRC= lexer.c\
    parser.c\
    printer.c\
    main.c\
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

.PHONY: clean test

clean:
	rm -f *.o
	rm -f $(TARGET)

test: re\
	test_1_1\
	test_2_1\
	test_2_2\
	test_3_1\
	test_3_2\
	test_3_3\
	test_3_4\
	test_3_5\
	test_4_1\
	test_4_2\
	test_4_3\
	test_4_4\
	test_4_5

#1{{{
test_1_1: main_1_1.c $(SRC:.c=.o)
	$(CC) -c $(CFLAGS) $<
	$(CC) $(LDFLAGS) $(shell echo $(?:.c=.o) | sed 's/main.o//g') -o test/tc_1_1_bin
	@echo 
	@echo "#### TEST CASE 1.1 ####"
	test/tc_1_1.sh
	@echo "#######################"
	@echo 
#}}}	

#2{{{
test_2_1: $(SRC:.c=.o)
	@echo 
	@echo "#### TEST CASE 2.1 ####"
	test/tc_2_1.sh
	@echo "#######################"
	@echo 

test_2_2: $(SRC:.c=.o)
	@echo 
	@echo "#### TEST CASE 2.2 ####"
	test/tc_2_2.sh
	@echo "#######################"
	@echo 

#}}}

#3{{{
test_3_1: $(SRC:.c=.o)
	@echo 
	@echo "#### TEST CASE 3.1 ####"
	test/tc_3_1.sh
	@echo 

test_3_2: $(SRC:.c=.o)
	@echo 
	@echo "#### TEST CASE 3.2 ####"
	test/tc_3_2.sh
	@echo "#######################"
	@echo 

test_3_3: $(SRC:.c=.o)
	@echo 
	@echo "#### TEST CASE 3.3 ####"
	test/tc_3_3.sh
	@echo "#######################"
	@echo 

test_3_4: $(SRC:.c=.o)
	@echo 
	@echo "#### TEST CASE 3.4 ####"
	test/tc_3_4.sh
	@echo "#######################"
	@echo 

test_3_5: $(SRC:.c=.o)
	@echo 
	@echo "#### TEST CASE 3.5 ####"
	test/tc_3_5.sh
	@echo "#######################"
	@echo 
#}}}

#4{{{
test_4_1: main_4_1.c $(SRC:.c=.o)
	$(CC) -c $(CFLAGS) $<
	$(CC) $(LDFLAGS) $(shell echo $(?:.c=.o) | sed 's/main.o//g') -o test/tc_4_1_bin
	@echo 
	@echo "#### TEST CASE 4.1 ####"
	test/tc_4_1.sh
	@echo "#######################"
	@echo 

test_4_2: $(SRC:.c=.o)
	@echo 
	@echo "#### TEST CASE 4.2 ####"
	test/tc_4_2.sh
	@echo "#######################"
	@echo 

test_4_3: $(SRC:.c=.o)
	@echo 
	@echo "#### TEST CASE 4.3 ####"
	test/tc_4_3.sh
	@echo "#######################"
	@echo 

test_4_4:main_4_4.c $(SRC:.c=.o)
	$(CC) -c $(CFLAGS) $<
	$(CC) $(LDFLAGS) $(shell echo $(?:.c=.o) | sed 's/main.o//g') -o test/tc_4_4_bin
	@echo 
	@echo "#### TEST CASE 4.4 ####"
	test/tc_4_4.sh
	@echo "#######################"
	@echo 

test_4_5: $(SRC:.c=.o)
	@echo 
	@echo "#### TEST CASE 4.5 ####"
	test/tc_4_5.sh
	@echo "#######################"
	@echo 

#}}}

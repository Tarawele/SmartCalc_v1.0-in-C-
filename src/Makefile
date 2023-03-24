SRCS = s21_polish.c s21_helpers_polish.c s21_stack.c
	
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LINUX_FLAGS= -lm -lsubunit -lrt 
OS:=$(shell uname -s)

all: s21_smartcalc

s21_polish.a: ${SRCS}
	@${CC} ${CFLAGS} -c ${SRCS} -lm 
	@ar rcs s21_polish.a ${OBJS}
	@ranlib s21_polish.a

tests:	s21_polish.a
ifeq ($(OS), Darwin)
	@${CC} ${CFLAGS} -c s21_polish_tests.c
	@${CC} s21_polish_tests.o s21_polish.a -o test -lcheck 
else
	@${CC} ${CFLAGS} -c s21_polish_tests.c $(LINUX_FLAGS) 
	@${CC} s21_polish_tests.o s21_polish.a -o test -lcheck  $(LINUX_FLAGS) 
endif
	./test

gcov_report:	s21_polish.a
ifeq ($(OS), Darwin)
	@gcc --coverage s21_polish_tests.c -lcheck ${SRCS} -o unit-test 
else
	@gcc --coverage s21_polish_tests.c ${SRCS} -o unit-test -lcheck $(LINUX_FLAGS) 
endif
	@./unit-test
	@lcov -t "test" -o test.info -c -d .
	@genhtml -o report test.info
	
clean:
	@/bin/rm -rf *.o *.a *.log *.aux *.pdf *.tar test unit-test *.gcno *gcda report *.info leak_check s21_SmartCalc

dvi:
	open readme/index.html

dist:
	tar -cf s21_SmartCalc_v1.0.tar *.c *.h Makefile readme ui

checks: cppcheck style leaks

style:
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem . *.c

leaks:
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test ./s21_SmartCalc
else
	G_SLICE=debug-blocks valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test ./s21_SmartCalc $(LINUX_FLAGS) 
endif

s21_smartcalc: s21_polish.a s21_SmartCalc_v1_0.c
ifeq ($(OS), Darwin)
	$(CC) `pkg-config --cflags gtk4` -DGDK_VERSION_MIN_REQUIRED=GDK_VERSION_4_2 s21_SmartCalc_v1_0.c s21_helpers_polish.c s21_polish.c s21_stack.c -o s21_SmartCalc `pkg-config --libs gtk4`
else
	$(CC) `pkg-config --cflags gtk4` -DGDK_VERSION_MIN_REQUIRED=GDK_VERSION_4_2 s21_SmartCalc_v1_0.c s21_helpers_polish.c s21_polish.c s21_stack.c -o s21_SmartCalc `pkg-config --libs gtk4` $(LINUX_FLAGS)
endif

run: s21_smartcalc
	./s21_SmartCalc
install: uninstall s21_smartcalc
	@mkdir ~/SmartCalc_mskyler_v1.0
	@install ./s21_SmartCalc ~/SmartCalc_mskyler_v1.0/
	@make clean

uninstall:
	@rm -rf ~/SmartCalc_mskyler_v1.0
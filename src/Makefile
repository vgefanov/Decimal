CC = gcc
CFLAGS =-Wall -Wextra -Werror -std=c11 -lm
CFLAGS_GCOV =-fprofile-arcs -ftest-coverage
CFLAGS_TEST =-Wall -Wextra -Werror -std=c11 -lm -lcheck -lpthread


SOURCES = s21_decimal.c
SOURCES_TEST = s21_decimal_test.c


BUILD_DIR = .
OUTFILE_TEST = s21_decimal_test


all: s21_string.a


clean:
	rm -rf ./lcov_report
	rm *.o *.a *.gcno *.gcda *.gcov *.info $(BUILD_DIR)/$(OUTFILE_TEST)


test:
	$(CC) $(CFLAGS_TEST) $(SOURCES) $(SOURCES_TEST) -o $(BUILD_DIR)/$(OUTFILE_TEST)
	$(BUILD_DIR)/$(OUTFILE_TEST)


s21_decimal.a:
	$(CC) $(CFLAGS) -c $(SOURCES) -o s21_decimal.o
	ar rc s21_decimal.a s21_decimal.o


gcov_report:
	$(CC) $(CFLAGS_TEST) $(CFLAGS_GCOV) $(SOURCES) $(SOURCES_TEST) -o $(BUILD_DIR)/$(OUTFILE_TEST)
	$(BUILD_DIR)/$(OUTFILE_TEST)
	gcov s21_decimal
	gcov -f s21_decimal.gcda


lcov_report:
	lcov --capture --directory . --output-file main_coverage.info
	genhtml main_coverage.info --output-directory lcov_report


check_all: style check leaks


style:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h


check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h


leaks: test
	CK_FORK=no leaks --atExit -- $(BUILD_DIR)/$(OUTFILE_TEST)


# service


brew:
	# cd ~/goinfre
	# git clone https://github.com/Homebrew/brew homebrew
	eval "$(~/goinfre/homebrew/bin/brew shellenv)"


lcov:
	brew install lcov


valgrind_install:
	brew tap LouisBrunner/valgrind
	brew install --HEAD LouisBrunner/valgrind/valgrind


valgrind:
	valgrind $(OUTFILE_TEST) --leak-check=full
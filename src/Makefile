GCOV_FLALG=
CHECK_FLAGS=
GENERATE_HTML=

TESTS_C=unit_tests.c

TESTS_C_EXCLUDE := $(addprefix -e ,$(TESTS_C))

OS := $(shell uname -s)
ifeq ($(OS),Linux)
	GCOV_FLAG = gcovr -r . $(TESTS_C_EXCLUDE) --html-details -o report.html
	CHECK_FLAGS= -lcheck -lm -lpthread -lrt --coverage -lsubunit
endif
ifeq ($(OS),Darwin)
    OS_VERS := $(shell sw_vers -productVersion)
    ifeq ($(findstring 11.,$(OS_VERS)),)
		GCOV_FLAG = gcovr -r . $(TESTS_C_EXCLUDE)  --html-nested -o report.html 
		CHECK_FLAGS= -lcheck -lm -lpthread --coverage
    else
        GCOV_FLAG = lcov --base-directory . $(TESTS_C_EXCLUDE)  --directory . -f -c -o report_test.info
		CHECK_FLAGS= -lcheck -lm -lpthread -lgcov
		GENERATE_HTML = genhtml -o "report_test_coverage" report_test.info  
    endif
endif

CC=gcc

CFLAGS = -c -Wall -Werror -Wextra -std=c11

UT_EXEC=unit_test.out

UT_LIB=unit_test*.o

BUILD_FLAGS=
COVERAGE_FLAGS= -fprofile-arcs -ftest-coverage

all: clean format test_seq
test_seq: test call_test gcov_report genhtml
test: $(UT_LIB) s21_decimal_tests.a
	$(CC) $(UT_LIB) -L. -ls21_decimal $(CHECK_FLAGS) -o $(UT_EXEC)
s21_decimal.o: s21_*.c
	$(CC) $(CFLAGS) -c s21_*.c
s21_decimal_tests.o: s21_*.c
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c s21_*.c
$(UT_LIB): 
	$(CC) $(CFLAGS) $(BUILD_FLAGS) -c $(TESTS_C) $(COVERAGE_FLAGS)
gcov_report:
	$(GCOV_FLAG)
genhtml: 
	$(GENERATE_HTML)
ifeq ($(OS),Darwin)
	open report.html
endif

call_test:
	./$(UT_EXEC)
s21_decimal.a: s21_decimal.o
	ar rcs s21_decimal.a s21_*.o
s21_decimal_tests.a: s21_decimal_tests.o
	ar rcs libs21_decimal.a s21_*.o
clean:	
	rm -rf *.o *.gcno *.gcda *.html *.css *.info $(UT_EXEC) report_test_coverage *.a *.out test_report.log
format:
	clang-format -i *.c
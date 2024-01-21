GCOV_FLALG=
CHECK_FLAGS=
GENERATE_HTML=
OS := $(shell uname -s)
ifeq ($(OS),Linux)
	GCOV_FLAG = gcovr -r . -e unit_tests.c --html-details -o report.html
	CHECK_FLAGS= -lcheck -lm -lpthread -lrt --coverage -lsubunit
endif
ifeq ($(OS),Darwin)
    OS_VERS := $(shell sw_vers -productVersion)
    ifeq ($(findstring 11.,$(OS_VERS)),)
		GCOV_FLAG = gcovr -r . -e unit_tests.c --html-nested -o report.html
		CHECK_FLAGS= -lcheck -lm -lpthread --coverage
    else
        GCOV_FLAG = lcov --base-directory . -e unit_tests.c --directory . -f -c -o report_test.info
		CHECK_FLAGS= -lcheck -lm -lpthread -lgcov
		GENERATE_HTML = genhtml -o "report_test_coverage" report_test.info  
    endif
endif
CC=gcc 
CFLAGS = -c -Wall -std=c11

# -Werror  -Wextra

BUILD_FLAGS=
COVERAGE_FLAGS= -fprofile-arcs -ftest-coverage
all: clean test_seq
test_seq: test call_test gcov_report genhtml
test: unit_tests.o s21_decimal_tests.a
	$(CC) unit_tests.o -L. -ls21_decimal $(CHECK_FLAGS) -o unit_test_out
s21_decimal.o: s21_*.c
	$(CC) $(CFLAGS) -c s21_*.c
s21_decimal_tests.o: s21_*.c
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c s21_*.c
unit_tests.o: 
	$(CC) $(CFLAGS) $(BUILD_FLAGS) -c unit_tests.c $(COVERAGE_FLAGS)
gcov_report:
	$(GCOV_FLAG)
genhtml: 
	$(GENERATE_HTML)
call_test:
	./unit_test_out
s21_decimal.a: s21_decimal.o
	ar rcs s21_decimal.a s21_*.o
s21_decimal_tests.a: s21_decimal_tests.o
	ar rcs libs21_decimal.a s21_*.o
clean:	
	rm -rf *.o *.gcno *.gcda *.html *.css *.info unit_test_out report_test_coverage *.a *.out test_report.log

#DEBUG_TARGETS
heidiren: clean
	gcc testfield_heidiren.c helpers.c s21_*.c -o a.out && ./a.out

dalbridt: clean
	gcc testfield_dalbridt.c helpers.c s21_*.c -o a.out && ./a.out

annamaer: clean
	gcc testfield_annamaer.c helpers.c s21_*.c -o a.out && ./a.out
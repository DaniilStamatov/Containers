GCC = g++ -Wall -Wextra -Werror -std=c++17
LIBS = $(shell pkg-config --libs --cflags gtest)
OS = $(shell uname)
FILES = $(wildcard containers/*.h tests/*.cc tests/*.h)
TESTS = tests/*.cc

test: clean
ifeq ($(OS),Linux)
	$(GCC) -g -D LIN $(TESTS) $(LIBS) && ./a.out
else
	$(GCC) -g $(TESTS) $(LIBS) && ./a.out
endif

gcov_report: clean
	$(GCC) --coverage $(TESTS) $(LIBS) && ./a.out
	lcov --capture --directory . -o coverage.info --ignore-errors inconsistent --rc branch_coverage=1
	lcov --extract coverage.info 'containers/s21_vector.h' -o coverage_filter.info
	genhtml --output-directory report --legend coverage_filter.info
	open report/index.html

clean:
	rm -rf *.gcda *.gcno *.out *.info report

format:
	clang-format -i --style=Google $(FILES)

style:
	clang-format -n --Werror --style=Google $(FILES)
	cppcheck --enable=all --suppress=missingIncludeSystem $(FILES)

memory: clean
	$(GCC) -g $(TESTS) $(LIBS)
ifeq ($(OS),Linux)
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes -s --trace-children=yes --track-fds=yes --show-leak-kinds=all ./a.out
else
	leaks --atExit -- ./a.out
endif
	rm ./a.out
ifeq ($(OS),Linux)
	$(GCC) -fsanitize=address $(TESTS) $(LIBS) && ./a.out
endif

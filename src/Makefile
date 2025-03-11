GCC = g++ -Wall -Wextra -Werror -std=c++17 -g
LIBS = $(shell pkg-config --libs --cflags gtest)
OS = $(shell uname)
FILES = $(wildcard containers/*.h tests/*.cc tests/*.h)
TESTS = tests/*.cc

test: clean
	@reset
ifeq ($(OS),Linux)
	$(GCC) -D LIN $(TESTS) -lgtest && ./a.out
else
	$(GCC) $(TESTS) $(LIBS) && ./a.out
endif

gcov_report: clean
ifeq ($(OS),Linux)
	$(GCC) -D LIN --coverage $(TESTS) -lgtest && ./a.out
else
	$(GCC) --coverage $(TESTS) $(LIBS) && ./a.out
endif
	lcov --capture --directory . -o coverage.info --ignore-errors inconsistent --rc branch_coverage=1
	lcov --extract coverage.info 'containers/s21_vector.h' -o coverage_filter.info
	genhtml --output-directory report --legend coverage_filter.info
	xdg-open report/index.html

clean:
	rm -rf *.gcda *.gcno *.out *.info report

format:
	clang-format -i --style=Google $(FILES)

style:
	clang-format -n --Werror --style=Google $(FILES)
	cppcheck --enable=all --suppress=missingIncludeSystem $(FILES)

memory: clean
	@reset
ifeq ($(OS),Linux)
	$(GCC) -D LIN $(TESTS) -lgtest
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes -s --trace-children=yes --track-fds=yes --show-leak-kinds=all ./a.out || exit 0
else
	$(GCC) $(TESTS) $(LIBS)
	leaks --atExit -- ./a.out
endif
	rm ./a.out
ifeq ($(OS),Linux)
	$(GCC) -fsanitize=address -D LIN $(TESTS) -lgtest && ./a.out
endif

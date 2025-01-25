GCC = g++ -Wall -Wextra -Werror -std=c++17
LIBS = $(shell pkg-config --libs --cflags gtest)
OS = $(shell uname)

test: clean
ifeq ($(OS),Linux)
	$(GCC) -D LIN test.cpp $(LIBS) && ./a.out
else
	$(GCC) test.cpp $(LIBS) && ./a.out
endif

gcov_report: clean
	$(GCC) --coverage test.cpp $(LIBS) && ./a.out
	lcov --capture --directory . -o coverage.info --ignore-errors inconsistent --rc branch_coverage=1
	lcov --extract coverage.info 'src/*.hpp' -o coverage_filter.info
	genhtml --output-directory report --legend coverage_filter.info
	open report/index.html

clean:
	rm -rf *.gcda *.gcno *.out *.info report

format:
	clang-format -i --style=Google *.hpp *.cpp

style:
	clang-format -n --Werror --style=Google *.hpp
	cppcheck --enable=all --suppress=missingIncludeSystem *.hpp *.cpp

memory: clean
	$(GCC) -fsanitize=address test.cpp $(LIBS) && ./a.out
	rm ./a.out
	$(GCC) test.cpp $(LIBS)
ifeq ($(OS),Linux)
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes -s --trace-children=yes --track-fds=yes --show-leak-kinds=all ./a.out
else
	leaks --atExit -- ./a.out
endif

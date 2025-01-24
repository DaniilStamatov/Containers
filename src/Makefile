OS := $(shell uname -s)
ARCH := $(shell uname -m)
OPEN_CMD = open

ARCH_PREFIX =
CC=g++ -Werror -Wall -Wextra -std=c++17
LDFLAGS = -I.
GTEST_FLAGS = $(shell pkg-config --cflags --libs gtest_main gtest)
INCLUDES= -Icontainers -Icontainersplus

SOURCES=$(wildcard containers/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=s21_containers.a

PLUS_SOURCES=$(wildcard containersplus/*.cpp)
PLUS_OBJECTS=$(PULS_SOURCES:.cpp=.o)
PLUS_EXECUTABLE=s21_containersplus.a

TEST_SOURCES=tests/*.cpp
TEST_EXECUTABLE=test

ifeq ($(OS),Linux)
    OS = LINUX
endif

all: $(EXECUTABLE) $(PLUS_EXECUTABLE)

install:
	if [ $(OS) = "LINUX" ]; then \
		sudo apt-get install -y libgtest-dev; \
		sudo apt-get install -y pkg-config; \
	else \
		brew install googletest pkg-config; \
	fi

$(EXECUTABLE):
	$(CC) $(FLAGS) -c $(SOURCES)
	ar rcs lib$(EXECUTABLE) $(OBJECTS)
	ranlib lib$(EXECUTABLE)
	rm -rf *.o

$(PLUS_EXECUTABLE):
	$(CC) $(FLAGS) -c $(PLUS_SOURCES)
	ar rcs lib$(PLUS_EXECUTABLE) $(PLUS_OBJECTS)
	ranlib lib$(PLUS_EXECUTABLE)
	rm -rf *.o

test: clean
	$(CC) $(FLAGS) $(TEST_SOURCES) $(SOURCES) $(PLUS_SOURCES) -o $(TEST_EXECUTABLE) $(LDFLAGS) $(GTEST_FLAGS) $(INCLUDES)
	./$(TEST_EXECUTABLE)
	rm -rf *.o

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(EXECUTABLE) $(PLUS_EXECUTABLE) $(TEST_EXECUTABLE) $(COVERAGE_FOLDER) report *.o *.a *.gcda *.gcno *.gcov *.html *.css *.info *.cleaned

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem .

valgrind: $(TEST_EXECUTABLE)
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes ./$(TEST_EXECUTABLE)

leaks: $(TEST_EXECUTABLE)
	CK_FORK=no leaks -atExit -- ./$(TEST_EXECUTABLE)

format:
	cp ../materials/linters/.clang-format .
	find . -type f \( -name '*.cpp' -o -name '*.h' \) -exec clang-format -i {} \; -exec clang-format -n {} \;

checks: format cppcheck
	if [ $(OS) = "LINUX" ]; then \
		make valgrind;  \
	else \
		make leaks; \
	fi

rebuild: clean all

.PHONY: all test gcov_report clean checks rebuild $(EXECUTABLE)
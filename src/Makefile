OS := $(shell uname -s)
ARCH := $(shell uname -m)
OPEN_CMD = open

ARCH_PREFIX =
CC = g++
CXXFLAGS = -Werror -Wall -Wextra -std=c++17
LDFLAGS = -I.
GTEST_FLAGS = $(shell pkg-config --cflags --libs gtest_main gtest)
INCLUDES = -Icontainers -Icontainersplus

# Source and object files
TEST_SOURCES = tests/*.cpp

# Build directory
BUILD_DIR = build

# Executables
TEST_EXECUTABLE = $(BUILD_DIR)/test

# Ensure the build directory exists
$(shell mkdir -p $(BUILD_DIR)/containers $(BUILD_DIR)/containersplus)

# Targets
all: test

install:
ifeq ($(OS),Linux)
	sudo apt-get install -y libgtest-dev pkg-config
else
	brew install googletest pkg-config
endif

test:
	$(CC) $(CXXFLAGS) $(TEST_SOURCES) -g -o $(TEST_EXECUTABLE) $(LDFLAGS) $(GTEST_FLAGS) $(INCLUDES) -L$(BUILD_DIR)
	./$(TEST_EXECUTABLE)

clean:
	rm -rf $(BUILD_DIR) report *.gcda *.gcno *.gcov *.html *.css *.info *.cleaned

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem .

valgrind: $(TEST_EXECUTABLE)
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes -s ./$(TEST_EXECUTABLE)

leaks: $(TEST_EXECUTABLE)
	CK_FORK=no leaks -atExit -- ./$(TEST_EXECUTABLE)

format:
	cp ../materials/linters/.clang-format .
	find . -type f \( -name '*.cpp' -o -name '*.h' \) -exec clang-format -i {} \; -exec clang-format -n {} \;

checks: format cppcheck
ifeq ($(OS),Linux)
	make valgrind
else
	make leaks
endif

rebuild: clean all

.PHONY: all install test clean cppcheck valgrind leaks format checks rebuild
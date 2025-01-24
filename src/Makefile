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
SOURCES = $(wildcard containers/*.cpp)
PLUS_SOURCES = $(wildcard containersplus/*.cpp)
TEST_SOURCES = tests/*.cpp

# Build directory
BUILD_DIR = build
OBJECTS = $(patsubst containers/%.cpp, $(BUILD_DIR)/containers/%.o, $(SOURCES))
PLUS_OBJECTS = $(patsubst containersplus/%.cpp, $(BUILD_DIR)/containersplus/%.o, $(PLUS_SOURCES))

# Executables
EXECUTABLE = $(BUILD_DIR)/libs21_containers.a
PLUS_EXECUTABLE = $(BUILD_DIR)/libs21_containersplus.a
TEST_EXECUTABLE = $(BUILD_DIR)/test

# Ensure the build directory exists
$(shell mkdir -p $(BUILD_DIR)/containers $(BUILD_DIR)/containersplus)

# Targets
all: $(EXECUTABLE) $(PLUS_EXECUTABLE)

install:
ifeq ($(OS),Linux)
	sudo apt-get install -y libgtest-dev pkg-config
else
	brew install googletest pkg-config
endif

$(EXECUTABLE): $(OBJECTS)
	ar rcs $@ $^

$(PLUS_EXECUTABLE): $(PLUS_OBJECTS)
	ar rcs $@ $^

test: $(EXECUTABLE) $(PLUS_EXECUTABLE)
	$(CC) $(CXXFLAGS) $(TEST_SOURCES) -o $(TEST_EXECUTABLE) $(LDFLAGS) $(GTEST_FLAGS) $(INCLUDES) -L$(BUILD_DIR) -ls21_containers -ls21_containersplus
	./$(TEST_EXECUTABLE)

$(BUILD_DIR)/containers/%.o: containers/%.cpp
	$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/containersplus/%.o: containersplus/%.cpp
	$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) report *.gcda *.gcno *.gcov *.html *.css *.info *.cleaned

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
ifeq ($(OS),Linux)
	make valgrind
else
	make leaks
endif

rebuild: clean all

.PHONY: all install test clean cppcheck valgrind leaks format checks rebuild
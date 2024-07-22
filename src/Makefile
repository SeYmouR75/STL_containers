CC=g++
CFLAGS=-std=c++17 -pedantic -lgtest #-Wall -Werror -Wextra
TEST_DIR=./tests
BUILD_DIR=./build
REPORT_DIR=./report

ifeq ($(wildcard $(BUILD_DIR)), )
  $(shell mkdir $(BUILD_DIR))
endif
ifeq ($(wildcard $(REPORT_DIR)), )
  $(shell mkdir $(REPORT_DIR))
endif

SRC=$(wildcard $(TEST_DIR)/*.cpp)
OBJ=$(addprefix $(BUILD_DIR)/,$(SRC:%.cpp=%.o))
TARGET=$(BUILD_DIR)/s21_test_containers.exe

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

test: rebuild
	./$(TARGET)

valgrind: rebuild
	valgrind --tool=memcheck --leak-check=yes -s ./$(TARGET)

gcov_report: clean gcov_flags test
	lcov -o $(REPORT_DIR)/s21_containers.info -c -d $(BUILD_DIR) --ignore-errors mismatch
	lcov -r $(REPORT_DIR)/s21_containers.info '/usr/include/*' -o $(REPORT_DIR)/filtered_coverage.info
	genhtml $(REPORT_DIR)/filtered_coverage.info -o report 
	xdg-open $(REPORT_DIR)/index.html

gcov_flags: 
	$(eval CFLAGS +=-g3 -fprofile-arcs -ftest-coverage --coverage)

clean_obj:
	rm -rf $(BUILD_DIR)/*
	rm -rf $(TARGET)

clean_gcov:
	rm -rf $(REPORT_DIR)/*

clean: clean_obj clean_gcov

clang_check:
	find . -name "*.cpp" | xargs clang-format -style=Google -n
	find . -name "*.h" | xargs clang-format -style=Google -n

clang_format: clang_check
	find . -name "*.cpp" | xargs clang-format -style=Google -i
	find . -name "*.h" | xargs clang-format -style=Google -i
	
rebuild: clean all
TARGET = s21_matrix_oop.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c++17 -O3 -lstdc++
TEST_FLAGS = -lgtest -pthread
TEST_TARGET = test
MODULES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(MODULES))

all: clean $(TARGET)

build: $(TARGET)

rebuild: clean $(TARGET)

%.o: %.cpp
	@mkdir -p obj
	@$(CC) -c $(CFLAGS) $< -o ./obj/$@

$(TARGET): $(OBJECTS)
	@ar rcs $(TARGET) $(wildcard obj/*.o)

test: $(TARGET)
	@g++ $(CFLAGS) ./*.cpp $(TEST_FLAGS) $(TARGET) -o ./$(TEST_TARGET)
	@./$(TEST_TARGET)

style_check:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@cp ../materials/linters/.clang-format .
	@clang-format -n *.cpp *.h
	@rm ./.clang-format

format_style:
	@echo "┏=========================================┓"
	@echo "┃  Formatting your code for Google Style  ┃"
	@echo "┗=========================================┛"
	@cp ../materials/linters/.clang-format .
	@clang-format -i *.cpp *.h
	@rm ./.clang-format

leaks:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_TARGET)

valgrind:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="valgrind.log" ./$(TEST_TARGET)
clean:
	@echo "Deleting unnecessary files..."
	@rm -rf obj *.a *.o $(TEST_TARGET) *.dSYM /*.dSYM *.log /*.log

.PHONY: all build rebuild test style_check format_style leaks valgrind clean
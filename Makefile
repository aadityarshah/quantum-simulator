CC = gcc

CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -g -Iinclude

LDLIBS = -lm

SRC_DIR = src
TEST_DIR = tests
INCLUDE_DIR = include
BUILD_DIR = build

TEST = $(BUILD_DIR)/test_complex

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TEST): $(SRC_DIR)/complex.c $(TEST_DIR)/test_complex.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

test: $(TEST)
	./$(TEST)

format:
	find $(SRC_DIR) $(INCLUDE_DIR) $(TEST_DIR) -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format -i {} +

format-check:
	find $(SRC_DIR) $(INCLUDE_DIR) $(TEST_DIR) -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format --dry-run --Werror {} +

lint:
	clang-tidy $(SRC_DIR)/*.c -- -std=c17 -Iinclude
	
clean:
	rm -rf $(BUILD_DIR)
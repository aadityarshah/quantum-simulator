CC = gcc

CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -g -Iinclude

LDLIBS = -lm

SRC_DIR = src
TEST_DIR = tests
INCLUDE_DIR = include
BUILD_DIR = build

TESTS = $(BUILD_DIR)/test_complex $(BUILD_DIR)/test_qubit $(BUILD_DIR)/test_quantum_state

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/test_complex: $(SRC_DIR)/complex.c $(TEST_DIR)/test_complex.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD_DIR)/test_qubit: $(SRC_DIR)/complex.c $(SRC_DIR)/qubit.c $(TEST_DIR)/test_qubit.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD_DIR)/test_quantum_state: $(SRC_DIR)/complex.c $(SRC_DIR)/qubit.c  $(SRC_DIR)/quantum_state.c $(TEST_DIR)/test_quantum_state.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

test: $(TESTS)
	./$(BUILD_DIR)/test_complex
	./$(BUILD_DIR)/test_qubit
	./$(BUILD_DIR)/test_quantum_state

format:
	find $(SRC_DIR) $(INCLUDE_DIR) $(TEST_DIR) -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format -i {} +

format-check:
	find $(SRC_DIR) $(INCLUDE_DIR) $(TEST_DIR) -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format --dry-run --Werror {} +

lint:
	clang-tidy $(SRC_DIR)/*.c -- -std=c17 -Iinclude

clean:
	rm -rf $(BUILD_DIR)
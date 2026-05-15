CC       = gcc
CFLAGS   = -Wall -Wextra -Werror -std=c99
CPPFLAGS = -MMD -I src -I src/libchessviz -I thirdparty
# Флаги для тестов — без -Werror чтобы ctest.h не ломал сборку
TEST_CFLAGS = -std=c99 -I src -I src/libchessviz -I thirdparty
# Флаги для coverage
COV_CFLAGS = -std=c99 -I src -I src/libchessviz --coverage
SRC_DIR  = src
LIB_SRC  = $(SRC_DIR)/libchessviz
APP_SRC  = $(SRC_DIR)/chessviz
TEST_DIR = test
OBJ_DIR  = obj
BIN_DIR  = bin
COV_DIR  = cov
TARGET      = $(BIN_DIR)/chessviz
TEST_TARGET = $(BIN_DIR)/chessviz-test
COV_TARGET  = $(BIN_DIR)/chessviz-test-cov
LIB         = $(OBJ_DIR)/libchessviz.a
COV_LIB     = $(OBJ_DIR)/libchessviz-cov.a
# Исходники
LIB_SRCS  = $(wildcard $(LIB_SRC)/*.c)
APP_SRCS  = $(wildcard $(APP_SRC)/*.c)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
# Объектные файлы
LIB_OBJS  = $(patsubst $(SRC_DIR)/%.c,  $(OBJ_DIR)/%.o, $(LIB_SRCS))
APP_OBJS  = $(patsubst $(SRC_DIR)/%.c,  $(OBJ_DIR)/%.o, $(APP_SRCS))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/$(TEST_DIR)/%.o, $(TEST_SRCS))
# Объектные файлы для coverage
COV_LIB_OBJS  = $(patsubst $(SRC_DIR)/%.c,  $(OBJ_DIR)/cov/%.o, $(LIB_SRCS))
COV_TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/cov/$(TEST_DIR)/%.o, $(TEST_SRCS))
# Файлы зависимостей
DEPS = $(LIB_OBJS:.o=.d) $(APP_OBJS:.o=.d) $(TEST_OBJS:.o=.d)
# ──────────────────────────────────────────────
.PHONY: all test coverage clean
all: $(BIN_DIR) $(TARGET)
test: $(BIN_DIR) $(TEST_TARGET)
	./$(TEST_TARGET)
coverage: $(BIN_DIR) $(COV_DIR) $(COV_TARGET)
	./$(COV_TARGET)
	lcov --capture --directory $(OBJ_DIR)/cov \
	     --output-file $(COV_DIR)/coverage.info \
	     --ignore-errors source
	lcov --remove $(COV_DIR)/coverage.info \
	     '*/thirdparty/*' '*/test/*' \
	     --output-file $(COV_DIR)/coverage_filtered.info \
	     --ignore-errors source
	lcov --summary $(COV_DIR)/coverage_filtered.info
	@COVERAGE=$$(lcov --summary $(COV_DIR)/coverage_filtered.info 2>&1 \
	    | grep -oP '\d+\.\d+(?=%)' | head -1); \
	echo "Line coverage: $${COVERAGE}%"; \
	python3 -c "import sys; v=float('$${COVERAGE}'); sys.exit(0 if v>=60 else 1)" \
	    || (echo "FAIL: coverage $${COVERAGE}% is below 60%" && exit 1)
$(BIN_DIR):
	mkdir -p $(BIN_DIR)
$(COV_DIR):
	mkdir -p $(COV_DIR)
# Линковка основного приложения
$(TARGET): $(APP_OBJS) $(LIB)
	$(CC) $(CFLAGS) -o $@ $^
# Линковка тестового приложения
$(TEST_TARGET): $(TEST_OBJS) $(LIB)
	$(CC) $(CFLAGS) -o $@ $^
# Линковка coverage-бинаря
$(COV_TARGET): $(COV_TEST_OBJS) $(COV_LIB)
	$(CC) $(COV_CFLAGS) -o $@ $^
# Сборка статической библиотеки
$(LIB): $(LIB_OBJS)
	@mkdir -p $(@D)
	ar rcs $@ $^
# Сборка статической библиотеки (coverage)
$(COV_LIB): $(COV_LIB_OBJS)
	@mkdir -p $(@D)
	ar rcs $@ $^
# Компиляция объектных файлов из src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<
# Компиляция объектных файлов из test/ — без -Werror (ctest.h)
$(OBJ_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $(TEST_CFLAGS) -MMD -o $@ $<
# Компиляция src/ (coverage)
$(OBJ_DIR)/cov/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $(COV_CFLAGS) -o $@ $<
# Компиляция test/ (coverage)
$(OBJ_DIR)/cov/$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $(TEST_CFLAGS) --coverage -o $@ $<
-include $(DEPS)
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/chessviz $(BIN_DIR)/chessviz-test \
	       $(BIN_DIR)/chessviz-test-cov $(COV_DIR)

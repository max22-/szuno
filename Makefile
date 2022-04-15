EXEC = szuno
BIN_DIR = $(PWD)/bin
BUILD_DIR = $(PWD)/build
SRC_DIRS = src

SRCS = $(shell find $(SRC_DIRS) -name *.c)
OBJS = $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

INC_DIRS = include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS = $(INC_FLAGS) -Wall -MMD -MP -std=c89
LDFLAGS =

all: $(BIN_DIR)/$(EXEC)

$(BIN_DIR):
	mkdir -p bin

$(BIN_DIR)/$(EXEC): $(OBJS) $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run format clean todo

run: $(BIN_DIR)/$(EXEC)
	$(BIN_DIR)/$(EXEC)

format:
	find src/* -exec clang-format -i {} \;

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)/$(EXEC)

todo:
	@grep -r "TODO" --exclude="Makefile" || true

-include $(DEPS)

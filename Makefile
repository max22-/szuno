CFLAGS = -Wall -std=c89 -MMD -MP -ggdb
-include $(DEPS)
EXEC = szuno
SRCS = $(shell find src -name "*.c")
OBJS = $(SRCS:src/%.c=build/%.o)
DEPS = $(OBJS:.o=.d)

all: bin/$(EXEC)

bin:
	mkdir -p bin

build:
	mkdir -p build

bin/$(EXEC): $(OBJS) bin
	$(CC) $(OBJS) -o $@

build/%.o: src/%.c build
	$(CC) $(CFLAGS) $< -c -o $@

.PHONY: run clean todo

run: bin/$(EXEC)
	bin/$(EXEC)

clean:
	rm -rf build bin

todo:
	@grep -r "TODO" --exclude="Makefile" || true

-include $(DEPS)
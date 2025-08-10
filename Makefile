CC = gcc
CFLAGS = -Wall -Iinclude
SRC = $(filter-out src/main.c, $(wildcard src/*.c))
OBJ = $(SRC:.c=.o)
TESTS = $(wildcard tests/*.c)
TEST_OBJ = $(TESTS:.c=.o)
TEST_LIBS = -lcunit
BIN=nenostatus
TEST_BIN=test_$(BIN)

.PHONY: tests clean all

all: $(BIN)

$(BIN): src/main.o $(OBJ)
	@echo LD $@
	@$(CC) $(CFLAGS) -o $@ $^

$(TEST_BIN): $(TEST_OBJ) $(OBJ)
	@echo LD $@
	@$(CC) $(CFLAGS) $(TEST_LIBS) -o $@ $^

src/%.o: src/%.c
	@echo CC $@
	@$(CC) $(CFLAGS) -c $< -o $@

tests/%.o: tests/%.c
	@echo CC $@
	@$(CC) $(CFLAGS) $(TEST_LIBS) -c $< -o $@

tests: $(TEST_BIN)
	@echo EXEC $<
	@./$<

watch:
	@make tests
	@while inotifywait -e modify,create,delete -r . > /dev/null 2> /dev/null; \
		do make tests; \
	done

clean:
	@echo RM src/*.o
	@rm -f src/*.o
	@echo RM $(BIN)
	@rm -f $(BIN)
	@echo RM tests/*.o
	@rm -f tests/*.o
	@echo RM $(TEST_BIN)
	@rm -f $(TEST_BIN)

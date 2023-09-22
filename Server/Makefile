SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

CC = clang
CPPFLAGS = -std=gnu99 -Isrc -Iinclude -MMD -MP
CFLAGS = -Wall -Wextra
LDFLAGS = -Llib
LDLIBS = -lm -lmongoose

EXE = $(BIN_DIR)/main
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

RM = rm -rf

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ $(XFLAGS)

$(BIN_DIR) $(OBJ_DIR):
	@mkdir -p $@

clean:
	@$(RM) $(BIN_DIR) $(OBJ_DIR)
	@$(RM) `find . -name "*.dSYM" -print`

-include $(OBJ:.o=.d)

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -g -Iinclude
LDFLAGS = -lm

TARGET = build/graph_layout

SRC_DIR = src
OBJ_DIR = build
INC_DIR = include
DATA_DIR = data

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) wynik*.txt

test: $(TARGET)
	@echo "=== TEST 1: Oczekiwany sukces (Graf planarny) ==="
	./$(TARGET) -i $(DATA_DIR)/graf_planarny.txt -o wynik1.txt -a tutte
	
	@echo "\n=== TEST 2: Oczekiwany blad (Graf nieplanarny) ==="
	-./$(TARGET) -i $(DATA_DIR)/graf_nieplanarny.txt -o wynik2.txt -a tutte
	
	@echo "\n=== TEST 3: Oczekiwany blad (Zle argumenty wejsciowe) ==="
	-./$(TARGET) -x nieistniejaca_flaga -i $(DATA_DIR)/graf_planarny.txt

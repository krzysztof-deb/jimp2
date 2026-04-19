CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -g
LDFLAGS = -lm

TARGET = graph_layout.exe


SRCS = main.c reingold.c tutte.c graph.c planarnosc.c config.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) wynik*.txt

test: $(TARGET)
	@echo "=== TEST 1: Oczekiwany sukces (Graf planarny, zapisany w wyniki1.txt) ==="
	./$(TARGET) -i graf_planarny.txt -o wynik1.txt -a tutte
	
	@echo "\n=== TEST 2: Oczekiwany blad (Graf nieplanarny) ==="
	-./$(TARGET) -i graf_nieplanarny.txt -o wynik2.txt -a tutte
	
	@echo "\n=== TEST 3: Oczekiwany blad (Zle argumenty wejsciowe) ==="
	-./$(TARGET) -x nieistniejaca_flaga -i graf_planarny.txt
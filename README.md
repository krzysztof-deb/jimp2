# Graph Visualiser

Projekt do wizualizacji grafów planarnych, składający się z backendu w języku C oraz frontendu w Javie.

## Struktura projektu

* `backend/` - Rdzeń obliczeniowy w języku C.
    * `src/` - Pliki źródłowe.
    * `include/` - Pliki nagłówkowe.
    * `data/` - Przykładowe dane wejściowe.
    * `Makefile` - Skrypt budowania backendu.
* `frontend/` - Aplikacja wizualizacyjna w Java Swing (w przygotowaniu).

## Backend (C)

Aplikacja konsolowa służąca do wyznaczania współrzędnych węzłów dla wizualizacji grafu planarnego.

### Kompilacja i uruchomienie

Aby skompilować backend:
```bash
cd backend
make
```

Aby uruchomić testy:
```bash
make test
```

Wynik kompilacji znajduje się w `backend/build/graph_layout`.

### Użycie
```bash
./backend/build/graph_layout -i backend/data/graf_planarny.txt -o wynik.txt -a tutte
```

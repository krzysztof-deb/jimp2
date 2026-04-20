# Wizualizacja Grafów Planarnych (Część w języku C)

Aplikacja konsolowa służąca do wyznaczania współrzędnych węzłów dla "ładnej" wizualizacji grafu planarnego, podanego w postaci listy krawędzi. Wynikiem działania programu jest plik z wyliczonymi współrzędnymi 
X i Y dla każdego wierzchołka.

## Funkcjonalności
* Wczytywanie grafów z plików tekstowych.
* Obliczanie współrzędnych wierzchołków przy użyciu zaimplementowanych algorytmów.
* **Walidacja planarności (post-walidacja):** Program po wyliczeniu współrzędnych weryfikuje matematycznie, czy wygenerowany rysunek nie zawiera przecinających się krawędzi. W przypadku wykrycia zderzenia,
* program zgłasza błąd i przerywa działanie.
* Eksport wyliczonych współrzędnych do pliku tekstowego.
* W pełni zautomatyzowany proces budowania i testowania przy użyciu pliku `Makefile`.

## Kompilacja

Projekt wykorzystuje narzędzie Make oraz kompilator `gcc` (standard C11). Aby skompilować program, otwórz terminal w folderze z projektem i wpisz:

```bash
make
```
do wykonania zautomatyzowanych testów:
```bash
make test
```
oczekiwanym wynikiem testów są 3 scenariusze. W pierszym obliczenia się udają i do pliku wyniki1.txt zapisany zostaje graf planarny. W drugim powstały graf nie jest planarny, a w trzecim podano złe argumenty 
wejścia i wyrzucany jest błąd.

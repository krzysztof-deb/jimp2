# Graph Visualiser

Projekt do wizualizacji grafów planarnych, składający się z backendu w języku C oraz frontendu w Javie Swing.

## Struktura projektu

* `backend/` - Rdzeń obliczeniowy w języku C (odpowiedzialny za obliczanie współrzędnych wierzchołków).
    * `src/` - Pliki źródłowe C.
    * `include/` - Pliki nagłówkowe.
    * `data/` - Przykładowe pliki wejściowe z grafami planarnego i nieplanarnego.
    * `Makefile` - Skrypt budowania backendu (GCC/make).
* `frontend/` - Aplikacja wizualizacyjna w Java Swing (wizualizuje grafy na podstawie współrzędnych wyznaczonych przez backend).
    * `src/` - Kod źródłowy Java.
    * `pom.xml` - Konfiguracja projektu Maven.
* `clean_build_backend.bat` - Skrypt wsadowy Windows do automatycznego i czystego budowania backendu wewnątrz WSL.

---

## Ustandaryzowane uruchamianie

Aplikacja kliencka (frontend) uruchamia plik wykonywalny backendu i przekazuje mu dane wejściowe. Ze względu na różnice między systemami operacyjnymi, frontend automatycznie zarządza sposobem wywołania backendu:
- **Na Linux / macOS**: Bezpośrednio wywołuje skompilowany plik binarny `backend/build/graph_layout`.
- **Na Windows (Natywnie)**: Jeśli wykryje obecność skompilowanego pliku `backend/build/graph_layout.exe`, uruchomi go bezpośrednio na hostie.
- **Na Windows (z WSL)**: Jeśli brak pliku `.exe`, ale w repozytorium znajduje się wersja skompilowana pod Linuxa/WSL, Java automatycznie uruchomi backend wewnątrz środowiska **WSL (Windows Subsystem for Linux)** przy użyciu komendy `wsl`. Odbywa się to bez interwencji użytkownika – ścieżki do plików są automatycznie mapowane na format Unixowy (np. `/mnt/c/...`).

---

## Instrukcja Uruchomienia

Szczegółowy opis kompilacji i uruchomienia dla poszczególnych systemów operacyjnych:

### 1. Windows + WSL 
Ta metoda pozwala na wygodne korzystanie z natywnego GUI na Windowsie, podczas gdy backend kompiluje się i uruchamia w przyjaznym dla C środowisku WSL.

1. **Wymagania**: Zainstalowane WSL (np. dystrybucja Ubuntu), JDK 17+ na Windowsie.
2. **Kompilacja backendu (w WSL)**:
   Możesz to zrobić na dwa sposoby:
   - **Automatycznie (Rekomendowane):** Kliknij dwukrotnie plik **`clean_build_backend.bat`** w katalogu głównym projektu. Skrypt ten wyczyści stare pliki kompilacji w WSL i zbuduje backend na nowo.
   - **Ręcznie:** Uruchom konsolę WSL w folderze `backend` i wpisz:
     ```bash
     make clean
     make
     ```
3. **Uruchomienie frontendu (w Windows)**:
   - Wczytaj projekt w **IntelliJ IDEA** (otwierając katalog `frontend` jako projekt Maven). Ustaw JDK 17+ i uruchom klasę `graphvisualizer.view.MainFrame`.
   - LUB z linii komend Windows (jeśli Maven jest zainstalowany):
     ```cmd
     cd frontend
     mvn clean compile exec:java
     ```

---

### 2. Linux 

1. **Wymagania**: Zainstalowane `gcc`, `make` (np. pakiet `build-essential`), Java JDK 17+ oraz Maven.
2. **Kompilacja backendu**:
   ```bash
   cd backend
   make clean
   make
   ```
3. **Uruchomienie frontendu**:
   ```bash
   cd ../frontend
   mvn clean compile exec:java
   ```

---

### 3. macOS

1. **Wymagania**: Zainstalowane Xcode Command Line Tools (`xcode-select --install`), Java JDK 17+ oraz Maven (np. przez Homebrew: `brew install openjdk maven`).
2. **Kompilacja backendu**:
   ```bash
   cd backend
   make clean
   make
   ```
3. **Uruchomienie frontendu**:
   ```bash
   cd ../frontend
   mvn clean compile exec:java
   ```

---

### 4. Windows (Natywnie - bez WSL)

Wymaga posiadania lokalnego kompilatora GCC (np. z MSYS2 lub MinGW).

1. **Kompilacja backendu**:
   W konsoli obsługującej kompilator GCC w folderze `backend` wpisz:
   ```powershell
   make clean
   make
   ```
   *(Alternatywnie, ręcznie z PowerShell/CMD)*:
   ```powershell
   gcc -Wall -Wextra -pedantic -std=c11 -g -Ibackend/include backend/src/*.c -o backend/build/graph_layout.exe -lm
   ```
2. **Uruchomienie frontendu**:
   Uruchom klasę `MainFrame` przez IntelliJ IDEA lub za pomocą Maven w folderze `frontend`:
   ```powershell
   mvn clean compile exec:java
   ```

---

## Testowanie backendu

Aby przetestować poprawność działania algorytmów backendu w środowisku Unix (lub WSL), uruchom w folderze `backend`:
```bash
make test
```

# Definicje klas i ich składowych w C++

Należy zaimplementować klasę reprezentującą macierz elementów double.
Klasa ma mieć następujące metody:

1. [x] Dwa konstruktory:
    przyjmujący dwa argumenty
    typu int tworzący macierz o podanych wymiarach zainicjalizowaną zerami
   [x] przyjmujący jeden argument
    typu int tworzący macierz kwadratową o podanym rozmiarze zainicjalizowaną zerami
2. [x] set(n, m, val)
    metoda ustawiająca wartość elementu (n, m) na val
3. [x] get(n, m)
    metoda pobierająca element (n, m)
4. [x] add(Matrix m2)
    metoda przyjmująca jako argument inną macierz i zwracająca jako wynik nową macierz będącą sumą bieżącej macierzy oraz macierzy przekazanej jako argument
5. [x] subtract(Matrix m2)
    metoda przyjmująca jako argument inną macierz i zwracająca jako wynik nową macierz będącą różnicą bieżącej macierzy oraz macierzy przekazanej jako argument
6. [x] multiply(Matrix m2)
    metoda przyjmująca jako argument inną macierz i zwracająca jako wynik nową macierz będącą iloczynem bieżącej macierzy oraz macierzy  przekazanej jako argument
7. [x] cols()
    metoda zwracająca liczbę kolumn macierzy
8. [x] rows()
    metoda zwracająca liczbę wierszy macierzy
9. [x] print()
    metoda wyświetlająca macierz na ekranie
10. [x] store(std::string filename, std::string path)
    metoda zapisująca macierz w pliku; w pliku powinny być zapisane wymiary macierzy (liczba kolumn i liczba wierszy w pierwszym wierszu pliku) oraz jej zawartość (każdy wiersz macierzy w osobnym wierszu pliku)
11. [x] dodatkowy konstruktor
    jako argument przyjmujący ścieżkę do pliku o podanym wcześniej formacie i na jego podstawie tworzący nową macierz na podstawie przekazanego pliku
12. [ ] metoda main
    pokazującą działanie wszystkich powyższych metod na przykładzie macierzy o rozmiarze co najmniej 4 (należy zademonstrować działanie wszystkich konstruktorów).

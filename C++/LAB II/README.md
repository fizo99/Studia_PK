### Zadanie 1
Napisz funkcję otrzymującą jako argumenty wskaźniki do dwóch zmiennych typu int, która zamienia ze sobą wartości wskazywanych zmiennych tylko wtedy, gdy wskazywana przez drugi argument zmienna jest mniejsza od zmiennej wskazywanej przez pierwszy argument.

### Zadanie 2
Napisz funkcję otrzymującą jako argumenty referencje
do dwóch zmiennych typu int, która zamienia ze sobą wartości zmiennych, do których referencje dostaliśmy w argumentach.

### Zdanie 3
Napisz funkcję otrzymującą dwa argumenty referencję a
oraz wskaźnik b do zmiennych typu int, która zamienia ze sobą wartości zmiennych, do których wskaźnik i referencję dostała w argumentach.

### Zadanie 4
Napisz funkcję, która pobiera dwa argumenty i zwraca dwa odrębne wyniki.
Jednym z wyników powinien być iloczyn obu argumentów, a drugim ich suma. Ponieważ funkcja może bezpośrednio zwracać tylko jedną wartość, druga
powinna być zwracana poprzez parametr wskaźnikowy albo referencję.

### Zadanie 5
Napisz funkcję, która zamienia miejscami wartości swoich dwóch argumentów.
Przekaż do funkcji argumenty przy użyciu wskaźników albo referencji.
Przygotuj odpowiednie testy dla zaproponowanego rozwiązania.

### Zadanie 6
(Source)[http://cpp0x.pl/dokumentacja/standard-C++/swap/461]
Należy wziąć pod uwagę, że ta funkcja powoduje skopiowanie obiektu do zmiennej tymczasowej i dwa razy wywołuje operator przypisania, 
więc może nie być efektywna dla typów, dla których wspomniane operacje są kosztowne. 
W takie sytuacji rekomendowane jest przeciążenie tej funkcji tak, by wykonywała zamianę w wydajniejszy sposób.
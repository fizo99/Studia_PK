#### Zadanie 1

Napisz program sortujący rosnąco ciąg liczb podanch jako argument programu.

Przykład dla zadania nr 1

```sh
sort.exe 100 2 30 5 8 34 56 78 90
out = 2 5 8 30 34 56 78 90 100

chmod +x sort
./sort 100 2 30 5 8 34 56 78 90
out = 2 5 8 30 34 56 78 90 100
```

#### Zadanie 2

Napisz program, który określi czy wczytany ciąg (argument programu) jest palindromem tekstowym.

#### Zadanie 3

Napisz kalkulator wyliczający wskaźnik BMI (Body Mass Index)

Wzór dla wskaźnika BMI

```cpp
BMI = (masa_ciala)/(wzrost * wzrost) // masa_ciala [kg], wzrost [m]
```

```
Zakresy wartości BMI:
mniej niż 16 - wygłodzenie
16 - 16.99 - wychudzenie
17 - 18.49 - niedowaga
18.5 - 24.99 - wartość prawidłowa
25 - 29.99 - nadwaga
30 - 34.99 - I stopień otyłości
35 - 39.99 - II stopień otyłości
powyżej 40 - otyłość skrajna
```

#### Zadanie 4

Dwie różne liczby całkowite a i b większe od 1 nazwiemy skojarzonymi,
jeśli suma wszystkich różnych dodatnich dzielników a mniejszych od a jest równa b+1,
a suma wszystkich różnych dodatnich dzielników b mniejszych od b jest równa a+1.

Skojarzone są np. liczby 140 i 195, ponieważ:
a) dzielnikami 140 są 1, 2, 4, 5, 7, 10, 14, 20, 28, 35, 70, a ich suma wynosi 196 = 195+1.
b) dzielnikami 195 są 1, 3, 5, 13, 15, 39, 65, a suma tych liczb równa jest 141 = 140+1.

#### Zadanie 5

Napisz program, który doda do siebie dwie macierze o wymiarach 2 x 3.

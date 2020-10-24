

#include "triangle.h"
#pragma warning(disable:4996)

int main()
{
	//operacja na pliku 
	//(WSZYSTKIE DANE ZOSTANA ZAPISANE DO PLIKU my_output_file.txt -> konsola bedzie pusta)
	// po zakomentowaniu linii 11 i 61 program działa normalnie w konsoli
	//FILE *f = freopen("my_output_file.txt", "w", stdout);

	//ABC
	MY_NODE A;
	A.crd[0] = 0;
	A.crd[1] = 0;
	MY_NODE B;
	B.crd[0] = 1;
	B.crd[1] = 2;
	MY_NODE C;
	C.crd[0] = 2;
	C.crd[1] = 1;

	//MNK
	MY_NODE M;
	M.crd[0] = 1;
	M.crd[1] = 1;
	MY_NODE N;
	N.crd[0] = 2;
	N.crd[1] = 4;
	MY_NODE K;
	K.crd[0] = 3;
	K.crd[1] = 2;

	//alokacja,stworzenie trojkatow
	MY_TRIANGLE *abc = TriangInit(&A, &B, &C);
	MY_TRIANGLE *mnk = TriangInit(&M, &N, &K);

	char nazwa1[4] = "ABC";
	char nazwa2[4] = "MNK";

	//wyswietlenie
	TrianglePrint(abc, nazwa1);
	TrianglePrint(mnk, nazwa2);


	// przypisanie i wyswietlenie
	TriangleFree(abc);
	abc = Copy(mnk);
	TrianglePrint(abc, nazwa1);
	TrianglePrint(mnk, nazwa2);

	////zwolnienie pamieci
	//TriangleFree(mnk);
	//TriangleFree(abc);
	//abc = NULL;
	//mnk = NULL;

	//fclose(f);

}


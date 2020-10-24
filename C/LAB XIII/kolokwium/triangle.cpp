#include "triangle.h"
#pragma warning(disable:4996)

MY_TRIANGLE *TriangInit(MY_NODE *A, MY_NODE *B, MY_NODE *C) {
	MY_TRIANGLE *tr = (MY_TRIANGLE*)malloc(sizeof(MY_TRIANGLE));
	tr->Nodes = (MY_NODE*)malloc(3 * sizeof(MY_NODE));
	tr->Nodes[0] = *A;
	tr->Nodes[1] = *B;
	tr->Nodes[2] = *C;

	return tr;
}
void TriangleFree(MY_TRIANGLE *tr) {
	free(tr->Nodes);
	tr->Nodes = NULL;
	free(tr);
}
void TrianglePrint(MY_TRIANGLE *tr, char *nazwa_trojkatu) {
	printf("%s\n", nazwa_trojkatu);
	showNode(&tr->Nodes[0]);
	showNode(&tr->Nodes[1]);
	showNode(&tr->Nodes[2]);
	//printf("%lf\n", tr->Nodes[0].crd[0]);
	//printf("%lf\n", tr->Nodes[0].crd[1]);
	//printf("%lf\n", tr->Nodes[1].crd[0]);
	//printf("%lf\n", tr->Nodes[1].crd[1]);
	//printf("%lf\n", tr->Nodes[2].crd[0]);
	//printf("%lf\n", tr->Nodes[2].crd[1]);
}

MY_TRIANGLE *Copy(MY_TRIANGLE *other) {
	//if (dest) TriangleFree(dest);
	return TriangInit(&other->Nodes[0], &other->Nodes[1], &other->Nodes[2]);
}
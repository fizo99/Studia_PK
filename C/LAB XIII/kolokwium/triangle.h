#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"

struct MY_TRIANGLE {
	MY_NODE *Nodes;
};

MY_TRIANGLE *TriangInit(MY_NODE *A, MY_NODE *B, MY_NODE *C);
void TriangleFree(MY_TRIANGLE *tr);
void TrianglePrint(MY_TRIANGLE *tr, char *nazwa_trojkatu);
MY_TRIANGLE *Copy(MY_TRIANGLE *other); // overloaded = operator
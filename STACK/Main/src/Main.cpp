#include "headers/interface.h"
#pragma warning (disable:4996)

int main()
{
	OPTION op = PUSH;
	while (op >= PUSH && op <= STOP) {
		show_menu();
		scanf("%d", &op);
		switch (op)
		{
		case PUSH: push();
			break;
		case POP: pop();
			break;
		case CLEAR_STACK: clear();
			break;
		case SHOW_FIRST: show_top();
			break;
		case SHOW_STACK: show_stack();
			break;
		case FIND: find();
			break;
		case SAVE: save();
			break;
		case LOAD: load();
			break;
		case STOP: clear();
			return 0;
		default:
			printf("\n\tUndefined operation code\n");
		};
	}
}


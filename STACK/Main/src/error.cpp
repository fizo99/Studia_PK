#include "headers/error.h"

void raise_error(ERRORS err) {
	switch (err) {
	case SPEC_NOT_VALID:
		printf("\n\tEntered specialization is not valid\n");
		break;
	case SURNAME_NOT_VALID:
		printf("\n\tEntered surname is not valid\n");
		break;
	case YEAR_NOT_VALID:
		printf("\n\tEntered year is not valid\n");
		break;
	case FILE_OPEN_FAILED:
		printf("\n\tError occurred while opening the file\n");
		break;
	case FILE_CLOSE_FAILED:
		printf("\n\tError occurred while closing the file\n");
		break;
	case POP_FAILED:
		printf("\n\tError occurred while removing element from stack\n");
		break;
	case PUSH_FAILED:
		printf("\n\tError occurred while pushing element onto stack\n");
		break;
	case CLEAR_FAILED:
		printf("\n\tError occurred while clearing stack\n");
		break;
	case INPUT_NOT_VALID:
		printf("\n\tInput is not valid\n");
		break;
	}
}

void raise_communicate(COMMUNICATE comm) {
	switch (comm) {
	case STACK_ELEM_POPPED:
		printf("\n\tElement removed from stack\n");
		break;
	case STACK_ELEM_PUSHED:
		printf("\n\tElement pushed onto stack\n");
		break;
	case STACK_CLEARED:
		printf("\n\tStack cleared\n");
		break;
	case STACK_EMPTY:
		printf("\n\tStack is empty\n");
		break;
	case STACK_SAVED:
		printf("\n\tStack saved\n");
		break;
	case STACK_LOADED:
		printf("\n\tStack loaded\n");
		break;
	case FILE_EMPTY:
		printf("\n\tFile is empty\n");
		break;
	case NO_RESULTS:
		printf("\n\tNo results\n");
		break;
	}
}
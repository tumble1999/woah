#include <stdio.h>

#include "parse_cmd.h"
#include "apt.h"

int main(int argc, char const *argv[]) {
	if (DEBUG) {
		printf("Params: woah");
		for (int i = 1; i < argc; i++)
			printf(" %s", argv[i]);
		printf("\n");
	}

	struct Arguments args;

	if (parseArguments(&args, argc, argv)) {
		printf("Error parsing the arguments\n");
		return 1;
	}
	if (callApt(&args)) {
		printf("Invalid action.\n");
		return 1;
	}
	return 0;
}

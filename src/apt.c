#include "apt.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char
	*apt_refresh = "sudo apt update",
	*apt_upgrade = "sudo apt upgrade",
	*apt_install = "sudo apt install";

static void callCommand(const char *cmd)
{
	printf("> %s\n", cmd);
	//system(cmd);
}

int callApt(struct Arguments *args)
{
	int done = 0;
	if (args->op == OP_SYNC) // -S
	{
		if (args->params[PARAM_REFRESH] == 1) // -Sy
		{
			callCommand("sudo apt update");
			done++;
		}
		if (args->params[PARAM_UPGRADES] == 1) // -Su
		{
			callCommand("sudo apt upgrade");
			done++;
		}

		if (done == 0)
		{ // -S (targets)
			const char *apt_install = "sudo apt install";

			char *cmd = malloc((strlen(apt_install) + 1 + args->targets_len) * sizeof(char));
			sprintf(cmd, "%s %s", apt_install, args->targets);
			callCommand(cmd);
			done++;
		}
	}
	return done == 0;
}

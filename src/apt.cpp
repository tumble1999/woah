#include "apt.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>

#include <apt-pkg/cachefile.h>

const char
	*apt_update = "sudo apt update",
	*apt_upgrade = "sudo apt upgrade",
	*apt_fullupgrade = "sudo apt full-upgrade",
	*apt_install = "sudo apt install",
	*apt_remove = "sudo apt remove",
	*apt_search = "apt search";

static void callCommand(const char *cmd)
{
	printf("> %s\n", cmd);
	system(cmd);
}

int callApt(struct Arguments *args)
{
	int done = 0;
	if (args->op == OP_SYNC) // -S
	{
		printf("SEARCH: %d\n", args->params[PARAM_SEARCH]);
		if (done == 0 && args->params[PARAM_SEARCH] == 1) // -Ss
		{
			char *cmd = (char *)malloc((strlen(apt_search) + 1 + args->targets_len) * sizeof(char));
			sprintf(cmd, "%s %s", apt_search, args->targets);
			callCommand(cmd);
			done++;
		}
		if (done == 0)
		{
			if (args->params[PARAM_REFRESH] == 1) // -Sy
			{
				callCommand(apt_update);
				done++;
			}
			if (args->params[PARAM_UPGRADES] == 1) // -Su
			{
				callCommand(apt_upgrade);
				done++;
			}
		}

		if (done == 0) // -S (targets)
		{
			char *cmd = (char *)malloc((strlen(apt_install) + 1 + args->targets_len) * sizeof(char));
			sprintf(cmd, "%s %s", apt_install, args->targets);
			callCommand(cmd);
			done++;
		}
	}

	if (args->op == OP_REMOVE) // -R
	{
		if (done == 0) // -R (targets)
		{
			char *cmd = (char *)malloc((strlen(apt_remove) + 1 + args->targets_len) * sizeof(char));
			sprintf(cmd, "%s %s", apt_remove, args->targets);
			callCommand(cmd);
			done++;
		}
	}
	return done == 0;
}

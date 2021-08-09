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
	*apt_search = "apt search",
	*apt_cache_policy = "apt-cache policy",

	//Regex
		*get_version = "Installed: ([0-9.]*)";

void callCommand(const char *cmd)
{
	printf("> %s\n", cmd);
	system(cmd);
}

FILE *getCommand(const char *cmd)
{
	if (DEBUG)
		printf("> %s\n", cmd);
	return popen(cmd, "r");
}

void closeCommand(FILE *fd)
{
	pclose(fd);
}

char *getVersion(const char *tool)
{
	char *cmd = (char *)malloc((strlen(apt_cache_policy) + 1 + sizeof(tool)) * sizeof(char));
	sprintf(cmd, "%s %s", apt_cache_policy, tool);
	FILE *fp = getCommand(cmd);

	char line[256];
	int l = 2;
	while (l--)
	{
		fgets(line, sizeof(line), fp);
		//printf("%s",line);
	}
	closeCommand(fp);
	char *t = &line[0];

	char *version = line + sizeof(" Installed: ") / sizeof(char);

	return version;
}

int callApt(struct Arguments *args)
{
	int done = 0;
	if (args->op == OP_VERSION)
	{
		if (done == 0)
		{
			if (args->params[PARAM_WOAH] == 1)
			{
				printf("woah v%s\n", WOAH_VERSION);
				done++;
			}
			if (args->params[PARAM_DEPS] == 1)
			{
				printf("dpkg v%s", getVersion("dpkg"));
				done++;
			}
			if (args->params[PARAM_APT] == 1)
			{
				printf("apt v%s", getVersion("apt"));
				done++;
			}
			if (args->params[PARAM_APTFILE] == 1)
			{
				printf("apt-file v%s", getVersion("apt-file"));
				done++;
			}
		}

		// -V
		if (done == 0)
		{
			printf("woah v%s\n", WOAH_VERSION);
			printf("dpkg v%s", getVersion("dpkg"));
			printf("apt v%s", getVersion("apt"));
			printf("apt-file v%s", getVersion("apt-file"));
			done++;
		}
	}
	if (args->op == OP_SYNC)
	{ // -S
		if (done == 0 && args->params[PARAM_SEARCH] == 1)
		{ // -Ss
			char *cmd = (char *)malloc((strlen(apt_search) + 1 + args->targets_len) * sizeof(char));
			sprintf(cmd, "%s %s", apt_search, args->targets);
			callCommand(cmd);
			done++;
		}
		if (done == 0)
		{
			if (args->params[PARAM_REFRESH] == 1)
			{ // -Sy
				callCommand(apt_update);
				done++;
			}
			if (args->params[PARAM_UPGRADES] == 1)
			{ // -Su
				callCommand(apt_upgrade);
				done++;
			}
		}

		if (done == 0)
		{ // -S (targets)
			char *cmd = (char *)malloc((strlen(apt_install) + 1 + args->targets_len) * sizeof(char));
			sprintf(cmd, "%s %s", apt_install, args->targets);
			callCommand(cmd);
			done++;
		}
	}

	if (args->op == OP_REMOVE)
	{ // -R
		if (done == 0)
		{ // -R (targets)
			char *cmd = (char *)malloc((strlen(apt_remove) + 1 + args->targets_len) * sizeof(char));
			sprintf(cmd, "%s %s", apt_remove, args->targets);
			callCommand(cmd);
			done++;
		}
	}
	return done == 0;
}

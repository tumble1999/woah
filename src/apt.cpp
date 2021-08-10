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
	*apt_file_search="apt-file search",
	*apt_file_list="apt-file list",

	//Regex
		*get_version = "Installed: ([0-9.]*)";

int callCommand(const char *cmd)
{
	printf("> %s\n", cmd);
	return system(cmd);
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
	if (args->params[PARAM_HELP] == 1)
	{
		if (done == 0 && args->op == OP_FILES)
		{
			printf("usage:  woah {-F --files} [option] <packages>\n\
options:\n\
  -l, --list <packages> List files in packages\n\
");
			done++;
		}
		if (done == 0 && args->op == OP_REMOVE)
		{
			printf("usage:  woah {-R --remove} <packages>\n\
");
			done++;
		}
		if (done == 0 && args->op == OP_SYNC)
		{
			printf("usage:  woah {-S --sync} [options] <packages>\n\
options:\n\
  -s, --search <regex> search in package descriptions\n\
  -u, --upgrades       upgrade the system by installing/upgrading packages\n\
  -y, --refresh        update list of available packages\n\
");
			done++;
		}
		if (done == 0 && args->op == OP_VERSION)
		{
			printf("usage:  woah {-V, --version} <options> <packages>\n\
options:\n\
  -q, --quiet      hide package name\n\
packages:\n\
  apt              apt version info\n\
  dpkg             dpkg version info\n\
  apt-file         apt-file version info\n\
  woah             woah version info\n\
");
			done++;
		}
		if (done == 0)
		{
			printf("usage:  woah <operation> [...]\n\
operations:\n\
    woah {-h --help}\n\
    woah {-V --version} [options] [packages]\n\
    woah {-F --files} [option] <packages>\n\
    woah {-R --remove}             <packages>\n\
    woah {-S --sync}    [options]  [packages]\n\
\n\
use 'woah {-h --help}' with an operation for available options\n\
");
			done++;
		}
	}

	if (args->op == OP_VERSION)
	{
		if (done == 0)
		{
			for (int i = 0; i < args->target_count; i++)
			{
				if (strcmp(args->targets_arr[i], "woah") == 0)
				{
					if (args->params[PARAM_QUIET] == 1)
					{
						printf("%s\n", WOAH_VERSION);
					}
					else
					{
						printf("woah %s\n", WOAH_VERSION);
					}
				}
				else
				{
					if (args->params[PARAM_QUIET] == 1)
					{
						printf("%s", getVersion(args->targets_arr[i]));
					}
					else
					{
						printf("%s %s", args->targets_arr[i], getVersion(args->targets_arr[i]));
					}
				}
				done++;
			}
		}

		// -V
		if (done == 0)
		{

			if (args->params[PARAM_QUIET] == 1)
			{
				printf("%s\n", WOAH_VERSION);
				printf("%s", getVersion("dpkg"));
				printf("%s", getVersion("apt"));
				printf("%s", getVersion("apt-file"));
			}
			else
			{
				printf("woah %s\n", WOAH_VERSION);
				printf("dpkg %s", getVersion("dpkg"));
				printf("apt %s", getVersion("apt"));
				printf("apt-file %s", getVersion("apt-file"));
			}
		}
		done++;
	}
	
	if(args->op == OP_FILES) { // -Fl
		if(done==0 && args->params[PARAM_LIST]==1) {// -Fl (packages)
			char *cmd = (char *)malloc((strlen(apt_file_list) + 1 + args->targets_len) * sizeof(char));
			sprintf(cmd, "%s %s", apt_file_list, args->targets);
			callCommand(cmd);
			done++;
		}
		if(done==0) {// -F (targets)
			char *cmd = (char *)malloc((strlen(apt_file_search) + 1 + args->targets_len) * sizeof(char));
			sprintf(cmd, "%s %s", apt_file_search, args->targets);
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
	return done == 0;
}

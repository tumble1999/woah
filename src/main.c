#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum Operation
{
	OP_NULL,
	OP_VERSION,
	OP_DATABASE,
	OP_FILES,
	OP_QUERY,
	OP_REMOVE,
	OP_SYNC,
	OP_DEPTEST,
	OP_UPGRADE
};

enum Param
{
	PARAM_CHECK,	//k
	PARAM_REFRESH,	//y
	PARAM_PRINT,	//p
	PARAM_SEARCH,	//s
	PARAM_LIST,		//l
	PARAM_GROUPS,	//g
	PARAM_INFO,		//i
	PARAM_CLEAN,	//c
	PARAM_UPGRADES, //u
	NUM_PARAMS
};

struct Arguments
{
	enum Operation op;
	unsigned int params[NUM_PARAMS];
	const char **targets_arr;
	unsigned int target_count;
	const char *targets;
	unsigned int targets_len;
} args;

void checkOPExists()
{
	if (args.op != OP_NULL)
	{
		printf("only one operation may be used at a time\n");
		exit(-1);
	}
}

int addOperation(const char *p)
{
	if (strcmp(p, "V") == 0 || strcmp(p, "version") == 0)
	{
		checkOPExists();
		args.op = OP_VERSION;
		printf("Operation: VERSION\n");
		return 0;
	}
	if (strcmp(p, "D") == 0 || strcmp(p, "database") == 0)
	{
		checkOPExists();
		args.op = OP_DATABASE;
		printf("Operation: DATABASE\n");
		return 0;
	}
	if (strcmp(p, "F") == 0 || strcmp(p, "files") == 0)
	{
		checkOPExists();
		args.op = OP_FILES;
		printf("Operation: FILES\n");
		return 0;
	}
	if (strcmp(p, "Q") == 0 || strcmp(p, "query") == 0)
	{
		checkOPExists();
		args.op = OP_QUERY;
		printf("Operation: QUERY\n");
		return 0;
	}
	if (strcmp(p, "R") == 0 || strcmp(p, "remove") == 0)
	{
		checkOPExists();
		args.op = OP_REMOVE;
		printf("Operation: REMOVE\n");
		return 0;
	}
	if (strcmp(p, "S") == 0 || strcmp(p, "sync") == 0)
	{
		checkOPExists();
		args.op = OP_SYNC;
		printf("Operation: SYNC\n");
		return 0;
	}
	if (strcmp(p, "T") == 0 || strcmp(p, "deptest") == 0)
	{
		checkOPExists();
		args.op = OP_DEPTEST;
		printf("Operation: DEPTEST\n");
		return 0;
	}
	if (strcmp(p, "U") == 0 || strcmp(p, "upgrade") == 0)
	{
		checkOPExists();
		args.op = OP_UPGRADE;
		printf("Operation: UPGRADE\n");
		return 0;
	}
	return 1;
}

int addParam(const char *p)
{
	if (strcmp(p, "k") == 0 || strcmp(p, "check") == 0)
	{
		args.params[PARAM_CHECK]++;
		printf("Param: CHECK\n");
		return 0;
	}
	if (strcmp(p, "y") == 0 || strcmp(p, "refresh") == 0)
	{
		args.params[PARAM_REFRESH]++;
		printf("Param: REFRESH\n");
		return 0;
	}
	if (strcmp(p, "p") == 0 || strcmp(p, "print") == 0)
	{
		args.params[PARAM_PRINT]++;
		printf("Param: PRINT\n");
		return 0;
	}
	if (strcmp(p, "s") == 0 || strcmp(p, "search") == 0)
	{
		args.params[PARAM_SEARCH]++;
		printf("Param: SEARCH\n");
		return 0;
	}
	if (strcmp(p, "l") == 0 || strcmp(p, "list") == 0)
	{
		args.params[PARAM_LIST]++;
		printf("Param: LIST\n");
		return 0;
	}
	if (strcmp(p, "g") == 0 || strcmp(p, "groups") == 0)
	{
		args.params[PARAM_GROUPS]++;
		printf("Param: GROUPS\n");
		return 0;
	}
	if (strcmp(p, "i") == 0 || strcmp(p, "info") == 0)
	{
		args.params[PARAM_INFO]++;
		printf("Param: INFO\n");
		return 0;
	}
	if (strcmp(p, "c") == 0 || strcmp(p, "clean") == 0)
	{
		args.params[PARAM_CLEAN]++;
		printf("Param: CLEAN\n");
		return 0;
	}
	if (strcmp(p, "u") == 0 || strcmp(p, "upgrades") == 0)
	{
		args.params[PARAM_UPGRADES]++;
		printf("Param: UPGRADES\n");
		return 0;
	}
	return 1;
}

int addTarget(const char *p)
{
	args.targets_arr[args.target_count] = p;
	printf("Target: %s\n", p);
	args.target_count++;
	args.targets_len += strlen(p);
	return 0;
}

int parseDoubleDashed(const char *p)
{
	if (!addOperation(p))
		return 0;
	if (!addParam(p))
		return 0;

	printf("Unsuported argument: -%s\n", p);
	return 1;
}

int parseSingleDashed(const char *p)
{
	int l = strlen(p);

	for (int i = 0; i < l; i++)
	{
		const char c[2] = {p[i], '\0'};
		if (!addOperation(c))
			continue;
		if (!addParam(c))
			continue;

		printf("Unsuported argument: --%c\n", p[i]);
		return 1;
	}
	return 0;
}

int parseRegular(const char *p)
{
	if (!addTarget(p))
		return 0;

	printf("Unsuported argument: %s\n", p);
	return 1;
}

void callAPT(const char *cmd)
{
	printf("> %s\n", cmd);
	//system(cmd);
}

int main(int argc, char const *argv[])
{
	printf("Params: woah");
	for (int i = 1; i < argc; i++)
		printf(" %s", argv[i]);
	printf("\n");
	args.op = OP_NULL;
	args.targets_arr = malloc(argc * sizeof(const char *));

	for (int i = 1; i < argc; i++)
	{
		const char *p = argv[i];

		if (p[0] == '-')
		{
			if (p[1] == '-')
			{
				// --A
				if (parseDoubleDashed(p + 2))
					exit(1);
			}
			else
			{
				// -A
				if (parseSingleDashed(p + 1))
					exit(1);
			}
		}
		else
		{
			// A
			if (parseRegular(p))
				exit(1);
		}
	}

	//MergeTargets
	args.targets_len +=args.target_count;// Add spaces
	args.targets = malloc(args.targets_len * sizeof(char));
	int offset = 0;
	for (int i = 0; i < args.target_count; i++)
	{
		int left = args.targets_len - offset,
			written = snprintf((char*)args.targets + offset, left, "%s ", args.targets_arr[i]);
			if(left<written)break;
			offset+=written;
	}
	printf("Targets: %s\n",args.targets);

	int done = 0;
	if (args.op == OP_SYNC) // -S
	{
		if (args.params[PARAM_REFRESH] == 1) // -Sy
		{
			callAPT("sudo apt update");
			done++;
		}
		if (args.params[PARAM_UPGRADES] == 1) // -Su
		{
			callAPT("sudo apt upgrade");
			done++;
		}
		
		if(done==0) { // -S (targets)
			const char* apt_install = "sudo apt install";
			
			char* cmd = malloc((strlen(apt_install)+1+args.targets_len)*sizeof(char));
			sprintf(cmd, "%s %s",apt_install,args.targets);
			callAPT(cmd);
			done++;
		}
	}

	if (!done)
	{
		printf("Invalid action.\n");
		return 1;
	}
	return 0;
}

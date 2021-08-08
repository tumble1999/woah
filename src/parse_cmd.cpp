#include "parse_cmd.h"

#include <stdio.h>
#include <string.h>
#include <cstdlib>

void checkOPExists(struct Arguments *args)
{
	if (args->op != OP_NULL)
	{
		printf("only one operation may be used at a time\n");
		exit(-1);
	}
}

int addOperation(struct Arguments *args, const char *p)
{
	if (strcmp(p, "V") == 0 || strcmp(p, "version") == 0)
	{
		checkOPExists(args);
		args->op = OP_VERSION;
		printf("Operation: VERSION\n");
		return 0;
	}
	if (strcmp(p, "D") == 0 || strcmp(p, "database") == 0)
	{
		checkOPExists(args);
		args->op = OP_DATABASE;
		printf("Operation: DATABASE\n");
		return 0;
	}
	if (strcmp(p, "F") == 0 || strcmp(p, "files") == 0)
	{
		checkOPExists(args);
		args->op = OP_FILES;
		printf("Operation: FILES\n");
		return 0;
	}
	if (strcmp(p, "Q") == 0 || strcmp(p, "query") == 0)
	{
		checkOPExists(args);
		args->op = OP_QUERY;
		printf("Operation: QUERY\n");
		return 0;
	}
	if (strcmp(p, "R") == 0 || strcmp(p, "remove") == 0)
	{
		checkOPExists(args);
		args->op = OP_REMOVE;
		printf("Operation: REMOVE\n");
		return 0;
	}
	if (strcmp(p, "S") == 0 || strcmp(p, "sync") == 0)
	{
		checkOPExists(args);
		args->op = OP_SYNC;
		printf("Operation: SYNC\n");
		return 0;
	}
	if (strcmp(p, "T") == 0 || strcmp(p, "deptest") == 0)
	{
		checkOPExists(args);
		args->op = OP_DEPTEST;
		printf("Operation: DEPTEST\n");
		return 0;
	}
	if (strcmp(p, "U") == 0 || strcmp(p, "upgrade") == 0)
	{
		checkOPExists(args);
		args->op = OP_UPGRADE;
		printf("Operation: UPGRADE\n");
		return 0;
	}
	return 1;
}

int addParam(struct Arguments *args, const char *p)
{
	if (strcmp(p, "k") == 0 || strcmp(p, "check") == 0)
	{
		args->params[PARAM_CHECK]++;
		printf("Param: CHECK\n");
		return 0;
	}
	if (strcmp(p, "y") == 0 || strcmp(p, "refresh") == 0)
	{
		args->params[PARAM_REFRESH]++;
		printf("Param: REFRESH\n");
		return 0;
	}
	if (strcmp(p, "p") == 0 || strcmp(p, "print") == 0)
	{
		args->params[PARAM_PRINT]++;
		printf("Param: PRINT\n");
		return 0;
	}
	if (strcmp(p, "s") == 0 || strcmp(p, "search") == 0)
	{
		args->params[PARAM_SEARCH]++;
		printf("Param: SEARCH\n");
		return 0;
	}
	if (strcmp(p, "l") == 0 || strcmp(p, "list") == 0)
	{
		args->params[PARAM_LIST]++;
		printf("Param: LIST\n");
		return 0;
	}
	if (strcmp(p, "g") == 0 || strcmp(p, "groups") == 0)
	{
		args->params[PARAM_GROUPS]++;
		printf("Param: GROUPS\n");
		return 0;
	}
	if (strcmp(p, "i") == 0 || strcmp(p, "info") == 0)
	{
		args->params[PARAM_INFO]++;
		printf("Param: INFO\n");
		return 0;
	}
	if (strcmp(p, "c") == 0 || strcmp(p, "clean") == 0)
	{
		args->params[PARAM_CLEAN]++;
		printf("Param: CLEAN\n");
		return 0;
	}
	if (strcmp(p, "u") == 0 || strcmp(p, "upgrades") == 0)
	{
		args->params[PARAM_UPGRADES]++;
		printf("Param: UPGRADES\n");
		return 0;
	}
	return 1;
}

int addTarget(struct Arguments *args, const char *p)
{
	args->targets_arr[args->target_count] = p;
	printf("Target: %s\n", p);
	args->target_count++;
	args->targets_len += strlen(p);
	return 0;
}

int parseDoubleDashed(struct Arguments *args, const char *p)
{
	if (!addOperation(args, p))
		return 0;
	if (!addParam(args, p))
		return 0;

	printf("Unsupported argument: --%s\n", p);
	return 1;
}

int parseSingleDashed(struct Arguments *args, const char *p)
{
	int l = strlen(p);

	for (int i = 0; i < l; i++)
	{
		const char c[2] = {p[i], '\0'};
		if (!addOperation(args, c))
			continue;
		if (!addParam(args, c))
			continue;

		printf("Unsupported argument: -%c\n", p[i]);
		return 1;
	}
	return 0;
}

int parseRegular(struct Arguments *args, const char *p)
{
	if (!addTarget(args, p))
		return 0;

	printf("Unsupported argument: %s\n", p);
	return 1;
}

int parseArguments(struct Arguments *args, int argc, char const *argv[])
{
	args->op = OP_NULL;
	args->target_count = 0;
	args->targets_arr = (const char **)malloc(argc * sizeof(const char *));
	args->targets_len = 0;
	args->params = (unsigned int *)malloc(sizeof(int) * NUM_PARAMS);

	for (int i = 1; i < argc; i++)
	{
		const char *p = argv[i];

		if (p[0] == '-')
		{
			if (p[1] == '-' && strlen(p) > 2)
			{
				if (parseDoubleDashed(args, p + 2))
					return 1;
			}
			else
			{
				if (parseSingleDashed(args, p + 1))
					return 1;
			}
		}
		else
		{
			// A
			if (parseRegular(args, p))
				return 1;
		}
	}

	//MergeTargets
	args->targets_len += args->target_count; // Add spaces
	args->targets = (const char *)malloc(args->targets_len * sizeof(char));
	int offset = 0;
	for (int i = 0; i < args->target_count; i++)
	{
		int left = args->targets_len - offset,
			written = snprintf((char *)args->targets + offset, left, "%s ", args->targets_arr[i]);
		if (left < written)
			break;
		offset += written;
	}
	printf("Targets: %s\n", args->targets);

	return 0;
}

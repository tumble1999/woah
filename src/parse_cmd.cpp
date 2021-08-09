#include "parse_cmd.h"

#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <cstdarg>

void checkOPExists(struct Arguments *args)
{
	if (args->op != OP_NULL)
	{
		printf("only one operation may be used at a time\n");
		exit(-1);
	}
}

int lookupOperation(struct Arguments *args, const char *p, const char *name, Operation op, int aliasc, ...)
{
	va_list valist;
	va_start(valist, aliasc);
	for (int i = 0; i < aliasc; i++)
	{
		if (strcmp(p, va_arg(valist, const char *)) == 0)
		{
			checkOPExists(args);
			args->op = op;
			if (DEBUG)
				printf("Operation: %s\n", name);
			return 1;
		}
	}
	return 0;
}

int lookupParam(struct Arguments *args, const char *p, const char *name, Param param, int aliasc, ...)
{
	va_list valist;
	va_start(valist, aliasc);
	for (int i = 0; i < aliasc; i++)
	{
		if (strcmp(p, va_arg(valist, const char *)) == 0)
		{
			args->params[param]++;
			if (DEBUG)
				printf("Param: %s\n", name);
			return 1;
		}
	}
	return 0;
}

int addOperation(struct Arguments *args, const char *p)
{
	if (
		lookupOperation(args, p, "VERSION", OP_VERSION, 2, "V", "version") ||
		lookupOperation(args, p, "DATABASE", OP_DATABASE, 2, "D", "database") ||
		lookupOperation(args, p, "FILES", OP_FILES, 2, "F", "files") ||
		lookupOperation(args, p, "QUERY", OP_QUERY, 2, "Q", "query") ||
		lookupOperation(args, p, "REMOVE", OP_REMOVE, 2, "R", "remove") ||
		lookupOperation(args, p, "SYNC", OP_SYNC, 2, "S", "sync") ||
		lookupOperation(args, p, "DEPTEST", OP_DEPTEST, 2, "T", "deptest") ||
		lookupOperation(args, p, "VERSION", OP_UPGRADE, 2, "U", "upgrade"))
		return 0;
	return 1;
}

int addParam(struct Arguments *args, const char *p)
{
	if (
		lookupParam(args, p, "CLEAN", PARAM_CLEAN, 2, "c", "clean") ||
		lookupParam(args, p, "DEPS", PARAM_DEPS, 2, "d", "deps") ||
		lookupParam(args, p, "GROUPS", PARAM_GROUPS, 2, "g", "groups") ||
		lookupParam(args, p, "HELP", PARAM_HELP, 2, "h", "help") ||
		lookupParam(args, p, "INFO", PARAM_INFO, 2, "i", "info") ||
		lookupParam(args, p, "CHECK", PARAM_CHECK, 2, "p", "check") ||
		lookupParam(args, p, "QUIET", PARAM_QUIET, 2, "q", "quiet") ||
		lookupParam(args, p, "LIST", PARAM_LIST, 2, "l", "list") ||
		lookupParam(args, p, "PRINT", PARAM_PRINT, 2, "p", "print") ||
		lookupParam(args, p, "SEARCH", PARAM_SEARCH, 2, "s", "search") ||
		lookupParam(args, p, "UPGRADES", PARAM_UPGRADES, 2, "u", "upgrades") ||
		lookupParam(args, p, "REFRESH", PARAM_REFRESH, 2, "y", "refresh"))
		return 0;
	return 1;
}

int addTarget(struct Arguments *args, const char *p)
{
	args->targets_arr[args->target_count] = p;
	if (DEBUG)
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
	if (args->targets_len > 0 && DEBUG)
		printf("Targets: %s\n", args->targets);

	return 0;
}

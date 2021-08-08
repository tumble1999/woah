#pragma once

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
	unsigned int *params;
	const char **targets_arr;
	unsigned int target_count;
	const char *targets;
	unsigned int targets_len;
};

#pragma once

#define DEBUG false

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
	PARAM_CLEAN,	//c
	PARAM_DEPS,		//d
	PARAM_EXPLICIT, //e
	PARAM_GROUPS,	//g
	PARAM_HELP,		//h
	PARAM_INFO,		//i
	PARAM_CHECK,	//k
	PARAM_LIST,		//l
	PARAM_PRINT,	//p
	PARAM_QUIET,	//q
	PARAM_SEARCH,	//s
	PARAM_UPGRADES, //u
	PARAM_REFRESH,	//y
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

struct dpkg_entry
{
	enum package_selection
	{
		SEL_UNKNOWN,
		SEL_INSTALL,
		SEL_HOLD,
		SEL_REMOVE,
		SEL_PURGE
	} select;
	enum package_status
	{
		STAT_NOTINSTALLED,
		STAT_CONFIGFILES,
		STAT_HALFINSTALLED,
		STAT_UNPACKED,
		STAT_HALFCONFIGURED,
		STAT_TRIGGERSAWAITING,
		STAT_TRIGGERSPENDING,
		STAT_INSTALLED
	} status;
	int reinstall_req;
	char *name, *version, *arch, *description;
};

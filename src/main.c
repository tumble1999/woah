#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum Operation {
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

enum Param {
	PARAM_CHECK,//k
	PARAM_REFRESH,//y
	PARAM_PRINT,//p
	PARAM_SEARCH,//s
	PARAM_LIST,//l
	PARAM_GROUPS,//g
	PARAM_INFO,//i
	PARAM_CLEAN,//c
	PARAM_UPGRADES,//u
	NUM_PARAMS
};

struct Arguments {
	enum Operation operation;
	unsigned int target_count;
	unsigned int params[NUM_PARAMS];
	char** targets;
} arguments;

void checkOPExists() {
	if(arguments.operation!=OP_NULL) {
		printf("only one operation may be used at a time\n");
		exit(-1);
	}
}

int parseParam(const char* p) {
	if(strcmp(p,"k")==0||strcmp(p,"check")==0) {
		arguments.params[PARAM_CHECK]++;
		printf("Param: CHECK\n");
		return 0;
	}
	if(strcmp(p,"y")==0||strcmp(p,"refresh")==0) {
		arguments.params[PARAM_REFRESH]++;
		printf("Param: REFRESH\n");
		return 0;
	}
	if(strcmp(p,"p")==0||strcmp(p,"print")==0) {
		arguments.params[PARAM_PRINT]++;
		printf("Param: PRINT\n");
		return 0;
	}
	if(strcmp(p,"s")==0||strcmp(p,"search")==0) {
		arguments.params[PARAM_SEARCH]++;
		printf("Param: SEARCH\n");
		return 0;
	}
	if(strcmp(p,"l")==0||strcmp(p,"list")==0) {
		arguments.params[PARAM_LIST]++;
		printf("Param: LIST\n");
		return 0;
	}
	if(strcmp(p,"g")==0||strcmp(p,"groups")==0) {
		arguments.params[PARAM_GROUPS]++;
		printf("Param: GROUPS\n");
		return 0;
	}
	if(strcmp(p,"i")==0||strcmp(p,"info")==0) {
		arguments.params[PARAM_INFO]++;
		printf("Param: INFO\n");
		return 0;
	}
	if(strcmp(p,"c")==0||strcmp(p,"clean")==0) {
		arguments.params[PARAM_CLEAN]++;
		printf("Param: CLEAN\n");
		return 0;
	}
	if(strcmp(p,"u")==0||strcmp(p,"upgrades")==0) {
		arguments.params[PARAM_UPGRADES]++;
		printf("Param: UPGRADES\n");
		return 0;
	}
	return 1;
}

int parseOperation(const char* p) {
	if(strcmp(p,"V")==0||strcmp(p,"version")==0) {
		checkOPExists();
		arguments.operation = OP_VERSION;
		printf("Operation: VERSION\n");
		return 0;
	}
	if(strcmp(p,"D")==0||strcmp(p,"database")==0) {
		checkOPExists();
		arguments.operation = OP_DATABASE;
		printf("Operation: DATABASE\n");
		return 0;
	}
	if(strcmp(p,"F")==0||strcmp(p,"files")==0) {
		checkOPExists();
		arguments.operation = OP_FILES;
		printf("Operation: FILES\n");
		return 0;
	}
	if(strcmp(p,"Q")==0||strcmp(p,"query")==0) {
		checkOPExists();
		arguments.operation = OP_QUERY;
		printf("Operation: QUERY\n");
		return 0;
	}
	if(strcmp(p,"R")==0||strcmp(p,"remove")==0) {
		checkOPExists();
		arguments.operation = OP_REMOVE;
		printf("Operation: REMOVE\n");
		return 0;
	}
	if(strcmp(p,"S")==0||strcmp(p,"sync")==0) {
		checkOPExists();
		arguments.operation = OP_SYNC;
		printf("Operation: SYNC\n");
		return 0;
	}
	if(strcmp(p,"T")==0||strcmp(p,"deptest")==0) {
		checkOPExists();
		arguments.operation = OP_DEPTEST;
		printf("Operation: DEPTEST\n");
		return 0;
	}
	if(strcmp(p,"U")==0||strcmp(p,"upgrade")==0) {
		checkOPExists();
		arguments.operation = OP_UPGRADE;
		printf("Operation: UPGRADE\n");
		return 0;
	}
	return 1;
}


int parseDoubleDashed(const char* p) {
	if(!parseOperation(p)) return 0;
	if(!parseParam(p)) return 0;
		
	printf("Unsuported argument: -%s\n",p);
	return 1;
}

int parseSingleDashed(const char* p) {
	int l = strlen(p);
	
	for (int i = 0; i < l; i++)
	{
		const char c[2] = {p[i],'\0'};
		if(!parseOperation(c)) continue;
		if(!parseParam(c)) continue;
		
		printf("Unsuported argument: --%c\n",p[i]);
		return 1;
	}
	return 0;
}

int parseRegular(const char* p) {
	printf("Regular: %s\n",p);
	return 1;
}

int main(int argc, char const *argv[])
{
	printf("Params: woah");
	for (int i = 1; i < argc; i++) printf(" %s",argv[i]);
	printf("\n");
	arguments.operation=OP_NULL;
	
	for (int i = 1; i < argc; i++)
	{
		const char* p = argv[i];
		
		if(p[0]=='-') {
			if(p[1]=='-') {
				// --A
				if(parseDoubleDashed(p+2))exit(1);
			} else {
				// -A
				if(parseSingleDashed(p+1))exit(1);
			}
		} else {
			// 
			if(parseRegular(p))exit(1);
		}
	}

	return 0;
}

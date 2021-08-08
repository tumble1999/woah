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

struct Arguments {
	enum Operation operation;
	unsigned int param_count,target_count;
	char* params;
	char** targets;
} arguments;

void checkOPExists() {
	if(arguments.operation!=OP_NULL) {
		printf("only one operation may be used at a time\n");
		exit(-1);
	}
}

void addParam(char p) {
	argument.params
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
	printf("Double Dashed: %s\n",p);
	if(!parseOperation(p)) return 0;
		
	//TODO: Parse regular args
		
	printf("Unsuported argument: -%s\n",p);
	return 1;
}

int parseSingleDashed(const char* p) {
	printf("Dashed: %s\n",p);
	int l = strlen(p);
	
	for (int i = 0; i < l; i++)
	{
		const char c[2] = {p[i],'\0'};
		printf("%c\n",p[i]);
		if(!parseOperation(c)) continue;
		printf("Unsuported argument: --%c\n",p[i]);
		return 1;
	}
	return 0;
}

int parseRegular(const char* p) {
	printf("Regular: %s\n",p);
	return 0;
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

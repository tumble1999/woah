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
	*dpkg_l = "dpkg -l",
	*list_manual = "apt-mark showmanual",
	*list_deps = "apt-mark showauto",
	*apt_file_search="apt-file search",
	*apt_file_list="apt-file list",
	*apt_file_update = "sudo apt-file update",

	//Regex
	*get_version = "Installed: ([0-9.]*)";

int callCommand(const char *cmd) {
	printf("> %s\n", cmd);
	return system(cmd);
}

FILE *getCommand(const char *cmd) {
	if (DEBUG) {
		printf("> %s\n", cmd);
	}
	return popen(cmd, "r");
}

void closeCommand(FILE *fd) {
	pclose(fd);
}

char *getVersion(const char *tool) {
	char *cmd = (char *)malloc((strlen(apt_cache_policy) + 1 + sizeof(tool)) * sizeof(char));
	sprintf(cmd, "%s %s", apt_cache_policy, tool);
	FILE *fp = getCommand(cmd);

	char line[256];
	int l = 2;
	while (l--) {
		fgets(line, sizeof(line), fp);
		//printf("%s",line);
	}
	closeCommand(fp);
	char *t = &line[0];

	char *version = line + sizeof(" Installed: ") / sizeof(char);

	return version;
}

int getList(const char *cmd, char **list) {
	FILE *fp = getCommand(cmd);
	char line[256];
	int i = 0;
	int c = 0;
	while (fgets(line, sizeof(line), fp)) {
		c = 0;
		list[i] = (char *)malloc(sizeof(line));
		while (line[c] != '\n') {
			list[i][c] = line[c];
			c++;
		}
		list[i][c] = '\0';
		//printf("compare_list: %s\n", list[i]);
		i++;
	}

	closeCommand(fp);

	return i;
}

int callApt(struct Arguments *args) {
	int done = 0;
	if (args->params[PARAM_HELP] == 1) {
		if (done == 0 && args->op == OP_FILES) {
			printf("usage:  woah {-F --files} [option] <packages>\n\
options:\n\
  -y, --refresh <packages> Fetch Contents files from apt-sources\n\
  -l, --list <packages> List files in packages\n\
");
			done++;
		}
		if (done == 0 && args->op == OP_QUERY) {
			printf("usage:  woah {-Q --query} [options]\n\
options:\n\
  -d, --deps           Print the list of automatically installed packages\n\
  -e, --explicit       Print the list of manually installed packages\n\
");
			done++;
		}
		if (done == 0 && args->op == OP_REMOVE) {
			printf("usage:  woah {-R --remove} <packages>\n\
");
			done++;
		}
		if (done == 0 && args->op == OP_SYNC) {
			printf("usage:  woah {-S --sync} [options] <packages>\n\
options:\n\
  -s, --search <regex> search in package descriptions\n\
  -u, --upgrades       upgrade the system by installing/upgrading packages\n\
  -y, --refresh        update list of available packages\n\
");
			done++;
		}
		if (done == 0 && args->op == OP_VERSION) {
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
		if (done == 0) {
			printf("usage:  woah <operation> [...]\n\
operations:\n\
    woah {-h --help}\n\
    woah {-V --version} <options> <packages>\n\
    woah {-F --files} [option] <packages>\n\
    woah {-Q --query}   [options]\n\
    woah {-R --remove}            <packages>\n\
    woah {-S --sync}    [options] <packages>\n\
\n\
use 'woah {-h --help}' with an operation for available options\n\
");
			done++;
		}
	}

	if (args->op == OP_VERSION) {
		if (done == 0) {
			for (int i = 0; i < args->target_count; i++) {
				if (strcmp(args->targets_arr[i], "woah") == 0) {
					if (args->params[PARAM_QUIET] == 1) {
						printf("%s\n", WOAH_VERSION);
					} else {
						printf("woah %s\n", WOAH_VERSION);
					}
				} else {
					if (args->params[PARAM_QUIET] == 1) {
						printf("%s", getVersion(args->targets_arr[i]));
					} else {
						printf("%s %s", args->targets_arr[i], getVersion(args->targets_arr[i]));
					}
				}
				done++;
			}
		}

		// -V
		if (done == 0) {

			if (args->params[PARAM_QUIET] == 1) {
				printf("%s\n", WOAH_VERSION);
				printf("%s", getVersion("dpkg"));
				printf("%s", getVersion("apt"));
				printf("%s", getVersion("apt-file"));
			} else {
				printf("woah %s\n", WOAH_VERSION);
				printf("dpkg %s", getVersion("dpkg"));
				printf("apt %s", getVersion("apt"));
				printf("apt-file %s", getVersion("apt-file"));
			}
		}
		done++;
	}

	if (args->op == OP_QUERY) {
		if (done == 0 && args->params[PARAM_EXPLICIT] && args->params[PARAM_DEPS]) {
			printf("error: invalid option: '--deps' and '--explicit' may not be used together\n");
			done++;
		}
		if (done == 0) {
			int compare_count = 0;
			char **compare_list = (char **)malloc(256 * 256 * sizeof(char *));
			if (args->params[PARAM_EXPLICIT] == 1) {
				compare_count = getList(list_manual, compare_list);
			}
			if (args->params[PARAM_DEPS] == 1) {
				compare_count = getList(list_deps, compare_list);
			}

			FILE *fp = getCommand(dpkg_l);
			char line[256];
			int l = 6;
			while (l--) {
				fgets(line, sizeof(line), fp);
			}

			while (fgets(line, sizeof(line), fp)) {
				dpkg_entry entry{};
				switch (line[0]) {
					case 'i':
						entry.select = dpkg_entry::SEL_INSTALL;
						break;
					case 'h':
						entry.select = dpkg_entry::SEL_HOLD;
						break;
					case 'r':
						entry.select = dpkg_entry::SEL_REMOVE;
						break;
					case 'p':
						entry.select = dpkg_entry::SEL_PURGE;
						break;
					case 'u':
					default:
						entry.select = dpkg_entry::SEL_UNKNOWN;
						break;
				}

				switch (line[1]) {
					case 'n':
						entry.status = dpkg_entry::STAT_NOTINSTALLED;
						break;
					case 'c':
						entry.status = dpkg_entry::STAT_CONFIGFILES;
						break;
					case 'H':
						entry.status = dpkg_entry::STAT_HALFINSTALLED;
						break;
					case 'U':
						entry.status = dpkg_entry::STAT_UNPACKED;
						break;
					case 'F':
						entry.status = dpkg_entry::STAT_HALFCONFIGURED;
						break;
					case 'W':
						entry.status = dpkg_entry::STAT_TRIGGERSAWAITING;
						break;
					case 't':
						entry.status = dpkg_entry::STAT_TRIGGERSPENDING;
						break;
					case 'i':
						entry.status = dpkg_entry::STAT_INSTALLED;
						break;
				}
				entry.reinstall_req = 0;
				if (line[2] == 'R') {
					entry.reinstall_req = 1;
				}

				int length = sizeof(line) / sizeof(char);
				entry.name = (char *)malloc(sizeof(line));
				entry.version = (char *)malloc(sizeof(line));
				entry.arch = (char *)malloc(sizeof(line));
				entry.description = (char *)malloc(sizeof(line));
				int property = 0, progress = 0;

				//printf("[0,1,2,3,4,5]: \"%c%c%c%c%c%c\"\n",line[0],line[1],line[2],line[3],line[4],line[5]);
				for (int i = 4; i < length; i++) {
					if (line[i] == '\n') {
						break; //cut off line before new line
					}
					if (line[i] == ' ' && property < 3) {
						//printf("now: '%c', next: '%c'\n",line[i],line[i+1]);
						if (progress != 0) {
							switch (property) {
								case 0: //name
									entry.name = (char *)realloc(entry.name, progress - 1 * sizeof(char));
									//printf("name: %s\n",entry.name);
									break;
								case 1: //version
									entry.version = (char *)realloc(entry.version, progress * sizeof(char));
									//printf("version: %s\n",entry.version);
									break;
								case 2: //arch
									entry.arch = (char *)realloc(entry.arch, progress * sizeof(char));
									//printf("arch: %s\n",entry.arch);
									break;
							}
							progress = 0;
						}
						if (line[i + 1] != ' ') {
							property++;
						}
						continue;
					}
					//printf("[%d:%d](%d): %c\n",property,progress,(int)line[i], line[i]);
					switch (property) {
						case 0: // name
							entry.name[progress] = line[i];
							break;
						case 1: // version
							entry.version[progress] = line[i];
							break;
						case 2: // arch
							entry.arch[progress] = line[i];
							break;
						case 3: // description
							entry.description[progress] = line[i];
							break;
					}
					progress++;
				}

				if (progress > 0) {
					// cap off the description
					entry.description = (char *)realloc(entry.description, progress * sizeof(char));
					//printf("description: %s\n",entry.description);
				} else {
					delete entry.description;
					entry.description = NULL;
				}

				//printf("entry: %s\n", entry.name);

				int show = 1;
				//show &= entry.select == dpkg_entry::SEL_INSTALL;

				if (compare_count > 0) {
					show = 0;
				}
				for (int i = 0; i < compare_count; i++) {
					//printf("compare_list: %s\nentry: %s\n", compare_list[i], entry.name);
					if (strcmp(compare_list[i], entry.name) == 0) {
						show = 1;
					}
				}

				if (show) {
					//printf("%s\n", entry.name, entry.version);
					printf("\033[0m%s \033[0;32m%s\033[0m\n", entry.name, entry.version);
				}
			}

			closeCommand(fp);
			done++;
		}
	}
	
	if (args->op == OP_FILES) { // -F
		if (done == 0 && args->params[PARAM_REFRESH]==1) {// -FY
			callCommand(apt_file_update);
			done++;
		}
		if(done == 0 && args->params[PARAM_LIST]==1) {// -Fl (packages)
			char *cmd = (char *)malloc((strlen(apt_file_list) + 1 + args->targets_len) * sizeof(char));
			sprintf(cmd, "%s %s", apt_file_list, args->targets);
			callCommand(cmd);
			done++;
		}
		if(done == 0) {// -F (targets)
			char *cmd = (char *)malloc((strlen(apt_file_search) + 1 + args->targets_len) * sizeof(char));
			sprintf(cmd, "%s %s", apt_file_search, args->targets);
			callCommand(cmd);
			done++;
		}
	}

	if (args->op == OP_REMOVE) {
		// -R
		if (done == 0) {
			// -R (targets)
			char *cmd = (char *)malloc((strlen(apt_remove) + 1 + args->targets_len) * sizeof(char));
			sprintf(cmd, "%s %s", apt_remove, args->targets);
			callCommand(cmd);
			done++;
		}
	}
	
	if (args->op == OP_SYNC) {
		// -S
		if (done == 0 && args->params[PARAM_SEARCH] == 1) {
			// -Ss
			char *cmd = (char *)malloc((strlen(apt_search) + 1 + args->targets_len) * sizeof(char));
			sprintf(cmd, "%s %s", apt_search, args->targets);
			callCommand(cmd);
			done++;
		}
		if (done == 0) {
			if (args->params[PARAM_REFRESH] == 1) {
				// -Sy
				callCommand(apt_update);
				done++;
			}
			if (args->params[PARAM_UPGRADES] == 1) {
				// -Su
				callCommand(apt_upgrade);
				done++;
			}
		}

		if (done == 0) {
			// -S (targets)
			char *cmd = (char *)malloc((strlen(apt_install) + 1 + args->targets_len) * sizeof(char));
			sprintf(cmd, "%s %s", apt_install, args->targets);
			callCommand(cmd);
			done++;
		}
	}
	return done == 0;
}

#ifndef HUR_SHELL_HEADER
#define HUR_SHELL_HEADER


typedef void (*cmdfunction)(int, char**);
extern const char *COMMAND_NAMES[];
extern const cmdfunction COMMAND_FUNCTIONS[];

void cmd_search(int argc, char** argv);
void cmd_download(int argc, char** argv);

#endif

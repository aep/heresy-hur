#ifndef HUR_CONFIG_HEADER
#define HUR_CONFIG_HEADER

extern const char *HUR_ENVVAR;
extern const char *HUR_ANON;
extern const char *HUR_KEYFILE;
extern const char *HUR_DIR;

void config_load(char *configfile);

#endif

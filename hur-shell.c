#include <sys/stat.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "hur-shell.h"
#include "package.h"
#include "config.h"

const char *COMMAND_NAMES[] = {
    "search",
    "download",
    NULL
};

const cmdfunction COMMAND_FUNCTIONS[] = {
    &cmd_search,
    &cmd_download
};


char *HUR_USER;

/*
 * Hur usage:
 *
 *  hur search PATTERNS...
 *  hur upload < package.tar.gz
 *  hur download packagename > package.tar.gz
 *  hur register username < key.pub
 *  hur delete packagename
 *  hur addkey < key.pub
 *  hur rmkey < key.pub
 *  hur flag packagename
 *  hur unflag packagename
 *
 */

int main(int argc, char **argv)
{
    char *cmd;
    char **args;
    int i, numargs = 0;

    // Get the current user
    HUR_USER = getenv(HUR_ENVVAR);
    if (HUR_USER == NULL) HUR_USER = HUR_ANON;

    // Get all arguments
    if (argc > 2 && !strcmp(argv[1], "-c"))
    {
        // Command name
        char *tokens[256];
        cmd = strtok(argv[2], " ");

        // Split further arguments
        do
        {
            args[numargs] = strtok(NULL, " ");
            numargs++;
        }
        while (args[numargs-1] != 0);

        numargs--;
        args = (char **)tokens;
    }
    else if ( argc > 1)
    {
        numargs = argc-2;
        args = argv+2;
        cmd = argv[1];
    }
    else 
    {
        printf("Usage: %s COMMAND PARAMS...\n", argv[0]);
        return 1;
    }

    // Get the correct command to run
    for (i=0; COMMAND_NAMES[i] != NULL; i++)
        if (!strcmp(COMMAND_NAMES[i], cmd))
        {
            COMMAND_FUNCTIONS[i](numargs, args);
            break;
        }

    return 0;
}

void cmd_search(int argc, char** argv)
{
    // For now, this just goes through all the directories and checks if they 
    // have pattern in them, this needs to get regex and description matching.
    char *pattern = argv[0];
    DIR *dir = opendir(HUR_DIR);
    struct dirent *fdesc;
    char fulldir[PATH_MAX];
    pkg_t *pkg;
    printf(":%s\n", pattern);

    while ((fdesc = readdir(dir)) != NULL)
    {
        // Skip . and .. special files
        if (strcmp(fdesc->d_name, ".") == 0 ||
            strcmp(fdesc->d_name, "..") == 0)
            continue;

        // Load package
        snprintf(fulldir, sizeof(fulldir), "%s/%s", HUR_DIR, fdesc->d_name);
        pkg = package_load(fulldir);

        // Check if it matches
        /*if (strcasestr(pkg->name, pattern) != NULL)*/
        /*{*/
            /*printf("%s %s - added by %s\n%s\n\n",*/
              /*pkg->name, pkg->version, pkg->owner, pkg->desc);*/
        /*}*/

        /*// Free package*/
        /*package_free(pkg);*/
    }
}

void cmd_download(int argc, char** argv)
{
}

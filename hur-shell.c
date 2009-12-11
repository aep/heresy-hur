#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include "package.h"
#include "hur-shell.h"

// XXX: This needs to be in a configuration file
#define HUR_DIR "/data/others/hur"

/*
 * Hur usage:
 *
 *  hur-shell search PATTERN...
 *
 */

int main(int argc, char **argv)
{
    // XXX: Needs optparsing
    // argv[1] == "-c" (added by ssh)
    // argv[2] = actual arguments for shell
    
    char *cmd = strtok(argv[2], " ");
    char *arg = strtok(NULL, " ");

    if (!strcasecmp(cmd, "search"))
        search(arg);
}

void search(char *pattern)
{
    // For now, this just goes through all the directories and checks if they 
    // have pattern in them, this needs to get regex and description matching.
    DIR *dir = opendir(HUR_DIR);
    struct dirent *fdesc;
    char fulldir[PATH_MAX];
    pkg_t *pkg;

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
        if (strcasestr(pkg->name, pattern) != NULL)
        {
            printf("%s %s - added by %s\n%s\n\n",
              pkg->name, pkg->version, pkg->owner, pkg->desc);
        }

        // Free package
        package_free(pkg);
    }
}

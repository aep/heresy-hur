#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "package.h"

pkg_t *package_load(char *pkgdir)
{
    struct stat st;
    FILE *file;
    char *varname, *value;
    char descfile[PATH_MAX];
    char line[PATH_MAX];

    // Description file location
    snprintf(descfile, PATH_MAX, "%s/DESC", pkgdir);

    // Make sure the file exists
    if (stat(descfile, &st) != 0)
        return NULL;

    // Parse file contents
    pkg_t *pkg = malloc(sizeof(pkg_t));
    file = fopen(descfile, "r");

    while (fgets(line, sizeof(line), file))
    {
        // Remove newline
        line[strlen(line)-1] = '\0';

        // Split
        varname = strtok(line, "=");
        value = strtok(NULL, "=");
        
        // Set correct variable
        if (!strcmp(varname, "NAME"))
            pkg->name = strdup(value);
        else if (!strcmp(varname, "DESC"))
            pkg->desc = strdup(value);
        else if (!strcmp(varname, "OWNER"))
            pkg->owner = strdup(value);
        else if (!strcmp(varname, "VERSION"))
            pkg->version = strdup(value);
    }

    return pkg;
}


void package_free(pkg_t *pkg)
{
    free(pkg->name);
    free(pkg->desc);
    free(pkg->version);
    free(pkg->owner);
    free(pkg);
}

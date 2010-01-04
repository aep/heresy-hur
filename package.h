#ifndef HUR_PACKAGE_HEADER
#define HUR_PACKAGE_HEADER

struct pkgstruct
{
    /** Package name **/
    char *name;

    /** Package description **/
    char *desc;

    /** Package version **/
    char *version;
    
    /** Package owner **/
    char *owner;

    /** Package creation time **/
    int ctime;

    /** Package modification time **/
    int mtime;
};

typedef struct pkgstruct pkg_t;

pkg_t *package_load(char *pkgdir);
void package_free(pkg_t *pkg);

#endif

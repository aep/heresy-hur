#include "hur-client.h"
#include "stdio.h"

// XXX: This needs to be in a configuration file
#define SSH_BIN "/usr/bin/ssh"
#define SSH_HOST "hur@localhost"

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        char cmd[256];
        snprintf(cmd, sizeof(cmd), "%s %s search %s", SSH_BIN, SSH_HOST, argv[1]);
        system(cmd);
    }
}

#include "minishell.h"

int pwd()
{
    char    *cwd;

    cwd = getcwd(NULL, 1024);
    if (!cwd)
    {
        perror("pwd");
        exit(1);
    }
    printf("%s\n", cwd);
    free(cwd);
    return (0);
}
/*int main()
{
    if (pwd() == 0)
        printf("DONE\n");
    return (0);
}*/
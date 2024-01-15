#include "minishell.h"

int echo(char *cmd, char *argv[], int argc)
{
    int i;

    i = 2;
    if (argc < 3)
        write(1, "\n", 1);
    while (i < argc)
    {
        ft_putstr_fd(argv[i++], 1);
        ft_putchar_fd(' ', 1);
        if (ft_strcmp("echo -n", cmd) != 0)
            write(1, "\n", 1);
    }
    return (0);
}

/*int main(int argc, char *argv[])
{
    echo(argv[1], argv, argc);
    return (0);
}*/
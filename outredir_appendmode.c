
#include "minishell.h"

void    redirection_appendmode(t_alloc *mllcd, char *filename)
{
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        ft_putstr_fd("Error: Output redirection iun append mode failed.\n", 2);
        mllcd->exit_status = 1;
        return ;
    }
    dup2(fd, 1);
    close(fd);
    return ;
}

int main(void)
{
    t_alloc *mllcd;
    char *filename;

    mllcd = (t_alloc *)malloc(sizeof(t_alloc));
    mllcd->exit_status = 0;
    filename = "_testfile";
    redirection_appendmode(mllcd, filename);
    return (0);
}
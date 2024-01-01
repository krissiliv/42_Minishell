
#include "minishell.h"

int	main(int argc, char **argv, char **envv)
{
	int		pipe_ends[2];
	t_alloc	mallcd;

	if (argc != 5 || (argc == 5 && !(argv[1][0])))
		return (error_handling(pipe_ends, 8, NULL, false));
	mallcd.cmd = NULL;
	mallcd.poss_paths = NULL;
	mallcd.cmdpath = NULL;
	mallcd.poss_path = NULL;
	if (pipe(pipe_ends) == -1)
		return (error_handling(pipe_ends, 9, NULL, false));
	return (pipex(pipe_ends, argv, envv, &mallcd));
}
#include "../../incs/minishell.h"

void	link_pipe(int i, t_pipe *base,t_data *data)
{
	if (i == data->info->pipe_num)
	{
		if (dup2(base->com[i-1].fd[0], STDIN_FILENO) == -1 || \
			close(base->com[i-1].fd[0]) == -1)
			program_error_exit("pipe");
	}
	else if (i == 0)
	{
		if (close(base->com[i].fd[0]) == -1 || \
			dup2(base->com[i].fd[1], STDOUT_FILENO) == -1 || \
			close(base->com[i].fd[1])== -1)
			program_error_exit("pipe");
	}
	else
	{
		if (dup2(base->com[i - 1].fd[0], STDIN_FILENO) == -1 || \
			close(base->com[i-1].fd[0]) == -1 || \
			dup2(base->com[i].fd[1], STDOUT_FILENO) == -1  ||\
			close(base->com[i].fd[1]) == -1)
			program_error_exit("pipe");
	}
}


// 정상 종료 확인해주고 수정;
void	wait_child_processes(t_data *data)
{
	int			i;
	int			status;

	i = 0;
	while (i < data->info->pipe_num)
	{
		waitpid(-1, &status, 0);
		i++;
	}
}





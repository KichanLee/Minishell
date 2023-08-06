#include "../../incs/minishell.h"

void	link_pipe(int i, t_pipe *base,t_data *data)
{
	if (i == data->info->pipe_num)
	{
		dup2(base->com[i-1].fd[0], STDIN_FILENO);
		close(base->com[i-1].fd[0]);
	}
	else if (i == 0)
	{
			close(base->com[i].fd[0]); 
			dup2(base->com[i].fd[1], STDOUT_FILENO);
			close(base->com[i].fd[1]);
	}
	else
	{	
		close(base->com[i].fd[0]);
		dup2(base->com[i - 1].fd[0], STDIN_FILENO);
		dup2(base->com[i].fd[1], STDOUT_FILENO);
	} 
}

// 정상 종료 확인해주고 수정;
void	wait_child_processes(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->info->pipe_num + 1)
	{
		waitpid(-1, &status, 0);
		i++;
	}
}

#include "../../incs/minishell.h"

void	set_pipe(t_data *data)
{
	data->pipe->com = (t_pid *)ft_calloc(data->pipe_num + 2, sizeof(t_pid));// 하나를 여유롭게 생성하는이유는 herdoc 때문에 하나를 여유롭게생성
	if(!data->pipe->com)
		program_error_exit("bash");
}

void	link_pipe(int i, t_pipe *base,t_data *data)
{
	if (i == data->pipe_num)
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
	while (i < data->pipe_num)
	{
		waitpid(-1, &status, 0);
		i++;
	}
}





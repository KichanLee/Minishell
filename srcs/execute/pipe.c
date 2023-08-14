#include "../../incs/minishell.h"

int	link_pipe(int i, t_pipe *base, t_data *data)
{
	if (i == data->info->pipe_num)
	{
		if (dup2(base->com[i - 1].fd[0], STDIN_FILENO) == -1 \
		|| close(base->com[i - 1].fd[0]) == -1)
			return (1);
	}
	else if (i == 0)
	{
		if (close(base->com[i].fd[0]) == -1 \
		|| dup2(base->com[i].fd[1], STDOUT_FILENO) == -1 \
		|| close(base->com[i].fd[1]) == -1)
			return (1);
	}
	else
	{
		if (close(base->com[i].fd[0]) == -1 \
		|| dup2(base->com[i - 1].fd[0], STDIN_FILENO) == -1 \
		|| dup2(base->com[i].fd[1], STDOUT_FILENO) == -1)
			return (1);
	}
	return (0);
}

void	wait_child_processes(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	signal (SIGINT, SIG_IGN);
	while (i < data->info->pipe_num + 1)
	{	
		if (wait(&status) \
		== data->pipe->com[data->info->pipe_num].pid)
			data->error_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status) && !data->info->heredoc_flag)
			data->error_code = 128 + WTERMSIG(status);
		if (WEXITSTATUS(status))
			error_check(WEXITSTATUS(status), data);
		i++;
	}
	if (WTERMSIG (status) == 2)
		ft_putendl_fd("", STDERR_FILENO);
	else if (WTERMSIG (status) == 3)
		ft_putendl_fd("Quit: 3", STDOUT_FILENO);
	close_file(data);
}



void	error_check(int num, t_data *data)
{
	if (num == 127)
	{
		printf("bash: %s: command not found\n", \
		data->root->left_child->right_child->token->str);
	}
	if (num == 1)
	{
		printf("bash: %s: No such file or directory\n", \
		data->root->left_child->right_child->token->str);
	}
}

void	close_file(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->info->index)
		unlink(data->info->heredoc_file[i]);
}

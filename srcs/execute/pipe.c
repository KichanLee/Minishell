/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 17:08:11 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/13 17:08:23 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	link_pipe(int i, t_pipe *base, t_data *data)
{
	if (i == data->info->pipe_num)
	{
		if (dup2(base->com[i - 1].fd[0], STDIN_FILENO) == -1 \
		|| close(base->com[i - 1].fd[0]) == -1)
			error_back_readline(data, "Bad file descriptor", EBADF, 1);
	}
	else if (i == 0)
	{
		if (close(base->com[i].fd[0]) == -1 \
		|| dup2(base->com[i].fd[1], STDOUT_FILENO) == -1 \
		|| close(base->com[i].fd[1]) == -1)
			error_back_readline(data, "Bad file descriptor", EBADF, 1);
	}
	else
	{
		if (close(base->com[i].fd[0]) == -1 \
		|| dup2(base->com[i - 1].fd[0], STDIN_FILENO) == -1 \
		|| dup2(base->com[i].fd[1], STDOUT_FILENO) == -1)
			error_back_readline(data, "Bad file descriptor", EBADF, 1);
	}
}

void	wait_child_processes(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	signal (SIGINT, SIG_IGN);
	while (i < data->info->pipe_num + 1)
	{	
		waitpid(-1, &status, 0);
		i++;
	}
	if (WIFSIGNALED(status))
	{
		if (status == 3)
			ft_putendl_fd("QUIT: 3", STDERR_FILENO);
		else if (status == 2)
			ft_putendl_fd("", STDERR_FILENO);
		data->error_code = WTERMSIG(status);
	}
	i = 0;
	while (i < data->info->index)
	{
		unlink(data->info->heredoc_file[i]);
		i++;
	}
}

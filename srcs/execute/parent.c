/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:37:35 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/14 20:16:40 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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
		i++;
	}
	if (WTERMSIG (status) == 2)
		ft_putendl_fd("", STDERR_FILENO);
	else if (WTERMSIG (status) == 3)
		ft_putendl_fd("Quit: 3", STDOUT_FILENO);
	close_file(data);
}

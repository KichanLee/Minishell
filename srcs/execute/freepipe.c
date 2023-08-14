/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freepipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:49:42 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/08 23:07:39 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	close_pipe(int i, t_pipe *base, t_data *data)
{
	if (i == data->info->pipe_num)
		close(base->com[i - 1].fd[0]);
	else if (i == 0)
		close(base->com[i].fd[1]);
	else
	{
		close(base->com[i - 1].fd[0]);
		close(base->com[i].fd[1]);
	}
}

void	check_file(int fd, t_data *data)
{
	if (fd < 0)
	{
		close(fd);
		data->error_code = 1;
		if (data->info->parent == 1)
			exit(1);
	}
}

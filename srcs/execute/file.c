/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:53:28 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/14 18:53:45 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	check_file(int fd, t_data *data);
void	close_file(t_data *data);

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

void	close_file(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->info->index)
		unlink(data->info->heredoc_file[i]);
}

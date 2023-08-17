/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:53:28 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/17 22:04:04 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		check_file(int fd, t_data *data);
void	close_file(t_data *data);

int	check_file(int fd, t_data *data)
{
	char	*str;

	str = data->root->left_child->left_child->left_child->token->str;
	if (fd < 0)
	{
		close(fd);
		g_error_code = 1;
		error_print(str, 0, 1);
		if (data->info->parent == 1)
			exit(1);
		return (0);
	}
	return (1);
}

void	close_file(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->info->index)
		unlink(data->info->heredoc_file[i]);
}

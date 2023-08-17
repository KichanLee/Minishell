/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:40:44 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/17 14:57:44 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	input_free(t_data *data);
void	data_free(t_data *data);

void	input_free(t_data *data)
{
	int	i;

	ft_lstclear(&data->tokens);
	data->tokens = NULL;
	free(data->input);
	data->input = NULL;
	tree_clear(data->root);
	data->root = NULL;
	free(data->pipe->com);
	free(data->pipe);
	i = -1;
	while (++i < data->info->heredoc_flag)
		free(data->info->heredoc_file[i]);
	free(data->info->heredoc_file);
	free(data->info);
}

void	data_free(t_data *data)
{
	free(data->env_array);
	ft_lstclear(&data->envs);
	free(data);
}

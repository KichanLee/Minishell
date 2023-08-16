/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:40:44 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/16 22:51:25 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool	error_back_readline(t_data *data, char *str, int error_code, int flag);
void	program_error_exit(char *str);
void	input_free(t_data *data);
void	data_free(t_data *data);

t_bool	error_back_readline(t_data *data, char *str, int error_code, int flag)
{
	if (flag)
		perror(str);
	else
		printf("%s\n", str);
	data->error_code = error_code;
	return (FALSE);
}

void	program_error_exit(char *str)
{
	perror(str);
	exit(errno);
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:40:44 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/08 18:34:06 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool	error_back_readline(t_data *data, char *str, int error_code,int flag);
void	program_error_exit(char *str);
void	input_free(t_data *data);
void	data_free(t_data *data);

//input 관련 에러일 때 사용
t_bool	error_back_readline(t_data *data, char *str, int error_code,int flag)
{
	if (flag)
		perror(str);
	else	
		printf("%s\n", str);
	data->error_code = error_code;
	return (FALSE);
}

//system 관련 에러일 때
void	program_error_exit(char *str)
{
	perror(str);
	exit(errno);
}

//input 한번 끝났을 때 사용
void	input_free(t_data *data)
{
	int i;

	ft_lstclear(&data->tokens);
	data->tokens = NULL;
	free(data->input);
	data->input = NULL;
	tree_clear(data->root);
	data->root = NULL;
	free(data->pipe);
	free(data->pipe->com);
	i = -1;
	while(++i < data->info->heredoc_flag)
		free(data->info->heredoc_file[i]);
	free(data->info->heredoc_file);
	free(data->info);
}

//정상종료 시 사용
void	data_free(t_data *data)
{
	ft_lstclear(&data->envs);
	free(data);
}
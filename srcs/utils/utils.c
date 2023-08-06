/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:40:44 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/21 08:45:57 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool	error_back_readline(t_data *data, char *str, int error_code);
void	program_error_exit(char *str);
void	input_free(t_data *data);
void	data_free(t_data *data);

//input 관련 에러일 때 사용
t_bool	error_back_readline(t_data *data, char *str, int error_code)
{
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
	ft_lstclear(&data->tokens);
	data->tokens = NULL;
	free(data->input);
	data->input = NULL;
	tree_clear(data->root);	
	data->root = NULL;
}

//정상종료 시 사용
void	data_free(t_data *data)
{
	ft_lstclear(&data->envs);
	free(data);
}
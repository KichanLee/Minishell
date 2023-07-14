/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:40:44 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/14 08:48:12 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	syntax_error_exit(char *str);
void	error_exit(char *str);

//부모가 258로 받게 해야 함
void	syntax_error_exit(char *str)
{
	printf("%s\n", str);
	exit(2);
}

void	error_exit(char *str)
{
	perror(str);
	exit(errno);
}

//free는 구현 끝나고 마지막에 하기
// void	all_free(t_data *data)
// {
// 	ft_lstclear(&data->envs);
// 	free(data->input);
// 	data->root;
// 	data->tokens;
// }
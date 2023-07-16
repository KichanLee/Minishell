/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:40:44 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/15 09:37:45 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	syntax_error_exit(char *str);
void	error_exit(char *str);
void	all_free(t_data *data);

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

void	all_free(t_data *data)
{
	free(data->input);
	ft_lstclear(&data->tokens);
	ft_lstclear(&data->envs);
	tree_clear(data->root);
	free(data);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:27:16 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/14 20:17:02 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_bool	get_input(t_data *data)
{
	data->input = readline("minishell$ ");
	if (!data->input)
	{
		printf("exit\n");
		exit(1);
	}
	if (!data->input[0])
	{
		free(data->input);
		return (FALSE);
	}
	add_history(data->input);
	lexer(data);
	if (syntax(data) == FALSE)
	{
		tree_clear(data->root);
		ft_lstclear(&data->tokens);
		free(data->input);
		return (FALSE);
	}
	parser(data);
	pipe_init(&data->pipe);
	info_init(&data->info);
	return (TRUE);
}

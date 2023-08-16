/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:27:16 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/16 19:15:48 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static t_bool	check_blank_input(char *str);

t_bool	get_input(t_data *data)
{
	data->input = readline("minishell$ ");
	if (!data->input)
	{
		printf("exit\n");
		exit(1);
	}
	if (check_blank_input(data->input) == TRUE)
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

static t_bool	check_blank_input(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0')
		return (TRUE);
	return (FALSE);
}

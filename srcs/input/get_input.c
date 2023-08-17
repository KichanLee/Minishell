/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:27:16 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/17 21:39:51 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool			get_input(t_data *data);
static t_bool	check_blank_input(char *str);

t_bool	get_input(t_data *data)
{
	data->input = readline("minishell$ ");
	if (!data->input)
	{
		printf("exit\n");
		g_error_code = 0;
		exit(0);
	}
	add_history(data->input);
	if (check_blank_input(data->input) == TRUE || lexer(data) == FALSE)
	{
		free(data->input);
		return (FALSE);
	}
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

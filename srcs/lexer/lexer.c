/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:24:37 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/14 08:01:29 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void		lexer(t_data *data);
static void	check_char(t_data *data, t_token **token, int *i);

void	lexer(t_data *data)
{
	int			i;
	t_token		*token;

	token = token_create();
	if (!token)
		error_exit("bash");
	i = -1;
	while (data->input[++i])
		check_char(data, &token, &i);
	if (token->str && *(token->str))
		token_add_list(&data->tokens, &token, FALSE);
}

static void	check_char(t_data *data, t_token **token, int *i)
{
	if (data->input[*i] == '|' \
		|| data->input[*i] == '<' || data->input[*i] == '>')
	{
		if (*(*token)->str)
			token_add_list(&data->tokens, token, TRUE);
		tokenizer(data, token, i);
	}
	else if (data->input[*i] == '\'' || data->input[*i] == '\"')
	{
		tokenizer(data, token, i);
	}
	else if (data->input[*i] == ' ' || data->input[*i] == '\t')
	{
		if (*(*token)->str)
			token_add_list(&data->tokens, token, TRUE);
	}
	else if (data->input[*i] == '$')
		expand(data, *token, i, FALSE);
	else
		(*token)->str = ft_strncat((*token)->str, &data->input[*i], 1);
}

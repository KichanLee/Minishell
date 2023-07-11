/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:24:37 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/11 17:16:42 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool			lexer(t_data *data);
static t_bool	check_char(t_data *data, t_token **token, int *i);

t_bool	lexer(t_data *data)
{
	int			i;
	t_token		*token;

	token = token_create();
	if (!token)
		return (FALSE);
	i = -1;
	while (data->input[++i])
		if (check_char(data, &token, &i) == FALSE)
			return (FALSE);
	if (token->str && *(token->str))
		token_add_list(&data->tokens, &token, FALSE);
	return (TRUE);
}

static t_bool	check_char(t_data *data, t_token **token, int *i)
{
	if (data->input[*i] == '|' || data->input[*i] == '<' || data->input[*i] == '>')
	{
		if (*(*token)->str)
		{
			if (token_add_list(&data->tokens, token, TRUE) == FALSE)
				return (FALSE);
		}
		if (tokenizer(data, token, i) == FALSE)
			return (FALSE);
	}
	else if (data->input[*i] == '\'' || data->input[*i] == '\"')
	{
		if (tokenizer(data, token, i) == FALSE)
			return (FALSE);
	}
	else if (data->input[*i] == ' ' || data->input[*i] == '\t')
	{
		if (*(*token)->str)
		{
			if (token_add_list(&data->tokens, token, TRUE) == FALSE)
				return (FALSE);
		}
	}
	else if (data->input[*i] == '$')
		expand(data, *token, i, FALSE);
	else
		(*token)->str = ft_strncat((*token)->str, &data->input[*i], 1);
	return (TRUE);
}
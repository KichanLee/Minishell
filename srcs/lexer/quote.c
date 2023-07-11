/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 07:46:30 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/11 17:18:11 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool 			single_quote(char *input, t_token *token, int *i);
t_bool 			double_quote(char *input, t_token *token, int *i, t_data *data);
static t_bool	find_next_quote(char *input, int i, char quote);

t_bool single_quote(char *input, t_token *token, int *i)
{
	*i += 1;
	if (find_next_quote(input, *i, '\'') == FALSE)
		token->str = ft_strncat(token->str, "\'", 1);
	while (input[*i] != '\'' && input[*i] != '\0')
	{
		if (input[*i] == '\\' && input[*i + 1] == '\'')
		{
			token->str = ft_strncat(token->str, "\\\'", 1);
			*i += 1;
		}
		else
			token->str = ft_strncat(token->str, &input[*i], 1);
		if (!token->str)
			return (FALSE);
		*i += 1;
	}
	if (input[*i] == '\0')
		*i -= 1;
	return (TRUE);
}

t_bool double_quote(char *input, t_token *token, int *i, t_data *data)
{
	*i += 1;
	if (find_next_quote(input, *i, '\"') == FALSE)
		token->str = ft_strncat(token->str, "\"", 1);
	while (input[*i] != '\"' && input[*i] != '\0')
	{
		if (input[*i] == '\\' && input[*i + 1] == '\"')
		{
			token->str = ft_strncat(token->str, "\\\"", 1);
			*i += 1;
		}
		if (input[*i] == '$')
		{
			if (input[*i + 1] == '\'')
				token->str = ft_strncat(token->str, &input[*i], 1);
			else
				if (expand(data, token, i, TRUE) == FALSE)
					return (FALSE);
		}
		else
			token->str = ft_strncat(token->str, &input[*i], 1);
		if (!token->str)
			return (FALSE);
		*i += 1;
	}
	if (input[*i] == '\0')
		*i -= 1;
	return (TRUE);
}

static t_bool	find_next_quote(char *input, int i, char quote)
{
	while (input[i] != quote && input[i] != '\0')
	{
		if (input[i] == '\\' && input[i + 1] == quote)
			i++;
		i++;
	}
	if (input[i] == '\0')
		return (FALSE);
	return (TRUE);
}

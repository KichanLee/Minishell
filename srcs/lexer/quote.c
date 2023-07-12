/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 07:46:30 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/12 21:01:39 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void			single_quote(char *input, t_token *token, int *i);
void			double_quote(char *input, t_token *token, int *i, t_data *data);
static t_bool	find_next_quote(char *input, int i, char quote);

static t_bool	check_blank(char *input, int *i, t_bool next_quote)
{
	if (next_quote == FALSE \
		&& (input[*i] != ' ' || input[*i] != '\t'))
	{
		*i -= 1;
		return (TRUE);
	}
	return (FALSE);
}

static void	check_escape()
{

}

void	single_quote(char *input, t_token *token, int *i)
{
	t_bool	next_quote;

	*i += 1;
	next_quote = find_next_quote(input, *i, '\'');
	if (next_quote == FALSE)
	{
		token->str = ft_strncat(token->str, "\'", 1);
		if (!token->str)
			error_exit("bash");
	}
	while (input[*i] != '\'' && input[*i] != '\0')
	{
		if (next_quote == FALSE \
			&& (input[*i] != ' ' || input[*i] != '\t'))
		{
			*i -= 1;
			return ;
		}
		if (input[*i] == '\\' && input[*i + 1] == '\'')
		{
			token->str = ft_strncat(token->str, "\\\'", 2);
			*i += 1;
		}
		else
			token->str = ft_strncat(token->str, &input[*i], 1);
		if (!token->str)
			error_exit("bash");
		*i += 1;
	}
	if (input[*i] == '\0')
		*i -= 1;
}

void	double_quote(char *input, t_token *token, int *i, t_data *data)
{
	t_bool	next_quote;

	*i += 1;
	next_quote = find_next_quote(input, *i, '\"');
	if (next_quote == FALSE)
	{
		token->str = ft_strncat(token->str, "\"", 1);
		if (!token->str)
			error_exit("bash");
	}
	while (input[*i] != '\"' && input[*i] != '\0')
	{
		if (input[*i] == '$')
		{
			if (input[*i + 1] == '\'')
				token->str = ft_strncat(token->str, &input[*i], 1);
			else
				expand(data, token, i, TRUE);
		}
		if (next_quote == FALSE \
			&& (input[*i] != ' ' || input[*i] != '\t'))
		{
			*i -= 1;
			return ;
		}
		if (input[*i] == '\\' && input[*i + 1] == '\"')
		{
			token->str = ft_strncat(token->str, "\\\"", 2);
			*i += 1;
		}
		else
			token->str = ft_strncat(token->str, &input[*i], 1);
		if (!token->str)
			error_exit("bash");
		*i += 1;
	}
	if (input[*i] == '\0')
		*i -= 1;
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

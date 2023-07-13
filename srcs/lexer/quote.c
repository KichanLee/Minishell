/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 07:46:30 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/14 08:07:53 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void			single_quote(char *input, t_token *token, int *i);
void			double_quote(char *input, t_token *token, int *i, t_data *data);
static t_bool	find_next_quote(char *input, t_token *token, int i, char quote);
static t_bool	s_check_char(char *input, t_token *token, int *i, t_bool next_quote);
static t_bool	d_check_char(char *input, t_token *token, int *i, t_bool next_quote);

void	single_quote(char *input, t_token *token, int *i)
{
	t_bool	next_quote;

	*i += 1;
	next_quote = find_next_quote(input, token, *i, '\'');
	while (input[*i] != '\'' && input[*i] != '\0')
	{
		if (s_check_char(input, token, i, next_quote) == TRUE)
			return ;
		*i += 1;
	}
	if (input[*i] == '\0')
		*i -= 1;
}

void	double_quote(char *input, t_token *token, int *i, t_data *data)
{
	t_bool	next_quote;

	*i += 1;
	next_quote = find_next_quote(input, token, *i, '\"');
	while (input[*i] != '\"' && input[*i] != '\0')
	{
		if (input[*i] == '$')
		{
			if (input[*i + 1] != '\'' && next_quote == TRUE)
				if (expand(data, token, i, TRUE) == TRUE)
					return ;
		}
		if (d_check_char(input, token, i, next_quote) == TRUE)
			return ;
		*i += 1;
	}
	if (input[*i] == '\0')
		*i -= 1;
}

static t_bool	find_next_quote(char *input, t_token *token, int i, char quote)
{
	if (quote == '\"')
		while (input[i] != quote && input[i] != '\0')
		{
			if (input[i] == '\\' && input[i + 1] == quote)
				i++;
			i++;
		}
	else
		while (input[i] != quote && input[i] != '\0')
			i++;
	if (input[i] == '\0')
	{
		token->str = ft_strncat(token->str, &quote, 1);
		if (!token->str)
			error_exit("bash");
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	s_check_char(char *input, t_token *token, int *i, t_bool next_quote)
{
	if (next_quote == FALSE \
		&& (input[*i] != ' ' || input[*i] != '\t'))
	{
		*i -= 1;
		return (TRUE);
	}
	else
		token->str = ft_strncat(token->str, &input[*i], 1);
	if (!token->str)
		error_exit("bash");
	return (FALSE);
}

static t_bool	d_check_char(char *input, t_token *token, int *i, t_bool next_quote)
{
	if (next_quote == FALSE \
		&& (input[*i] != ' ' || input[*i] != '\t'))
	{
		*i -= 1;
		return (TRUE);
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
	return (FALSE);
}
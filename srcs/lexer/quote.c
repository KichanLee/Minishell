/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 07:46:30 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/21 20:55:14 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void			single_quote(char *line, t_token *token, int *i);
void			double_quote(char *line, t_token *token, int *i, t_input *input);
static t_bool	find_next_quote(char *line, t_token *token, int i, char quote);
static t_bool	s_check_char(char *line, t_token *token, int *i, t_bool next_quote);
static t_bool	d_check_char(char *line, t_token *token, int *i, t_bool next_quote);

void	single_quote(char *line, t_token *token, int *i)
{
	t_bool	next_quote;

	*i += 1;
	next_quote = find_next_quote(line, token, *i, '\'');
	while (line[*i] != '\'' && line[*i] != '\0')
	{
		if (s_check_char(line, token, i, next_quote) == TRUE)
			return ;
		*i += 1;
	}
	if (line[*i] == '\0')
		*i -= 1;
}

void	double_quote(char *line, t_token *token, int *i, t_input *input)
{
	t_bool	next_quote;

	*i += 1;
	next_quote = find_next_quote(line, token, *i, '\"');
	while (line[*i] != '\"' && line[*i] != '\0')
	{
		if (line[*i] == '$')
		{
			if (line[*i + 1] != '\'' && next_quote == TRUE)
				if (expand(input, token, i, TRUE) == TRUE)
					return ;
		}
		if (d_check_char(line, token, i, next_quote) == TRUE)
			return ;
		*i += 1;
	}
	if (line[*i] == '\0')
		*i -= 1;
}

static t_bool	find_next_quote(char *line, t_token *token, int i, char quote)
{
	if (quote == '\"')
		while (line[i] != quote && line[i] != '\0')
		{
			if (line[i] == '\\' && line[i + 1] == quote)
				i++;
			i++;
		}
	else
		while (line[i] != quote && line[i] != '\0')
			i++;
	if (line[i] == '\0')
	{
		token->str = ft_strncat(token->str, &quote, 1);
		if (!token->str)
			program_error_exit("bash");
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	s_check_char(char *line, t_token *token, int *i, t_bool next_quote)
{
	if (next_quote == FALSE \
		&& (line[*i] != ' ' || line[*i] != '\t'))
	{
		*i -= 1;
		return (TRUE);
	}
	else
		token->str = ft_strncat(token->str, &line[*i], 1);
	if (!token->str)
		program_error_exit("bash");
	return (FALSE);
}

static t_bool	d_check_char(char *line, t_token *token, int *i, t_bool next_quote)
{
	if (next_quote == FALSE \
		&& (line[*i] != ' ' || line[*i] != '\t'))
	{
		*i -= 1;
		return (TRUE);
	}
	if (line[*i] == '\\' && line[*i + 1] == '\"')
	{
		token->str = ft_strncat(token->str, "\\\"", 2);
		*i += 1;
	}
	else
		token->str = ft_strncat(token->str, &line[*i], 1);
	if (!token->str)
		program_error_exit("bash");
	return (FALSE);
}
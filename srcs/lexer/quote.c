/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 07:46:30 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/13 13:39:07 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void			single_quote(char *input, t_token **token, int *i);
void			double_quote(t_data *data, char *input, t_token **token, int *i);
static t_bool	find_next_quote(char *input, t_token *token, int i, char quote);
static t_bool	s_check_char(char *input, t_token *token, int *i, t_bool next_quote);
static t_bool	d_check_char(char *input, t_token *token, int *i, t_bool next_quote);

void	single_quote(char *input, t_token **token, int *i)
{
	t_bool	next_quote;

	*i += 1;
	if (input[*i] == '\'')
		(*token)->blank = FALSE;
	next_quote = find_next_quote(input, (*token), *i, '\'');
	while (input[*i] != '\'' && input[*i] != '\0')
	{
		if (s_check_char(input, *token, i, next_quote) == TRUE)
			return ;
		*i += 1;
	}
	if (check_end(input[*i + 1]) == FALSE \
		|| check_last_blank(input, *i + 1) == TRUE)
		(*token)->blank = FALSE;
	if (input[*i] == '\0')
		*i -= 1;
}

void	double_quote(t_data *data, char *input, t_token **token, int *i)
{
	t_bool	next_quote;

	*i += 1;
	if (input[*i] == '\"')
		(*token)->blank = FALSE;
	next_quote = find_next_quote(input, *token, *i, '\"');
	while (input[*i] != '\"' && input[*i] != '\0')
	{
		if (input[*i] == '$' && input[*i + 1] == '\"')
		{
			(*token)->str = ft_strncat((*token)->str, &input[*i], 1);
			*i += 1;
			continue ;
		}
		while (input[*i] == '$' && input[*i + 1] != '\'')
		{
			if (next_quote == TRUE)
				if (expand(data, token, i, TRUE) == TRUE)
					break ;
		}
		if (d_check_char(input, *token, i, next_quote) == TRUE)
			break ;
		*i += 1;
	}
	if (check_end(input[*i + 1]) == FALSE \
		|| check_last_blank(input, *i + 1) == TRUE)
		(*token)->blank = FALSE;
	if (input[*i] == '\0')
		*i -= 1;
}

static t_bool	find_next_quote(char *input, t_token *token, int i, char quote)
{
	while (input[i] != quote && input[i] != '\0')
		i++;
	if (input[i] == '\0')
	{
		token->str = ft_strncat(token->str, &quote, 1);
		if (!token->str)
			program_error_exit("bash");
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
		program_error_exit("bash");
	return (FALSE);
}

static t_bool	d_check_char(char *input, t_token *token, int *i, t_bool next_quote)
{
	if (next_quote == TRUE && input[*i] == '\"')
		return (TRUE);
	if (next_quote == FALSE \
		&& (input[*i] != ' ' || input[*i] != '\t'))
	{
		*i -= 1;
		return (TRUE);
	}
	else
		token->str = ft_strncat(token->str, &input[*i], 1);
	if (!token->str)
		program_error_exit("bash");
	return (FALSE);
}
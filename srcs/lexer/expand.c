/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:20:49 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/21 20:55:49 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool			expand(t_input *input, t_token *token, int *i, t_bool quote);
static t_bool	check_heredoc(t_input *input, t_token *token, int *i);
static t_bool	check_blank(t_input *input, t_token *token, int *i, t_bool quote);
static t_bool	check_other(t_input *input, t_token *token, int *i, t_bool 	quote);
static void		replace(t_input *input, t_token *token, char *name);

//환경변수 뒤에 숫자 알파벳 외에는 환경변수 치환해야함
t_bool	expand(t_input *input, t_token *token, int *i, t_bool quote)
{
	char	*name;

	*i += 1;
	name = NULL;
	if (check_heredoc(input, token, i) == TRUE)
		return (TRUE);
	if (check_blank(input, token, i, quote) == TRUE)
		return (TRUE);
	if (check_other(input, token, i, quote) == TRUE)
		return (TRUE);
	while (input->line[*i] != '\'' && input->line[*i] != '\"' \
		&& input->line[*i] != ' ' && input->line[*i] != '\t' \
		&& input->line[*i] != '\0' && ft_isalnum(input->line[*i]))
	{
		name = ft_strncat(name, &input->line[*i], 1);
		if (!name)
			program_error_exit("bash");
		*i += 1;
	}
	replace(input, token, name);
	if (quote == FALSE)
		*i -= 1;
	else if (quote == TRUE && input->line[*i] == '\"')
		return (TRUE);
	return (FALSE);
}

static t_bool	check_heredoc(t_input *input, t_token *token, int *i)
{
	t_list	*tmp;

	tmp = ft_lstlast(input->tokens);
	if (tmp && tmp->token->redirect_type == T_HEREDOC)
	{
		token->str = ft_strncat(token->str, "$", 1);
		if (!token->str)
			program_error_exit("bash");
		*i -= 1;
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	check_blank(t_input *input, t_token *token, int *i, t_bool quote)
{
	if (quote == FALSE && (input->line[*i] == ' ' || input->line[*i] == '\t'))
	{
		token->str = ft_strncat(token->str, "$", 1);
		if (!token->str)
			program_error_exit("bash");
		if (quote == FALSE)
		{
			*i -= 1;
			return (TRUE);
		}
		token->str = ft_strncat(token->str, &input->line[*i], 1);
		if (!token->str)
			program_error_exit("bash");
		if (quote == TRUE)
			return (TRUE);
	}
	return (FALSE);
}

static t_bool	check_other(t_input *input, t_token *token, int *i, t_bool quote)
{
	if (input->line[*i] == '\"')
	{
		if (quote == TRUE)
		{
			token->str = ft_strncat(token->str, "$", 1);
			if (!token->str)
				program_error_exit("bash");
		}
		else
		{
			if (input->line[*i + 1] == '\0')
				return (FALSE);
			*i -= 1;
		}
		return (TRUE);
	}
	else if (input->line[*i] == '\'')
	{
		*i -= 1 ;
		return (TRUE);
	}
	else if (input->line[*i] == '\0')
	{
		token->str = ft_strncat(token->str, "$", 1);
		if (!token->str)
			program_error_exit("bash");
		return (TRUE);
	}
	return (FALSE);
}

static void	replace(t_input *input, t_token *token, char *name)
{
	int		j;
	t_list	*tmp;

	tmp = env_search(input, name);
	if (!tmp)
	{
		token->str = ft_strdup("$");
		if (!token->str)
			program_error_exit("bash");
		token->str = ft_strncat(token->str, name, ft_strlen(name));
		if (!token->str)
			program_error_exit("bash");
	}
	else
	{
		j = 0;
		while (tmp->env[j] != '=')
			j++;
		token->str = ft_strncat(token->str, \
			&tmp->env[j + 1], ft_strlen(&tmp->env[j + 1]));
		if (!token->str)
			program_error_exit("bash");
	}
	free(name); // test.
}

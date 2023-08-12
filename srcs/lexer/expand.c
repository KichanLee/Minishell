/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:20:49 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/12 21:08:53 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool			expand(t_data *data, t_token **token, int *i, t_bool quote);
static t_bool	check_heredoc(t_data *data, t_token *token, int *i);
static t_bool	check_blank(t_data *data, t_token *token, int *i, t_bool quote);
static t_bool	check_other(t_data *data, t_token *token, int *i, t_bool quote);
static t_bool	check_question(t_data *data, t_token *token, int *i);
static void		replace(t_data *data, t_token *token, char *name);

static t_bool	check_special(t_data *data, t_token *token, int *i)
{
	if (!ft_isalpha(data->input[*i]) && data->input[*i] != '_')
	{
		token->str = ft_strncat(token->str, "$", 1);
		while (!ft_isalpha(data->input[*i]) && data->input[*i] != '$' && check_end(data->input[*i]) == FALSE)
		{
			token->str = ft_strncat(token->str, &data->input[*i], 1);
			if (!token->str)
				program_error_exit("bash");
			*i += 1;
		}
		return (TRUE);
	}
	return (FALSE);
}

t_bool	expand(t_data *data, t_token **token, int *i, t_bool quote)
{
	char	*name;

	*i += 1;
	if (check_heredoc(data, *token, i) == FALSE \
		&& check_question(data, *token, i) == FALSE \
		&& check_blank(data, *token, i, quote) == FALSE \
		&& check_other(data, *token, i, quote) == FALSE \
		&& check_special(data, *token, i) == FALSE)
	{
		name = ft_strdup("");
		while (ft_isalnum(data->input[*i]) || data->input[*i] == '_')
		{
			name = ft_strncat(name, &data->input[*i], 1);
			if (!name)
				program_error_exit("bash");
			*i += 1;
		}
		replace(data, *token, name);
	}
	if (quote == FALSE)
	{
		if (check_end(data->input[*i]) == FALSE)
			(*token)->blank = FALSE;
		*i -= 1;
	}
	return (FALSE);
}

static t_bool	check_heredoc(t_data *data, t_token *token, int *i)
{
	t_list	*tmp;

	tmp = ft_lstlast(data->tokens);
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

static t_bool	check_blank(t_data *data, t_token *token, int *i, t_bool quote)
{
	if (quote == FALSE && (data->input[*i] == ' ' || data->input[*i] == '\t'))
	{
		token->str = ft_strncat(token->str, "$", 1);
		if (!token->str)
			program_error_exit("bash");
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	check_other(t_data *data, t_token *token, int *i, t_bool quote)
{
	if (data->input[*i] == '\'')
		return (TRUE);
	else if (data->input[*i] == '\"')
	{
		if (quote == TRUE \
			|| check_end(data->input[*i + 1]) == TRUE)
		{
			token->str = ft_strncat(token->str, "$", 1);
			if (!token->str)
				program_error_exit("bash");
		}
		return (TRUE);
	}
	else if (data->input[*i] == '\0')
	{
		token->str = ft_strncat(token->str, "$", 1);
		if (!token->str)
			program_error_exit("bash");
		return (TRUE);
	}
	return (FALSE);
}

static void	replace(t_data *data, t_token *token, char *name)
{
	int		j;
	t_list	*tmp;

	tmp = env_search(data, name);
	if (tmp)
	{
		j = 0;
		while (tmp->env[j] != '=')
			j++;
		token->str = ft_strncat(token->str, \
			&tmp->env[j + 1], ft_strlen(&tmp->env[j + 1]));
		if (!token->str)
			program_error_exit("bash");
	}
	free(name);
}

static t_bool	check_question(t_data *data, t_token *token, int *i)
{
	char	*tmp;
	
	if (data->input[*i] == '?')
	{
		tmp = ft_itoa(data->error_code);
		token->str = ft_strncat(token->str, tmp, ft_strlen(tmp));
		if (check_end(data->input[*i + 1]) == FALSE)
			token->blank = FALSE;
		*i += 1;
		return (TRUE);
	}
	return (FALSE);
}

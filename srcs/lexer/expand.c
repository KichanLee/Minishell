/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:20:49 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/14 08:45:36 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool			expand(t_data *data, t_token *token, int *i, t_bool quote);
static t_bool	check_heredoc(t_data *data, t_token *token, int *i);
static t_bool	check_blank(t_data *data, t_token *token, int *i, t_bool quote);
static t_bool	check_other(t_data *data, t_token *token, int *i, t_bool 	quote);
static void		replace(t_data *data, t_token *token, char *name);

t_bool	expand(t_data *data, t_token *token, int *i, t_bool quote)
{
	char	*name;

	*i += 1;
	name = NULL;
	if (check_heredoc(data, token, i) == TRUE)
		return (TRUE);
	if (check_blank(data, token, i, quote) == TRUE)
		return (TRUE);
	if (check_other(data, token, i, quote) == TRUE)
		return (TRUE);
	while (data->input[*i] != '\'' && data->input[*i] != '\"' \
		&& data->input[*i] != ' ' && data->input[*i] != '\t' \
		&& data->input[*i] != '\0')
	{
		name = ft_strncat(name, &data->input[*i], 1);
		if (!name)
			error_exit("bash");
		*i += 1;
	}
	replace(data, token, name);
	if (quote == FALSE)
		*i -= 1;
	else if (quote == TRUE && data->input[*i] == '\"')
		return (TRUE);
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
			error_exit("bash");
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
			error_exit("bash");
		if (quote == FALSE)
		{
			*i -= 1;
			return (TRUE);
		}
		token->str = ft_strncat(token->str, &data->input[*i], 1);
		if (!token->str)
			error_exit("bash");
		if (quote == TRUE)
			return (TRUE);
	}
	return (FALSE);
}

static t_bool	check_other(t_data *data, t_token *token, int *i, t_bool quote)
{
	if (data->input[*i] == '\'' || data->input[*i] == '\"')
	{
		if (quote == TRUE)
		{
			*i += 1;
			return (FALSE);
		}
		*i -= 1 ;
		return (TRUE);
	}
	if (data->input[*i] == '\0')
	{
		token->str = ft_strncat(token->str, "$", 1);
		if (!token->str)
			error_exit("bash");
		return (TRUE);
	}
	return (FALSE);
}

static void	replace(t_data *data, t_token *token, char *name)
{
	int		j;
	t_list	*tmp;

	tmp = env_search(data, name);
	if (!tmp)
	{
		token->str = ft_strdup("$");
		if (!token->str)
			error_exit("bash");
		token->str = ft_strncat(token->str, name, ft_strlen(name));
		if (!token->str)
			error_exit("bash");
	}
	else
	{
		j = 0;
		while (tmp->env[j] != '=')
			j++;
		token->str = ft_strncat(token->str, \
			&tmp->env[j + 1], ft_strlen(&tmp->env[j + 1]));
		if (!token->str)
			error_exit("bash");
	}
	free(name);
}

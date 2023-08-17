/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:23:58 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/17 21:29:36 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool	check_heredoc(t_data *data, t_token *token, int *i);
t_bool	check_question(t_data *data, t_token *token, int *i);
t_bool	check_d_quote(t_data *data, t_token *token, int *i, t_bool quote);
t_bool	check_other(t_data *data, t_token *token, int *i, t_bool quote);
t_bool	check_special(t_data *data, t_token *token, int *i);

t_bool	check_heredoc(t_data *data, t_token *token, int *i)
{
	t_list	*tmp;

	tmp = ft_lstlast(data->tokens);
	if (tmp && tmp->token->redirect_type == T_HEREDOC)
	{
		token->str = ft_strncat(token->str, "$", 1);
		*i -= 1;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	check_question(t_data *data, t_token *token, int *i)
{
	char	*tmp;

	if (data->input[*i] == '?')
	{
		tmp = ft_itoa(g_error_code);
		token->str = ft_strncat(token->str, tmp, ft_strlen(tmp));
		token->blank = check_end(data->input[*i + 1]);
		*i += 1;
		free(tmp);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	check_d_quote(t_data *data, t_token *token, int *i, t_bool quote)
{
	int	idx;

	if (data->input[*i] == '\"')
	{
		idx = *i;
		if (quote == FALSE)
			while (data->input[idx + 1] != '\"' && data->input[idx + 1] != '\0')
				idx++;
		if (quote == TRUE || check_end(data->input[idx + 1]) == TRUE)
			token->str = ft_strncat(token->str, "$", 1);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	check_other(t_data *data, t_token *token, int *i, t_bool quote)
{
	if (quote == FALSE && (data->input[*i] == ' ' || data->input[*i] == '\t'))
	{
		token->str = ft_strncat(token->str, "$", 1);
		return (TRUE);
	}
	else if (data->input[*i] == '\'')
		return (TRUE);
	else if (data->input[*i] == '\0')
	{
		token->str = ft_strncat(token->str, "$", 1);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	check_special(t_data *data, t_token *token, int *i)
{
	if (!ft_isalpha(data->input[*i]) && data->input[*i] != '_')
	{
		token->str = ft_strncat(token->str, "$", 1);
		while (!ft_isalpha(data->input[*i]) \
			&& data->input[*i] != '$' \
			&& check_end(data->input[*i]) == FALSE)
		{
			token->str = ft_strncat(token->str, &data->input[*i], 1);
			*i += 1;
		}
		return (TRUE);
	}
	return (FALSE);
}

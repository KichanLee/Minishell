/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:23:58 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/13 16:30:15 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool	check_heredoc(t_data *data, t_token *token, int *i);
t_bool	check_question(t_data *data, t_token *token, int *i);
t_bool	check_blank(t_data *data, t_token *token, int *i, t_bool quote);
t_bool	check_other(t_data *data, t_token *token, int *i, t_bool quote);
t_bool	check_special(t_data *data, t_token *token, int *i);

t_bool	check_heredoc(t_data *data, t_token *token, int *i)
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

t_bool	check_question(t_data *data, t_token *token, int *i)
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

t_bool	check_blank(t_data *data, t_token *token, int *i, t_bool quote)
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

t_bool	check_other(t_data *data, t_token *token, int *i, t_bool quote)
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
			if (!token->str)
				program_error_exit("bash");
			*i += 1;
		}
		return (TRUE);
	}
	return (FALSE);
}

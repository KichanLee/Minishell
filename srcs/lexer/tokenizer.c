/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:26:13 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/11 15:04:42 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool	tokenizer(t_data *data, t_token **token, int *i);
t_token	*token_create();
t_bool	token_redirect(t_data *data, t_token *token, int *i);
t_bool	token_add_list(t_list **head, t_token **token, t_bool token_flag);

t_bool	tokenizer(t_data *data, t_token **token, int *i)
{
	if (data->input[*i] == '|')
		(*token)->type = T_PIPE;
	else if (data->input[*i] == '\"')
	{
		if (double_quote(data->input, *token, i, data) == FALSE)
			return (FALSE);
	}
	else if (data->input[*i] == '\'')
	{
		if (single_quote(data->input, *token, i) == FALSE)
			return (FALSE);
	}
	else if (data->input[*i] == '<' || data->input[*i] == '>')
	{
		if (token_redirect(data, *token, i) == FALSE)
			return (FALSE);
	}
	if ((data->input[*i] == '\'' || data->input[*i] == '\"') && (data->input[*i + 1] != ' ' && data->input[*i + 1] != '\t'))
		return (TRUE);
	if (token_add_list(&data->tokens, token, TRUE) == FALSE)
		return (FALSE);
	return (TRUE);
}

t_token	*token_create()
{
	t_token	*token;
	
	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL); //list clear
	token->type = T_WORD;
	token->str = ft_strdup("");
	if (!token->str)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

t_bool	token_redirect(t_data *data, t_token *token, int *i)
{
	token->type = T_REDIRECT;
	if (data->input[*i] == '<')
	{
		if (data->input[*i + 1] == '<')
		{
			token->redirect_type = T_HEREDOC;
			*i += 1;
		}
		else
			token->redirect_type = T_INPUT;
	}
	else
	{
		if (data->input[*i + 1] == '>')
		{
			token->redirect_type = T_APPEND;
			*i += 1;
		}
		else
			token->redirect_type = T_OUTPUT;
	}
	return (TRUE);
}

t_bool	token_add_list(t_list **head, t_token **token, t_bool token_flag)
{
	t_list	*new;
	
	new = ft_lstnew();
	if (!new)
		return (FALSE);
	new->token = *token;
	ft_lstadd_back(head, new);
	if (token_flag == TRUE)
	{
		*token = token_create();
		if (!*token)
			return (FALSE);
	}
	return (TRUE);
}

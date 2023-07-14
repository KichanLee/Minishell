/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:26:13 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/14 08:07:55 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	tokenizer(t_data *data, t_token **token, int *i);
t_token	*token_create(void);
void	token_redirect(t_data *data, t_token *token, int *i);
void	token_add_list(t_list **head, t_token **token, t_bool token_flag);

void	tokenizer(t_data *data, t_token **token, int *i)
{
	if (data->input[*i] == '|')
		(*token)->type = T_PIPE;
	else if (data->input[*i] == '\"')
		double_quote(data->input, *token, i, data);
	else if (data->input[*i] == '\'')
		single_quote(data->input, *token, i);
	else if (data->input[*i] == '<' || data->input[*i] == '>')
		token_redirect(data, *token, i);
	if ((data->input[*i] == '\'' || data->input[*i] == '\"') \
		&& (data->input[*i + 1] != ' ' && data->input[*i + 1] != '\t') \
		&& (data->input[*i + 1] != '\0'))
		return ;
	token_add_list(&data->tokens, token, TRUE);
}

t_token	*token_create(void)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		error_exit("bash");
	token->type = T_WORD;
	token->str = ft_strdup("");
	if (!token->str)
		error_exit("bash");
	return (token);
}

void	token_redirect(t_data *data, t_token *token, int *i)
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
}

void	token_add_list(t_list **head, t_token **token, t_bool token_flag)
{
	t_list	*new;

	new = ft_lstnew();
	if (!new)
		error_exit("bash");
	new->token = *token;
	ft_lstadd_back(head, new);
	if (token_flag == TRUE)
	{
		*token = token_create();
		if (!*token)
			error_exit("bash");
	}
}

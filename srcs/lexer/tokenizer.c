/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:26:13 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/17 20:28:42 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	tokenizer(t_data *data, t_token **token, int *i);
t_token	*token_create(void);
void	token_redirect(t_data *data, t_token *token, int *i);
void	token_add_list(t_list **head, t_token **token);

void	tokenizer(t_data *data, t_token **token, int *i)
{
	if (data->input[*i] == '|')
		(*token)->type = T_PIPE;
	else if (data->input[*i] == '\"')
		double_quote(data, data->input, token, i);
	else if (data->input[*i] == '\'')
		single_quote(data->input, token, i);
	else if (data->input[*i] == '<' || data->input[*i] == '>')
		token_redirect(data, *token, i);
	token_add_list(&data->tokens, token);
}

t_token	*token_create(void)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		program_error_exit("bash");
	token->blank = TRUE;
	token->type = T_WORD;
	token->str = ft_strdup("");
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

void	token_add_list(t_list **head, t_token **token)
{
	t_list	*new;

	if ((*token)->type == T_WORD && !(*token)->str[0])
		return ;
	new = ft_lstnew();
	new->token = *token;
	ft_lstadd_back(head, new);
	*token = token_create();
}

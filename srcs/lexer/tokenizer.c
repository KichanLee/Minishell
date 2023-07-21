/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:26:13 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/21 20:54:53 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	tokenizer(t_input *input, t_token **token, int *i);
t_token	*token_create(void);
void	token_redirect(t_input *input, t_token *token, int *i);
void	token_add_list(t_list **head, t_token **token, t_bool token_flag);

void	tokenizer(t_input *input, t_token **token, int *i)
{
	if (input->line[*i] == '|')
	{
		(*token)->type = T_PIPE;
		input->pipe_num++;
		printf("%d\n", input->pipe_num);
	}
	else if (input->line[*i] == '\"')
		double_quote(input->line, *token, i, input);
	else if (input->line[*i] == '\'')
		single_quote(input->line, *token, i);
	else if (input->line[*i] == '<' || input->line[*i] == '>')
		token_redirect(input, *token, i);
	if ((input->line[*i] == '\'' || input->line[*i] == '\"') \
		&& (input->line[*i + 1] != ' ' && input->line[*i + 1] != '\t') \
		&& (input->line[*i + 1] != '\0'))
		return ;
	token_add_list(&input->tokens, token, TRUE);
}

t_token	*token_create(void)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		program_error_exit("bash");
	token->type = T_WORD;
	token->str = ft_strdup("");
	if (!token->str)
		program_error_exit("bash");
	return (token);
}

void	token_redirect(t_input *input, t_token *token, int *i)
{
	token->type = T_REDIRECT;
	if (input->line[*i] == '<')
	{
		if (input->line[*i + 1] == '<')
		{
			token->redirect_type = T_HEREDOC;
			*i += 1;
		}
		else
			token->redirect_type = T_INPUT;
	}
	else
	{
		if (input->line[*i + 1] == '>')
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
		program_error_exit("bash");
	new->token = *token;
	ft_lstadd_back(head, new);
	if (token_flag == TRUE)
	{
		*token = token_create();
		if (!*token)
			program_error_exit("bash");
	}
}

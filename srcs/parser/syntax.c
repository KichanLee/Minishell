/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:24:38 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/14 14:10:38 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void		syntax(t_data *data);
static void	syntax_none(t_list *cur);
static void	syntax_word(t_list *cur);
static void	syntax_redirect(t_list *cur);
static void	syntax_pipe(t_list *cur);

void	syntax(t_data *data)
{
	t_list	*cur;

	cur = data->tokens;
	syntax_none(cur);
	cur = cur->next;
	while (cur)
	{
		if (cur->token->type == T_WORD)
			syntax_word(cur);
		else if (cur->token->type == T_PIPE)
			syntax_pipe(cur);
		else if (cur->token->type == T_REDIRECT)
			syntax_redirect(cur);
		cur = cur->next;
	}
}

static void	syntax_none(t_list *cur)
{
	if (cur->token->type == T_WORD)
		cur->token->type = T_CMD;
	else if (cur->token->type == T_PIPE)
		syntax_error_exit(E_SYNTAX_PIPE);
}

static void	syntax_word(t_list *cur)
{
	if (cur->pre->token->type == T_ARG \
		&& cur->pre->pre->token->type == T_REDIRECT)
		cur->token->type = T_CMD;
	else if (cur->pre->token->type == T_CMD \
		|| cur->pre->token->type == T_ARG \
		|| cur->pre->token->type == T_REDIRECT)
		cur->token->type = T_ARG;
	else if (cur->pre->token->type == T_PIPE)
		cur->token->type = T_CMD;
}

static void	syntax_redirect(t_list *cur)
{
	if (cur->pre->token->type == T_REDIRECT)
	{
		if (cur->token->redirect_type == T_INPUT)
			syntax_error_exit(E_SYNTAX_INPUT);
		if (cur->token->redirect_type == T_OUTPUT)
			syntax_error_exit(E_SYNTAX_OUTPUT);
		if (cur->token->redirect_type == T_HEREDOC)
			syntax_error_exit(E_SYNTAX_HEREDOC);
		if (cur->token->redirect_type == T_APPEND)
			syntax_error_exit(E_SYNTAX_APPEND);
	}
	if (!cur->next)
		syntax_error_exit(E_SYNTAX_NEWLINE);
}

static void	syntax_pipe(t_list *cur)
{
	if (cur->pre->token->type == T_PIPE)
		syntax_error_exit(E_SYNTAX_PIPE);
	if (cur->pre->token->type == T_REDIRECT)
		syntax_error_exit(E_SYNTAX_PIPE);
	if (!cur->next)
		syntax_error_exit(E_SYNTAX_NEWLINE);
}

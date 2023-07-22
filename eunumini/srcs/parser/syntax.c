/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:24:38 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/17 06:40:42 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool			syntax(t_data *data);
static t_bool	syntax_none(t_data *data, t_list *cur);
static void		syntax_word(t_list *cur);
static t_bool	syntax_redirect(t_data *data, t_list *cur);
static t_bool	syntax_pipe(t_data *data, t_list *cur);

t_bool	syntax(t_data *data)
{
	t_list	*cur;

	cur = data->tokens;
	if (syntax_none(data, cur) == FALSE)
		return (FALSE);
	cur = cur->next;
	while (cur)
	{
		if (cur->token->type == T_WORD)
			syntax_word(cur);
		else if (cur->token->type == T_PIPE)
		{
			if (syntax_pipe(data, cur) == FALSE)
				return (FALSE);
		}
		else if (cur->token->type == T_REDIRECT)
		{
			if (syntax_redirect(data, cur) == FALSE)
				return (FALSE);
		}
		cur = cur->next;
	}
	return (TRUE);
}

static t_bool	syntax_none(t_data *data, t_list *cur)
{
	if (cur->token->type == T_WORD)
		cur->token->type = T_CMD;
	else if (cur->token->type == T_PIPE)
		return (error_back_readline(data, E_SYNTAX_PIPE, 258));
	return (TRUE);
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

static t_bool	syntax_redirect(t_data *data, t_list *cur)
{
	if (cur->pre->token->type == T_REDIRECT)
	{
		if (cur->token->redirect_type == T_INPUT)
			return (error_back_readline(data, E_SYNTAX_INPUT, 258));
		if (cur->token->redirect_type == T_OUTPUT)
			return (error_back_readline(data, E_SYNTAX_OUTPUT, 258));
		if (cur->token->redirect_type == T_HEREDOC)
			return (error_back_readline(data, E_SYNTAX_HEREDOC, 258));
		if (cur->token->redirect_type == T_APPEND)
			return (error_back_readline(data, E_SYNTAX_APPEND, 258));
	}
	if (!cur->next)
		return (error_back_readline(data, E_SYNTAX_NEWLINE, 258));
	return (TRUE);
}

static t_bool	syntax_pipe(t_data *data, t_list *cur)
{
	if (cur->pre->token->type == T_PIPE)
		return (error_back_readline(data, E_SYNTAX_PIPE, 258));
	if (cur->pre->token->type == T_REDIRECT)
		return (error_back_readline(data, E_SYNTAX_PIPE, 258));
	if (!cur->next)
		return (error_back_readline(data, E_SYNTAX_NEWLINE, 258));
	return (TRUE);
}

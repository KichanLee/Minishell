/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:36:15 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/12 08:36:48 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	syntax_error_check_pipe(t_list *cur);
void	syntax_error_check_redirect(t_list *cur);

void	syntax_error_check_pipe(t_list *cur)
{
	if (cur->pre->token->type == T_REDIRECT)
		syntax_error_exit(E_SYNTAX_PIPE);
	else if (!cur->next)
		syntax_error_exit(E_SYNTAX_NEWLINE);
}

void	syntax_error_check_redirect(t_list *cur)
{
	if (!cur->pre)
		return ;
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
	else if (!cur->next)
		syntax_error_exit(E_SYNTAX_NEWLINE);
}
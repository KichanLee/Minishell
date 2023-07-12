/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 07:53:54 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/12 16:40:33 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "struct.h"

# define E_SYNTAX_PIPE "bash: syntax error near unexpected token `|'"
# define E_SYNTAX_INPUT "bash: syntax error near unexpected token `<'"
# define E_SYNTAX_OUTPUT "bash: syntax error near unexpected token `>'"
# define E_SYNTAX_HEREDOC "bash: syntax error near unexpected token `<<'"
# define E_SYNTAX_APPEND "bash: syntax error near unexpected token `>>'"
# define E_SYNTAX_NEWLINE "bash: syntax error near unexpected token `newline'"

void	tokenizer(t_data *data, t_token **token, int *i);
t_token	*token_create();
void	token_add_list(t_list **head, t_token **token, t_bool token_flag);
void	token_redirect(t_data *data, t_token *token, int *i);

void 	single_quote(char *input, t_token *token, int *i);
void	double_quote(char *input, t_token *token, int *i, t_data *data);

void	lexer(t_data *data);

void	syntax(t_data *data);

void	parser(t_data *data);

void	expand(t_data *data, t_token *token, int *i, t_bool quote);

#endif
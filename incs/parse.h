/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 07:53:54 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/11 19:12:49 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "struct.h"

# define E_PIPE "bash: syntax error near unexpected token `|'"
# define E_RE_IN "bash: syntax error near unexpected token `<'"
# define E_RE_OUT "bash: syntax error near unexpected token `>'"
# define E_NEWLINE "bash: syntax error near unexpected token `newline'"

t_bool	tokenizer(t_data *data, t_token **token, int *i);
t_token	*token_create();
t_bool	token_add_list(t_list **head, t_token **token, t_bool token_flag);
t_bool	token_redirect(t_data *data, t_token *token, int *i);

t_bool 	single_quote(char *input, t_token *token, int *i);
t_bool	double_quote(char *input, t_token *token, int *i, t_data *data);

t_bool	lexer(t_data *data);

t_bool	expand(t_data *data, t_token *token, int *i, t_bool quote);

#endif
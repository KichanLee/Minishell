/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 07:53:54 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/17 09:33:03 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "struct.h"

void	tokenizer(t_data *data, t_token **token, int *i);
t_token	*token_create(void);
void	token_add_list(t_list **head, t_token **token, t_bool create_flag);
void	token_redirect(t_data *data, t_token *token, int *i);

void	single_quote(char *input, t_token **token, int *i);
void	double_quote(t_data *data, char *input, t_token **token, int *i);

void	lexer(t_data *data);

t_bool	expand(t_data *data, t_token **token, int *i, t_bool quote);

/*expand_check*/
t_bool	check_heredoc(t_data *data, t_token *token, int *i);
t_bool	check_question(t_data *data, t_token *token, int *i);
t_bool	check_d_quote(t_data *data, t_token *token, int *i, t_bool quote);
t_bool	check_other(t_data *data, t_token *token, int *i, t_bool quote);
t_bool	check_special(t_data *data, t_token *token, int *i);

/*lexer_uitls*/
t_bool	check_end(char c);
t_bool	check_last_blank(char *str, int i);
void	quote_utils(char *input, t_token **token, int *i);

t_bool	syntax(t_data *data);

void	parser(t_data *data);

#endif
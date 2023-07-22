/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 07:53:54 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/17 07:09:31 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "struct.h"

void	tokenizer(t_data *data, t_token **token, int *i);
t_token	*token_create(void);
void	token_add_list(t_list **head, t_token **token, t_bool token_flag);
void	token_redirect(t_data *data, t_token *token, int *i);

void	single_quote(char *input, t_token *token, int *i);
void	double_quote(char *input, t_token *token, int *i, t_data *data);

void	lexer(t_data *data);

t_bool	syntax(t_data *data);

void	parser(t_data *data);

t_bool	expand(t_data *data, t_token *token, int *i, t_bool quote);

#endif
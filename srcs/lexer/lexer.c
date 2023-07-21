/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:24:37 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/21 20:55:32 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void		lexer(t_input *input);
static void	check_char(t_input *input, t_token **token, int *i);

void	lexer(t_input *input)
{
	int			i;
	t_token		*token;

	token = token_create();
	if (!token)
		program_error_exit("bash");
	i = -1;
	while (input->line[++i])
		check_char(input, &token, &i);
	if (token->str && *(token->str))
		token_add_list(&input->tokens, &token, FALSE);
}

static void	check_char(t_input *input, t_token **token, int *i)
{
	if (input->line[*i] == '|' \
		|| input->line[*i] == '<' || input->line[*i] == '>')
	{
		if (*(*token)->str)
			token_add_list(&input->tokens, token, TRUE);
		tokenizer(input, token, i);
	}
	else if (input->line[*i] == '\'' || input->line[*i] == '\"')
	{
		tokenizer(input, token, i);
	}
	else if (input->line[*i] == ' ' || input->line[*i] == '\t')
	{
		if (*(*token)->str)
			token_add_list(&input->tokens, token, TRUE);
	}
	else if (input->line[*i] == '$')
		expand(input, *token, i, FALSE);
	else
	{
		(*token)->str = ft_strncat((*token)->str, &input->line[*i], 1);
		if (!(*token)->str)
			program_error_exit("bash");
	}
}

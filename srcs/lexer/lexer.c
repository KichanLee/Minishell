/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:24:37 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/19 17:01:28 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool		lexer(t_data *data);
static void	check_char(t_data *data, t_token **token, int *i, t_bool *pre_pipe);
static void	blank_char(t_data *data, t_token **token, int *i, t_bool *pre_pipe);
static void	normal_char(t_data *data, t_token **token, int *i);

t_bool	lexer(t_data *data)
{
	int			i;
	t_token		*token;
	t_bool		pre_pipe;
	t_list		*last_token;

	pre_pipe = FALSE;
	token = token_create();
	i = -1;
	while (data->input[++i])
		check_char(data, &token, &i, &pre_pipe);
	free(token->str);
	free(token);
	if (!data->tokens)
		return (FALSE);
	last_token = ft_lstlast(data->tokens);
	last_token->token->blank = FALSE;
	return (TRUE);
}

static void	check_char(t_data *data, t_token **token, int *i, t_bool *pre_pipe)
{
	if (data->input[*i] == '|' \
		|| data->input[*i] == '<' \
		|| data->input[*i] == '>' \
		|| data->input[*i] == '\'' \
		|| data->input[*i] == '\"')
		tokenizer(data, token, i);
	else if (data->input[*i] == '$')
	{
		expand(data, token, i, FALSE);
		token_add_list(&data->tokens, token);
	}
	else if (data->input[*i] == ' ' || data->input[*i] == '\t')
		blank_char(data, token, i, pre_pipe);
	else
		normal_char(data, token, i);
}

static void	blank_char(t_data *data, t_token **token, int *i, t_bool *pre_pipe)
{
	if (*pre_pipe == TRUE)
	{
		*pre_pipe = FALSE;
		return ;
	}
	while (data->input[*i] == ' ' || data->input[*i] == '\t')
		*i += 1;
	if (data->input[*i] == '|')
		*pre_pipe = TRUE;
	token_add_list(&data->tokens, token);
	*i -= 1;
}

static void	normal_char(t_data *data, t_token **token, int *i)
{
	(*token)->blank = FALSE;
	(*token)->str = ft_strncat((*token)->str, &data->input[*i], 1);
	(*token)->blank = check_last_blank(data->input, *i + 1);
	if (data->input[*i + 1] == '|' \
		|| data->input[*i + 1] == '<' \
		|| data->input[*i + 1] == '>' \
		|| data->input[*i + 1] == '\'' \
		|| data->input[*i + 1] == '\"' \
		|| data->input[*i + 1] == '$' \
		|| data->input[*i + 1] == '\0')
		token_add_list(&data->tokens, token);
}

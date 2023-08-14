/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:24:37 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/13 16:54:50 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void		lexer(t_data *data);
static void	check_char(t_data *data, t_token **token, int *i, t_bool *pre_pipe);
static void	blank_char(t_data *data, t_token **token, int *i, t_bool *pre_pipe);
static void	normal_char(t_data *data, t_token **token, int *i);

void	lexer(t_data *data)
{
	int			i;
	t_token		*token;
	t_bool		pre_pipe;

	pre_pipe = FALSE;
	token = token_create();
	if (!token)
		program_error_exit("bash");
	i = -1;
	while (data->input[++i])
		check_char(data, &token, &i, &pre_pipe);
	free(token->str);
	free(token);
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
		token_add_list(&data->tokens, token, TRUE);
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
	token_add_list(&data->tokens, token, TRUE);
	*i -= 1;
}

static void	normal_char(t_data *data, t_token **token, int *i)
{
	(*token)->blank = FALSE;
	(*token)->str = ft_strncat((*token)->str, &data->input[*i], 1);
	if (!(*token)->str)
		program_error_exit("bash");
	if (check_end(data->input[*i + 1]) == TRUE \
		&& check_last_blank(data->input, *i + 1) == FALSE)
		(*token)->blank = TRUE;
	if (data->input[*i + 1] == '|' \
		|| data->input[*i + 1] == '<' \
		|| data->input[*i + 1] == '>' \
		|| data->input[*i + 1] == '\'' \
		|| data->input[*i + 1] == '\"' \
		|| data->input[*i + 1] == '$' \
		|| data->input[*i + 1] == '\0')
		token_add_list(&data->tokens, token, TRUE);
}

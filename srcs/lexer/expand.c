/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:20:49 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/16 22:03:49 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool			expand(t_data *data, t_token **token, int *i, t_bool quote);
static void		replace(t_data *data, t_token *token, char *name);
static char		*get_name(t_data *data, int *i);

t_bool	expand(t_data *data, t_token **token, int *i, t_bool quote)
{
	char	*name;

	*i += 1;
	if (check_heredoc(data, *token, i) == FALSE \
		&& check_question(data, *token, i) == FALSE \
		&& check_blank(data, *token, i, quote) == FALSE \
		&& check_other(data, *token, i, quote) == FALSE \
		&& check_special(data, *token, i) == FALSE)
	{
		name = get_name(data, i);
		replace(data, *token, name);
	}
	if (quote == FALSE)
	{
		(*token)->blank = check_end(data->input[*i]);
		*i -= 1;
	}
	return (FALSE);
}

static char	*get_name(t_data *data, int *i)
{
	char	*name;

	name = ft_strdup("");
	if (!name)
		program_error_exit("bash");
	while (ft_isalnum(data->input[*i]) || data->input[*i] == '_')
	{
		name = ft_strncat(name, &data->input[*i], 1);
		if (!name)
			program_error_exit("bash");
		*i += 1;
	}
	return (name);
}

static void	replace(t_data *data, t_token *token, char *name)
{
	int		j;
	t_list	*tmp;

	tmp = env_search(data, name, TRUE);
	if (tmp)
	{
		j = 0;
		while (tmp->env[j] != '=')
			j++;
		token->str = ft_strncat(token->str, \
			&tmp->env[j + 1], ft_strlen(&tmp->env[j + 1]));
		if (!token->str)
			program_error_exit("bash");
	}
	free(name);
}

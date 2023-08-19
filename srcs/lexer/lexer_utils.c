/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:15:15 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/19 17:01:32 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool	check_end(char c);
t_bool	check_last_blank(char *str, int i);
void	quote_utils(char *input, t_token **token, int *i);

t_bool	check_end(char c)
{
	if (c == ' ' || c == '\t' || c == '\0')
		return (TRUE);
	return (FALSE);
}

t_bool	check_last_blank(char *str, int i)
{
	char	c;

	c = str[i];
	while (c == '\'' || c == '\"')
	{
		c = str[i];
		if (str[i + 1] == c)
			i += 2;
		else
			break ;
	}
	return (check_end(str[i]));
}

void	quote_utils(char *input, t_token **token, int *i)
{
	if (check_end(input[*i + 1]) == FALSE)
		(*token)->blank = FALSE;
	if (input[*i] == '\0')
		*i -= 1;
}

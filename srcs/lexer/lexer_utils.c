/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:15:15 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/13 17:02:47 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool	check_end(char c)
{
	if (c == ' ' || c == '\t' || c == '\0')
		return (TRUE);
	return (FALSE);
}

t_bool	check_last_blank(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0' || str[i] == '|')
		return (TRUE);
	return (FALSE);
}

void	quote_utils(char *input, t_token **token, int *i)
{
	if (check_end(input[*i + 1]) == FALSE \
		|| check_last_blank(input, *i + 1) == TRUE)
		(*token)->blank = FALSE;
	if (input[*i] == '\0')
		*i -= 1;
}

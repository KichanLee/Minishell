/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:15:15 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/13 14:09:25 by eunwolee         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:35:07 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/12 12:11:37 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool	parser(t_data *data)
{
	t_list	*cur;

	cur = data->tokens;
	while (cur)
	{
		
		cur = cur->next;
	}
}
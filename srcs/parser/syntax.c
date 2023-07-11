/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:24:38 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/11 19:26:51 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	check_pipe(t_list *cur)
{

}

static void	check_re_in(t_list *cur)
{

}

static void	check_re_out(t_list *cur)
{

}

t_bool	syntax(t_data *data)
{
	t_list	*cur;

	cur = data->tokens;
	while (cur)
	{
		if (cur->token->type == T_PIPE)
		{
			if (cur.)
		}
		if (cur->token->type == )
		cur = cur->next;
	}
}
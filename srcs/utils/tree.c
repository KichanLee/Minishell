/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:48:39 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/11 18:43:21 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_leaf	*t_create_leaf(t_token *token, t_bool exist)
{
	t_leaf	*new;

	new = (t_leaf *)ft_calloc(1, sizeof(t_leaf));
	if (!new)
		return (NULL);
	new->token = token;
	new->exist = exist;
	new->left_child = NULL;
	new->right_child = NULL;
	return (new);
}

t_bool	t_add_left(t_leaf *parent, t_leaf *new)
{
	if (!parent || parent->left_child || !new)
		return (FALSE);
	parent->left_child = new;
	return (TRUE);
}

t_bool	t_add_right(t_leaf *parent, t_leaf *new)
{
	if (!parent || parent->right_child || !new)
		return (FALSE);
	parent->right_child = new;
	return (TRUE);
}

// t_leaf	*t_preorder(t_data *data)
// {
	
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:48:39 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/12 19:45:31 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_leaf	*tree_create_leaf(t_leaf *parent, int leaf_type);
t_bool	tree_add_left(t_leaf *parent, t_token *new_token, int leaf_type);
t_bool	tree_add_right(t_leaf *parent, t_token *new_token, int leaf_type);
void	tree_clear(t_leaf *leaf);

t_leaf	*tree_create_leaf(t_leaf *parent, int leaf_type)
{
	t_leaf	*new;

	new = (t_leaf *)ft_calloc(1, sizeof(t_leaf));
	if (!new)
		return (NULL);
	new->leaf_type = leaf_type;
	new->parent = parent;
	new->left_child = NULL;
	new->right_child = NULL;
	return (new);
}

t_bool	tree_add_left(t_leaf *parent, t_token *new_token, int leaf_type)
{
	t_leaf	*child;

	if (!parent || !new_token)
		return (FALSE);
	while (parent->left_child)
		parent = parent->left_child;
	child = tree_create_leaf(parent, leaf_type);
	child->token = new_token;
	parent->left_child = child;
	return (TRUE);
}

t_bool	tree_add_right(t_leaf *parent, t_token *new_token, int leaf_type)
{
	t_leaf	*child;

	if (!parent || !new_token)
		return (FALSE);
	while (parent->right_child)
		parent = parent->right_child;
	child = tree_create_leaf(parent, leaf_type);
	child->token = new_token;
	parent->right_child = child;
	return (TRUE);
}

//토큰은 환경변수 리스트에서 삭제하기 때문에 트리의 큰 틀만 삭제
void	tree_clear(t_leaf *leaf)
{
	if (!leaf)
		return ;
	free(leaf);
	tree_clear(leaf->left_child);
	tree_clear(leaf->left_child);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:20:41 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/13 21:58:50 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**input_leaf(t_leaf *com_leaf, char **input)
{
	t_leaf	*leaf;
	int		i;
	char	**str;

	i = 1;
	leaf = com_leaf;
	str = input;
	while (leaf)
	{
		if (leaf->right_child)
		{
			str[i] = leaf->right_child->token->str;
			leaf = leaf->right_child;
			i++;
		}
		else
			break ;
	}
	return (str);
}

char	**join_cmd(t_leaf *com_leaf)
{
	int		i;
	char	**str;
	t_leaf	*temp;
	t_leaf	*leaf;

	i = 1;
	temp = com_leaf;
	leaf = com_leaf;
	while (temp && temp->right_child)
	{
		temp = temp->right_child;
		i++;
	}
	str = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!str)
		return (NULL);
	str[0] = leaf->token->str;
	str = input_leaf(leaf, str);
	return (str);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	add_env_front(t_data *head, char *key, char *value)
{
	if (head->envs == NULL)
		head->envs = create_env_node(key, value);
	else
		ft_lstadd_front(&(head->envs), create_env_node(key, value));
}

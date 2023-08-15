/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 22:15:42 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/15 16:09:34 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char		**ft_join_cmd(t_leaf *com_leaf);
static char	**input_leaf(t_leaf *com_leaf, char **input);

char	**ft_join_cmd(t_leaf *com_leaf)
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

static char	**input_leaf(t_leaf *com_leaf, char **input)
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

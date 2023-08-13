/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:20:41 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/13 17:15:16 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (*args != NULL)
	{
		count++;
		args++;
	}
	return (count);
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
	i = 1;
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

t_list	*create_env_node(char *key, char *value)
{
	t_list	*new_node;
	char	*key_equal;

	new_node = (t_list *)ft_calloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->token = (t_token *)ft_calloc(sizeof(t_token));
	if (!new_node->token)
	{
		free(new_node);
		return (NULL);
	}
	new_node->token->type = T_CMD;
	new_node->token->redirect_type = 0;
	new_node->token->str = key;
	key_equal = (char *)ft_calloc(sizeof(char), ft_strlen(key) + 2);
	key_equal = ft_strdup(key);
	key_equal[ft_strlen(key)] = '=';
	key_equal[ft_strlen(key) + 1] = '\0';
	new_node->env = ft_strjoin(key_equal, value);
	return (new_node);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new -> next = *lst;
	*lst = new;
}

void	add_env_front(t_data *head, char *key, char *value)
{
	if (head->envs == NULL)
		head->envs = create_env_node(key, value);
	else
		ft_lstadd_front(&(head->envs), create_env_node(key, value));
}

void	update_env(t_data *data, char *key, char *value)
{
	t_list	*tmp;
	char	*key_equal;

	tmp = env_search(data, key);
	if (!tmp)
		add_env_front(data, key, value);
	else
	{
		free(tmp->env);
		key_equal = (char *)ft_calloc(sizeof(char), ft_strlen(key) + 2);
		key_equal = ft_strdup(key);
		key_equal[ft_strlen(key)] = '=';
		key_equal[ft_strlen(key) + 1] = '\0';
		tmp->env = ft_strjoin(key_equal, value);
	}
}

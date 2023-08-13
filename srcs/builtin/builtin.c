/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:42:18 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/13 21:58:42 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	check_bulitin_func(char *name)
{
	if (!ft_strncmp(name, "cd", 3))
		return (1);
	if (!ft_strncmp(name, "echo", 5))
		return (2);
	if (!ft_strncmp(name, "exit", 5))
		return (3);
	if (!ft_strncmp(name, "pwd", 4))
		return (4);
	if (!ft_strncmp(name, "unset", 6))
		return (5);
	if (!ft_strncmp(name, "export", 7))
		return (6);
	if (!ft_strncmp(name, "env", 4))
		return (7);
	return (0);
}

void	exec_bulitin(int bulitnum, t_data *data)
{
	if (bulitnum == 1)
		ft_cd(data, data->root);
	else if (bulitnum == 2)
		ft_echo(data->root->left_child->right_child);
	else if (bulitnum == 3)
		ft_exit(data, data->root);
	else if (bulitnum == 4)
		ft_pwd(data, data->root);
	else if (bulitnum == 5)
		ft_unset(data, data->root);
	else if (bulitnum == 6)
		ft_export(data, data->root);
	else if (bulitnum == 7)
		ft_env(data, data->root);
}

int	count_args(char **args)
{
	int	count;

	 count= 0;
	while (*args != NULL)
	{
		count++;
		args++;
	}
	return (count);
}

t_list	*create_env_node(char *key, char *value)
{
	t_list	*new_node;
	char	*key_equal;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->pre = NULL;
	new_node->next = NULL;
	new_node->token = (t_token *)malloc(sizeof(t_token));
	if (!new_node->token)
	{
		free(new_node);
		return (NULL);
	}
	new_node->token->type = T_CMD;
	new_node->token->redirect_type = 0;
	new_node->token->str = key;

	if(value[0] != ' ')
	{
		key_equal = (char *)ft_calloc(ft_strlen(key) + 2, sizeof(char));
		key_equal = ft_strdup(key);
		key_equal[ft_strlen(key)] = '=';
		key_equal[ft_strlen(key) + 1] = '\0';
		new_node->env = ft_strjoin(key_equal, value);
	}
	else
	{
		key_equal = (char *)ft_calloc(ft_strlen(key) + 1, sizeof(char));
		key_equal = ft_strdup(key);
		key_equal[ft_strlen(key)] = '\0';
		new_node->env = key_equal;
	}
	return (new_node);
}

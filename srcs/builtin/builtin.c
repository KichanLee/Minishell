/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:42:18 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/14 20:39:23 by eunwolee         ###   ########.fr       */
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
		ft_pwd();
	else if (bulitnum == 5)
		ft_unset(data, data->root);
	else if (bulitnum == 6)
		ft_export(data);
	else if (bulitnum == 7)
		ft_env(data, data->root);
}

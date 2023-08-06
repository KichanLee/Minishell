/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:42:18 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/06 14:43:55 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int check_bulitin_func(char *name)
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
	return (0);
}
void exec_bulitin(int bulitnum,t_data *data , t_leaf *leaf)
{
    if (bulitnum == 1)
		ft_cd(data, leaf);
	else if (bulitnum == 2)
		ft_echo(leaf);
	else if (bulitnum == 3)
		ft_exit(data, leaf);
	else if (bulitnum == 4)
		ft_pwd(data, leaf);
	else if (bulitnum == 5)
		ft_unset(data, leaf);
	else if (bulitnum == 6)
		ft_export(data, leaf);
}

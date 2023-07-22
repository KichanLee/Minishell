/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:42:18 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/22 11:57:28 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*(*get_builtin_func(char *name))(t_data *, t_leaf *)
{
    if (!ft_strncmp(name, "cd", 3))
		return (ft_cd);
	if (!ft_strncmp(name, "echo", 5))
		return (ft_echo);
	if (!ft_strncmp(name, "exit", 5))
		return (ft_exit);
	if (!ft_strncmp(name, "pwd", 4))
		return (ft_pwd);
	if (!ft_strncmp(name, "unset", 6))
		return (ft_unset);
	if (!ft_strncmp(name, "export", 7))
		return (ft_export);
	return (NULL);
}
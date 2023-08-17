/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>             +#+  +:+       +#+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:15:04 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/07 14:49:51 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool	ft_env(t_data *data);

t_bool	ft_env(t_data *data)
{
	char	**cmd;
	int		arg_cnt;

	cmd = ft_join_cmd(data->root->left_child->right_child);
	arg_cnt = ft_cnt_args(cmd);
	if (arg_cnt != 1)
	{
		printf("env: %s: No such file or directory\n", cmd[1]);
		free_d_char_ptr(cmd);
		return (FALSE);
	}
	free_d_char_ptr(cmd);
	env_print(data);
	return (TRUE);
}

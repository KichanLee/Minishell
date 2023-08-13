/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:51:02 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/13 16:42:31 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_unset(t_data *data, t_leaf *cur_root);

void	ft_unset(t_data *data, t_leaf *cur_root)
{
	char	**cmd;
	int		arg_cnt;
	int		i;

	cmd = join_cmd(cur_root->left_child->right_child);
	arg_cnt = count_args(cmd);
	i = 1;
	while (i < arg_cnt)
	{
		env_remove(data, cmd[i]);
		++i;
	}
	data->env_array = env_to_array(data);
}

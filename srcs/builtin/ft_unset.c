/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:51:02 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/14 20:49:38 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_unset(t_data *data, t_leaf *cur_root);

void	ft_unset(t_data *data, t_leaf *cur_root)
{
	char	**cmd;
	int		arg_cnt;
	int		i;

	cmd = ft_join_cmd(cur_root->left_child->right_child);
	arg_cnt = ft_count_args(cmd);
	i = 1;
	while (i < arg_cnt)
	{
		env_remove(data, cmd[i]);
		++i;
	}
	free(cmd);
}

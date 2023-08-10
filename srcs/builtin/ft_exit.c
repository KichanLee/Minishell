/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:23:29 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/11 06:30:45 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	arg_over_two(t_data *data, int count, char **cmd, int flag)
{
	int	status;
	int	i;

	i = 1;
	status = char_to_long_long(cmd[1], &flag);
	(void)status;
	while (i < count)
	{
		if (flag && is_num_str(cmd[i]) && ft_strlen(cmd[i]) <= 20)
		{
			printf("bash: exit: too many arguments\n");
			data->error_code = 1;
			break ;
		}
		else
			exit_not_num(data, cmd[i]);
		++i;
	}
}

void	arg_over_one(t_data *data, int count, char **cmd, int flag)
{
	int	status;

	if (count == 2)
	{
		status = char_to_long_long(cmd[1], &flag);
		if (flag && is_num_str(cmd[1]) && ft_strlen(cmd[1]) <= 20)
		{
			printf("exit\n");
			data->error_code = status % 256;
			exit(status % 256);
		}
		else
			exit_not_num(data, cmd[1]);
	}
	else
		arg_over_two(data, count, cmd, flag);
}

void	ft_exit(t_data *data, t_leaf *cur_root)
{
	long long	status;
	char		**cmd;
	int			count;
	int			flag;

	cmd = join_cmd(cur_root->left_child->right_child);
	count = count_args(cmd);
	flag = 1;
	status = 0;
	if (count == 1)
	{
		printf("exit\n");
		exit(status);
	}
	else
		arg_over_one(data, count, cmd, flag);
}

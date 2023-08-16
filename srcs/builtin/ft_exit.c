/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:23:29 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/16 22:23:26 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void		ft_exit(t_data *data);
static void	arg_over_one(t_data *data, int count, char **cmd, int flag);
static void	arg_over_two(t_data *data, int count, char **cmd, int flag);
static void	exit_not_num(t_data *data, char *str);
static int	is_num_str(char *str);

void	ft_exit(t_data *data)
{
	long long	status;
	char		**cmd;
	int			count;
	int			flag;

	cmd = ft_join_cmd(data->root->left_child->right_child);
	count = ft_cnt_args(cmd);
	flag = 1;
	status = 0;
	if (count == 1)
	{
		printf("exit\n");
		exit(status);
	}
	else
		arg_over_one(data, count, cmd, flag);
	free_d_char_ptr(cmd);
}

static void	arg_over_one(t_data *data, int count, char **cmd, int flag)
{
	int	status;

	if (count == 2)
	{
		if (!ft_strncmp("-9223372036854775808", cmd[1], 20))
		{
			printf("exit\n");
			data->error_code = 0;
			exit(0);
		}
		status = ft_atolong(cmd[1], &flag);
		if (flag && is_num_str(cmd[1]) && ft_strlen(cmd[1]) <= 20)
		{
			printf("exit\n");
			data->error_code = status % 256;
			exit(status % 256);
		}
		exit_not_num(data, cmd[1]);
	}
	else
		arg_over_two(data, count, cmd, flag);
}

static void	arg_over_two(t_data *data, int count, char **cmd, int flag)
{
	int			i;

	i = 1;
	// status = ft_atolong(cmd[1], &flag);
	ft_atolong(cmd[1], &flag);
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

static void	exit_not_num(t_data *data, char *str)
{
	printf("exit\n");
	printf("bash: exit: %s: numeric argument required\n", str);
	data->error_code = 255;
	exit(255);
}

static int	is_num_str(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

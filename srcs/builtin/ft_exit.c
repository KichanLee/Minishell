/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:23:29 by kichan            #+#    #+#             */
/*   Updated: 2023/07/22 13:24:11 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static int	is_num_str(char *str);
static void	exit_not_num(t_data *data);

t_bool	ft_exit(t_data *data, t_leaf *cur_root)
{
	int		status;
    char    **cmd;
	int		count;
	
    cmd = join_cmd(data->input->root->left_child->right_child);
    count = count_args(cmd);
	status = 0;
	if (count == 1)
	{
		printf("exit\n");
		exit(status);
	}
	else if (count == 2)
	{
		if (is_num_str(cmd[1]))
		{
			status = ft_atoi(cmd[1]);
			printf("exit\n");
			exit(status);
		}
		else
			exit_not_num(data);
	}
	else
	{
		printf("bash: exit: too many arguments\n");
		status = 1;
	}
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

static void	exit_not_num(t_data *data)
{
	printf("exit\n");
	printf("bash: exit: %s: numeric argument required\n", data->input->root->left_child->right_child->token->str);
	exit(255);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:23:29 by kichan            #+#    #+#             */
/*   Updated: 2023/08/08 18:49:29 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static int	is_num_str(char *str);
static void	exit_not_num(t_data *data, t_leaf *cur_root);






/**
 *  1. 두번째 인자 
 * 		1)  exit 다음 숫자는 long long 형 범위까지이다. 
 * 			-9,223,372,036,854,775,808 ~ 9,223,372,036,854,775,807
 * 	   		까지는 정상적으로 종료가 되어야 한다. 
 * 	 	2) longlong 형범위를 초과해서 입력해주는 경우에는 255 error가 발생한다.
 *  2.  
 * 
 * 
*/

void	ft_exit(t_data *data, t_leaf *cur_root)
{
	long long	status;
    char    	**cmd;
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
	else if (count == 2)
	{
		if (is_num_str(cmd[1]) && ft_strlen(cmd[1]) < 20)
		{
			status = ft_atoi(cmd[1]);// ft_atolong(cmd[1], &flag);
			if(flag == 1)
			{
				printf("exit\n");
				data->error_code = status % 256;
				exit(status % 256);
			}
			else
				exit_not_num(data, cur_root);
		}
		else
			exit_not_num(data, cur_root);
	}
	else
	{
		printf("bash: exit: too many arguments\n");
		data->error_code = 1;
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

static void	exit_not_num(t_data *data, t_leaf *cur_root)
{
	(void)data;
	
	printf("exit\n");
	printf("bash: exit: %s: numeric argument required\n", cur_root->left_child->right_child->token->str);
	data->error_code = 255;
	exit(255);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 02:30:59 by kichan            #+#    #+#             */
/*   Updated: 2023/07/22 13:21:19 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_bool		ft_echo(t_data *data, t_leaf *cur_root);
static void	check_echo_flag(char **av, int *i, int *flag);

t_bool	ft_echo(t_data *data, t_leaf *cur_root)
{
	char **cmd;
	int cnt;
	int flag = 0;
	// int i = 0;
	int blank = 0;
	cmd = join_cmd(data->input->root->left_child->right_child);
	int k = 1;
	check_echo_flag(cmd, &cnt, &flag);
	blank = count_args(cmd);
	if(flag == 1)
		k = 2;
	while (cmd[k])
	{
		printf("%s", cmd[k]);
		if(k < blank - 1)
			printf(" ");
		++k;
	}
	if(flag == 0)
		printf("\n");
}

static void	check_echo_flag(char **av, int *i, int *flag)
{
	int	j;

	*i = 1;
	if (av[1] && av[*i][0] == '-' && av[*i][1] == 'n')
	{
		while (av[*i][0] == '-' && av[*i][1] == 'n')
		{
			j = 1;
			while (av[1][j] != '\0')
			{
				if (av[1][j] != 'n')
					return ;
				j++;
			}
			(*i)++;
		}
		*flag = 1;
	}
}

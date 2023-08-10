/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 02:30:59 by kichan            #+#    #+#             */
/*   Updated: 2023/08/10 22:21:47 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void		ft_echo(t_leaf *cur_root);
static void	check_flag(char **av, int *idx, int *flag);
static void	print_line(char *line);

void	ft_echo(t_leaf *cur_root)
{
	int i;
	int flag;
	int blank;
	char **cmd;

	cmd = join_cmd(cur_root->left_child->right_child);
	blank = count_args(cmd);
	i = 1;
	flag = FALSE;
	check_flag(cmd, &i, &flag);
	while (cmd[i])
	{
		print_line(cmd[i]);
		if(i < blank - 1)
			printf(" ");
		i++;
	}
	if (flag == FALSE)
		printf("\n");
}

static void	check_flag(char **av, int *idx, int *flag)
{
	int	i;
	int	j;

	i = 1;
	while (av[i] && av[i][0] == '-' && av[i][1] == 'n')
	{
		j = 1;
		while (av[i][j] != '\0')
		{
			if (av[i][j] != 'n')
				return ;
			j++;
		}
		i++;
		*idx += 1;
		*flag = TRUE;
	}
}

static void	print_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] != '\0')
			break ;
		printf("%c", line[i]);
		i++;
	}
}

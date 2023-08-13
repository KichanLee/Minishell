/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 02:30:59 by kichan            #+#    #+#             */
/*   Updated: 2023/08/12 21:30:31 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void		ft_echo(t_leaf *cmd);
// static void	check_flag(char **av, int *idx, int *flag);
// static void	print_line(char *line);
static void	check_flag(t_leaf *cmd, int *cnt, int *flag);
static void	print_line(t_leaf *cmd);

// void	ft_echo(t_leaf *cmd)
// {
// 	int i;
// 	int flag;
// 	int blank;
// 	char **cmd;

// 	cmd = join_cmd(cmd->left_child->right_child);
// 	blank = count_args(cmd);
// 	i = 1;
// 	flag = FALSE;
// 	check_flag(cmd, &i, &flag);
// 	while (cmd[i])
// 	{
// 		print_line(cmd[i]);
// 		if(i < blank - 1)
// 			printf(" ");
// 		i++;
// 	}
// 	if (flag == FALSE)
// 		printf("\n");
// }

// static void	check_flag(char **av, int *idx, int *flag)
// {
// 	int	i;
// 	int	j;

// 	i = 1;
	// while (av[i] && av[i][0] == '-' && av[i][1] == 'n')
// 	{
// 		j = 1;
// 		while (av[i][j] != '\0')
// 		{
// 			if (av[i][j] != 'n')
// 				return ;
// 			j++;
// 		}
// 		i++;
// 		*idx += 1;
// 		*flag = TRUE;
// 	}
// }

// static void	print_line(char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '$' && line[i + 1] != '\0')
// 			break ;
// 		printf("%c", line[i]);
// 		i++;
// 	}
// }

void	ft_echo(t_leaf *cmd)
{
	int cnt;
	int flag;

	cnt = 0;
	flag = FALSE;
	cmd = cmd->right_child;
	check_flag(cmd, &cnt, &flag);
	while (cnt--)
		cmd = cmd->right_child;
	while (cmd)
	{
		print_line(cmd);
		if (cmd->token->blank == TRUE && cmd->right_child)
			printf(" ");
		cmd = cmd->right_child;
	}
	if (flag == FALSE)
		printf("\n");
}

static void	check_flag(t_leaf *cmd, int *cnt, int *flag)
{
	int	i;

	while (cmd && cmd->token->str[0] == '-' && cmd->token->str[1] == 'n')
	{
		i = 1;
		while (cmd->token->str[i] != '\0')
		{
			if (cmd->token->str[i] != 'n')
				return ;
			i++;
		}
		cmd = cmd->right_child;
		*cnt += 1;
		*flag = TRUE;
	}
}

static void	print_line(t_leaf *cmd)
{
	int	i;

	i = 0;
	while (cmd->token->str[i])
	{
		printf("%c", cmd->token->str[i]);
		i++;
	}
}

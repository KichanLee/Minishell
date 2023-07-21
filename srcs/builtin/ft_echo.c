/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 02:30:59 by kichan            #+#    #+#             */
/*   Updated: 2023/07/20 22:20:42 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"


char **join_cmd(t_leaf * com_leaf)
{
	int cnt =1;

	t_leaf *temp = com_leaf;
	t_leaf *leaf = com_leaf;
	// printf("%s\n",leaf->token->str);
	while(temp && temp->right_child)
	{
		temp= temp->right_child;
		cnt++;
	}
	char **str = (char **)ft_calloc(cnt + 1, sizeof(char *));

	int i=1;
	str[0]= leaf->token->str;
	while(leaf)
    {
        if (leaf->right_child)
        {
            str[i] = leaf->right_child->token->str;
            leaf = leaf->right_child;
            i++;
        }
        else
            break;
    }
	return str;
}

void	check_echo_flag(char **av, int *i, int *flag)
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
int count_args(char **args)
{
    int count = 0;

    while (*args != NULL)
    {
        count++;
        args++;
    }

    return count;
}
void ft_echo(t_data *data)
{
	char **cmd;
	int cnt;
	int flag = 0;
	// int i = 0;
	int blank = 0;
	cmd = join_cmd(data->root->left_child->right_child);
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
	if(flag == 1)
		printf("\n");
}
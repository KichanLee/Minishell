/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:23:29 by kichan            #+#    #+#             */
/*   Updated: 2023/07/21 21:40:55 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		is_num_str(char *str)
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

void	exit_not_num(t_data *data)
{
	printf("exit\n");
	printf("bash: exit: %s: numeric argument required\n", data->input->root->left_child->right_child->token->str);
	exit(255);
}

int count_args_two(char **args)
{
    int count = 0;

    while (*args != NULL)
    {
        count++;
        args++;
    }

    return count;
}

char **join_cmd_two(t_leaf * com_leaf)
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


void	ft_exit(t_data *data)
{
	int		status;
    char    **cmd;
	int		count;
	
    cmd = join_cmd_two(data->input->root->left_child->right_child);
    count = count_args_two(cmd);
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

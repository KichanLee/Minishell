/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:51:02 by kichan            #+#    #+#             */
/*   Updated: 2023/07/21 21:42:05 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void env_clear(t_data *data)
{
    printf("env clear start!\n");
	t_list *current = data->input->envs;
	while (current != NULL)
	{
		t_list *next = current->next;
		ft_lstdelone(current);
		current = next;
	}
	data->input->envs = NULL;
}

void    ft_unset(t_data *data)
{
    char    **cmd;
    int     arg_cnt;
    int     i;
    
    cmd = join_cmd(data->input->root->left_child->right_child);
    arg_cnt = count_args(cmd) - 1;
    i = 1;
    printf("\n=====arg_Cnt : %d\n========", arg_cnt);
    if(arg_cnt == 0)
    {
        printf("if start!");
        env_clear(data);
    }
    else
    {
        printf("else start!");
        while (i < arg_cnt)
        {
            env_remove(data->input, cmd[i]);
            ++i;
        }
    }
}
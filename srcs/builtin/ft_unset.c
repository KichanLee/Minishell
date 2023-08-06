/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong < donghong@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:51:02 by kichan            #+#    #+#             */
/*   Updated: 2023/08/03 17:12:24 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void      ft_unset(t_data *data, t_leaf *cur_root);
static void env_clear(t_data *data);

void  ft_unset(t_data *data, t_leaf *cur_root)
{
    char    **cmd;
    int     arg_cnt;
    int     i;
    
    cmd = join_cmd(cur_root->left_child->right_child);
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
            env_remove(data, cmd[i]);
            ++i;
        }
    }
    // return (TRUE);
}

static void env_clear(t_data *data)
{
    printf("env clear start!\n");
	t_list *current = data->envs;
	while (current != NULL)
	{
		t_list *next = current->next;
		ft_lstdelone(current);
		current = next;
	}
	data->envs = NULL;
}

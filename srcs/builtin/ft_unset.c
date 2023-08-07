/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:51:02 by kichan            #+#    #+#             */
/*   Updated: 2023/08/06 22:32:49 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void        ft_unset(t_data *data, t_leaf *cur_root);
// static void env_clear(t_data *data);

void  ft_unset(t_data *data, t_leaf *cur_root)
{
    char    **cmd;
    int     arg_cnt;
    int     i;
    
    cmd = join_cmd(cur_root->left_child->right_child);
    // arg_cnt = count_args(cmd) - 1;
    arg_cnt = count_args(cmd);
    i = 1;
    // if(arg_cnt == 0)
    //     env_clear(data);
    // else
    // {
        while (i < arg_cnt)
        {
            env_remove(data, cmd[i]);
            ++i;
        }
    // }
}


//왜 arg_cnt가 0이면 clear하지?
// static void env_clear(t_data *data)
// {
// 	t_list *current = data->envs;
// 	while (current != NULL)
// 	{
// 		t_list *next = current->next;
// 		ft_lstdelone(current);
// 		current = next;
// 	}
// 	data->envs = NULL;
// }

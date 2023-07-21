/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:00:48 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/21 22:04:30 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool	preorder(t_data *data, t_leaf *cur_root)
{
	if (cur_root->right_child)
		preorder(data, cur_root->right_child);
}
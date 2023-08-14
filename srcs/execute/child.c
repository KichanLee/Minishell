/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:36:58 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/14 18:37:20 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	do_cmd(t_data *data);
void	exec_fork(t_data *data);

void	do_cmd(t_data *data)
{
	int		builtnum;
	t_leaf	*temp;

	temp = data->root->left_child->right_child;
	if (data->info->pipe_num >= 300)
	{
		printf("%s\n", E_SYNTAX_PIPE);
		exit(258);
	}
	if (temp != NULL)
		builtnum = check_bulitin_func(temp->token->str);
	if (data->root->left_child->left_child != NULL)
		check_redirect (data->root, data);
	if (temp == NULL)
		exit(0);
	if (builtnum != 0)
	{
		exec_bulitin(builtnum, data);
		exit(0);
	}
	else
		exec_fork(data);
}

void	exec_fork(t_data *data)
{
	t_pipe	*base;

	base = data->pipe;
	if (!data->root->left_child->right_child)
		return ;
	abs_path(data);
	base->command = set_path(data, data->root->left_child->right_child);
	if (!base->command)
	{
		data->error_code = 127;
		exit(data->error_code);
	}
	execve(base->command, base->cmd_path, data->env_array);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 17:07:56 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/14 08:32:27 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	do_cmd(t_data *data)
{
	int		builtnum;
	t_leaf	*temp;

	if (data->info->pipe_num >= 300)
	{
		printf("%s\n", E_SYNTAX_PIPE);
		exit(258);
	}
	temp = data->root->left_child->right_child;
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

void	execute(t_data *data)
{
	count_pipe(data);
	heredoc_flag(data->root, data);
	data->info->heredoc_file = (char **)ft_calloc(data->info->heredoc_flag + 1, \
	sizeof(char *));
	if (!data->info->heredoc_file)
		program_error_exit("bash");
	if (!data->info->pipe_num && !data->info->heredoc_flag)
		if (check_bulitin(data) == TRUE)
			return ;
	if (data->info->heredoc_flag)
	{
		if (fork_heredoc (data))
			return ;
	}
	execute_cmd(data, 0);
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
		exit(127);
	execve(base->command, base->cmd_path, data->env_array);
}

void	execute_single_cmd(t_data *data, t_pipe *base, int i, int flag)
{
	if (i < data->info->pipe_num)
		if (pipe(base->com[i].fd) < 0)
			error_back_readline(data, "bash", EPIPE, 1);
	base->com[i].pid = fork();
	if (base->com[i].pid == -1)
	{
		if (flag)
			program_error_exit("bash");
		else
			error_back_readline(data, "bash", ENOMEM, 1);
	}
	if (base->com[i].pid == 0)
	{
		signal(SIGINT, child_handler);
		signal(SIGQUIT, child_handler);
		data->info->parent = 1;
		if (data->info->pipe_num != 0)
			if (link_pipe(i, base, data) == TRUE)
				exit(1);
		do_cmd(data);
	}
	else
		data->root = data->root->right_child;
	if (data->info->pipe_num)
		close_pipe(i, base, data);
}

void	execute_cmd(t_data *data, int flag)
{
	int		i;
	t_pipe	*base;
	t_leaf	*head;

	i = 0;
	base = data->pipe;
	head = data->root;
	while (i < data->info->pipe_num + 1)
	{
		execute_single_cmd(data, base, i, flag);
		i++;
	}
	data->root = head;
	wait_child_processes(data);
}

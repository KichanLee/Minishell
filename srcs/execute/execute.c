/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 12:06:55 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/22 18:52:50 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool			execute(t_data *data);
static t_bool	command(t_data *data, t_leaf *cur_root);
static void		exec_cmd(t_data *data, t_leaf *cur_root);
static void		exec_fork(t_data *data, t_leaf *cur_root, t_cmd *cmd);
static void		wait_child_processes(t_data *data);

t_bool	execute(t_data *data)
{
	t_leaf	*cur_root;

	cur_root = data->input->root;
	data->cmd_idx = 0;
	while (cur_root)
	{
		if (cur_root->left_child->left_child)
			redirect(data, cur_root);
		command(data, cur_root);
		data->cmd_idx++;
		cur_root = cur_root->right_child;
	}
	wait_child_processes(data);
	return (TRUE);
}

static t_bool	command(t_data *data, t_leaf *cur_root)
{
	t_bool (*func)(t_data *, t_leaf *);

	if (!cur_root->left_child->right_child) //cmd 없을 때
	{
		// 다시 돌려놔줘야함 안그러면 redirect로 바꾼곳으로 계속출력됨
        recover_std(data);
		return (FALSE);
	}
    func = get_builtin_func(cur_root->left_child->right_child->token->str);
    if (!func || data->input->pipe_num) // execve
		exec_cmd(data, cur_root);
    if (func(data, cur_root) == FALSE)
        return (FALSE);
    return (TRUE);
}

static void	exec_cmd(t_data *data, t_leaf *cur_root)
{
	t_cmd	*cur_cmd;
	t_cmd	*pre_cmd;
	
	cur_cmd = &data->cmd[data->cmd_idx]; //왜 &?
	pre_cmd = &data->cmd[data->cmd_idx - 1];
	signal(SIGQUIT, SIG_DFL);
	if (pipe(cur_cmd->fd) < 0)
		// exit(1); 에러처리
	cur_cmd->pid = fork();
	printf("%d\n", cur_cmd->pid);
	// if (cmd->pid == -1) 에러처리
		// return;
	if (cur_cmd->pid == CHILD)
	{
		data->parent = 1;
		link_pipe(data, cur_cmd, pre_cmd);
		exec_fork(data, cur_root, cur_cmd);
	}
	close_pipe(data, cur_cmd, pre_cmd);
	signal(SIGQUIT, SIG_IGN);
}

static void exec_fork(t_data *data, t_leaf *cur_root, t_cmd *cmd) // 이제경로 찾고 하던 대로해주면됨 
{
    data->input->env_array = env_to_array(data->input);
    abs_path(data, cmd);
	set_path(cur_root, cmd);
	// if (!cmd->cmd_path)
		// exit(1);
	execve(cmd->cmd_path, cmd->cmd_list, data->input->env_array);
	// if (execve(cmd->cmd_path, cmd->cmd_list, data->input->env_array) == -1)
		// exit(1);
}

static void	wait_child_processes(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->input->pipe_num)
	{
		waitpid(-1, &status, 0);
		i++;
	}
}
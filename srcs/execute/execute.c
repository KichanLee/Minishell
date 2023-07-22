/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 12:06:55 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/22 13:30:29 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool	execute(t_data *data)
{
	t_leaf	*cur_root;

	data->cmd_idx = 0;
	while (cur_root)
	{
		if (cur_root->left_child->left_child)
		{
			heredoc(data, cur_root);
			redirect(data, cur_root);
		}
		command(data, cur_root);
		cur_root = data->input->root;
		data->cmd_idx++;
	}
}

t_bool	command(t_data *data, t_leaf *cur_root)
{
	char	*(*func)(t_data *, t_leaf *);

	if (!cur_root->left_child->right_child) //cmd 없을 때
	{
		// 다시 돌려놔줘야함 안그러면 redirect로 바꾼곳으로 계속출력됨
        recover_std(data);
		return ;
	}
    func = get_builtin_func(cur_root->left_child->right_child);
    if (!func) // execve
		exec_cmd(data);
    if (func(data, cur_root) == FALSE)
        return (FALSE);
    return (TRUE);
}

// 부모에서 exit 하면 return  자식에서 하면 exit (??)
void	exec_cmd(t_data *data, t_leaf *cur_root)
{
	t_cmd	*cmd;
	t_cmd	*pre;
	
	cmd = &data->cmd[data->cmd_idx]; //왜 &?
	pre = &data->cmd[data->cmd_idx - 1];
	signal(SIGQUIT, SIG_DFL);
	if (pipe(cmd->fd) < 0)
		// exit(1); 에러처리
	cmd->pid = fork();
	// if (cmd->pid == -1) 에러처리
	// 	return;
	if (cmd->pid == CHILD)
	{
		// data->parent =1; 무슨 용도?
		link_pipe(data, cmd, pre);
		exec_fork(data, cur_root);
	}
	close_pipe(data, cur, pre);
	signal(SIGQUIT, SIG_IGN);
	wait_child_processes(data);
	
	// free_cmd(base);
}

void exec_fork(t_data *data, t_leaf *cur_root) // 이제경로 찾고 하던 대로해주면됨 
{
	t_cmd *base = data->cmd;
	
	if(!data->input->root->left_child->right_child)
		return ;
    data->input->env_array = env_to_array(data);
    abs_path(data);
	base->command = set_path(data ,data->input->root->left_child->right_child);
	if (!base->command)
		exit(1);
	if (execve(base->command, base->cmd_path, data->input->env_array) == -1)
		exit(1);
}

// 정상 종료 확인해주고 수정;
void	wait_child_processes(t_data *data)
{
	int			i;
	int			status;

	i = 0;
	while (i < data->input->pipe_num)
	{
		waitpid(-1, &status, 0);
		i++;
	}
}
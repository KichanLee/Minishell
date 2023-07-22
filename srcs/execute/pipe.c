#include "../../incs/minishell.h"

void	set_pipe(t_data *data);
void	link_pipe(t_data *data, t_cmd *cur_cmd, t_cmd *pre_cmd);
void	close_pipe(t_data *data, t_cmd *cur_cmd, t_cmd *pre_cmd);

void	set_pipe(t_data *data)
{
	data->cmd = (t_cmd *)ft_calloc(data->input->pipe_num + 2, sizeof(t_cmd));// herdoc 때문에 하나를 여유롭게생성(ㅇㅗㅐ +2??)
	if(!data->cmd)
		program_error_exit("bash");
}

void	link_pipe(t_data *data, t_cmd *cur_cmd, t_cmd *pre_cmd)
{
	if (!data->input->pipe_num)
		return ;
	if (data->cmd_idx == 0)
	{
		if (close(cur_cmd->fd[0]) == -1 \
			|| dup2(cur_cmd->fd[1], STDOUT_FILENO) == -1 \
			|| close(cur_cmd->fd[1])== -1)
			program_error_exit("pipe");
	}
	else if (data->cmd_idx == data->input->pipe_num)
	{
		if (dup2(pre_cmd->fd[0], STDIN_FILENO) == -1 \
			|| close(pre_cmd->fd[0]) == -1)
			program_error_exit("pipe");
	}
	else
	{
		if (dup2(pre_cmd->fd[0], STDIN_FILENO) == -1 \
			|| close(pre_cmd->fd[0]) == -1 \
			||dup2(cur_cmd->fd[1], STDOUT_FILENO) == -1 \
			|| close(cur_cmd->fd[1]) == -1)
			program_error_exit("pipe");
	}
}

void	close_pipe(t_data *data, t_cmd *cur_cmd, t_cmd *pre_cmd)
{
	if (data->cmd_idx == 0)
		close(cur_cmd->fd[1]);
	else if (data->cmd_idx == data->input->pipe_num)
		close(pre_cmd->fd[0]);
	else
	{
		close(pre_cmd->fd[0]);
		close(cur_cmd->fd[1]);
	}
}

void	recover_std(t_data *data)
{
    dup2(data->oristdin,STDIN_FILENO);
    close(data->oristdin);
    dup2(data->oristdout,STDOUT_FILENO);
    close(data->oristdin);
}
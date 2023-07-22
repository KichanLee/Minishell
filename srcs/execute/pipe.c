#include "../../incs/minishell.h"

void	set_pipe(t_data *data);
void	link_pipe(t_data *data, t_cmd *cur_cmd, t_cmd *pre_cmd);
void	close_pipe(t_data *data, t_cmd *cur_cmd, t_cmd *pre_cmd);
void	recover_std(t_data *data);

void	set_pipe(t_data *data)
{
	data->cmd = (t_cmd *)ft_calloc(data->input->pipe_num + 1, sizeof(t_cmd));// heredoc 때문에 하나를 여유롭게생성
	if(!data->cmd)
		program_error_exit("bash");
}

void	link_pipe(t_data *data, t_cmd *cur_cmd, t_cmd *pre_cmd)
{
	if (!data->input->pipe_num)
		return ;
	if (data->cmd_idx == 0)
	{
		if (close(cur_cmd->fd[P_READ]) == -1 \
			|| dup2(cur_cmd->infile_fd, STDIN_FILENO) == -1 \
			|| dup2(cur_cmd->fd[P_WRITE], STDOUT_FILENO) == -1)
			program_error_exit("pipe");
	}
	else if (data->cmd_idx == data->input->pipe_num)
	{
		if (close(pre_cmd->fd[P_WRITE]) == -1 \
			|| dup2(pre_cmd->fd[P_READ], STDIN_FILENO) == -1 \
			|| dup2(cur_cmd->outfile_fd, STDOUT_FILENO) == -1)
			program_error_exit("pipe");
	}
	else
	{
		if (close(cur_cmd->fd[P_READ]) == -1 \
			|| dup2(pre_cmd->fd[P_READ], STDIN_FILENO) == -1 \
			|| dup2(cur_cmd->fd[P_WRITE], STDOUT_FILENO) == -1)
			program_error_exit("pipe");
	}
}

void	close_pipe(t_data *data, t_cmd *cur_cmd, t_cmd *pre_cmd)
{
	if (data->cmd_idx == 0)
	{
		if (close(cur_cmd->fd[P_WRITE]) == -1)
			program_error_exit("pipe");
	}
	else if (data->cmd_idx == data->input->pipe_num)
	{
		if (close(pre_cmd->fd[P_READ] == -1))
			program_error_exit("pipe");
	}
	else
	{
		if (close(pre_cmd->fd[P_READ]) \
			|| close(cur_cmd->fd[P_WRITE]))
			program_error_exit("pipe");
	}
}

void	recover_std(t_data *data)
{
    dup2(data->oristdin,STDIN_FILENO);
    close(data->oristdin);
    dup2(data->oristdout,STDOUT_FILENO);
    close(data->oristdin);
}
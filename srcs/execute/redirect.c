#include "../../incs/minishell.h"

void	redirect(t_data *data, t_leaf *cur_leaf)
{
	input_redirect(cur_leaf, data);
	output_redirect(cur_leaf, data);
}

void	input_redirect(t_data *data, t_leaf *cur_leaf)
{
	t_leaf	*input;

	if (data->cmd[data->cmd_idx].infile_fd > 0)
	{
		dup2 (data->cmd[data->cmd_idx].infile_fd, STDIN_FILENO);
		return ;
	}
	while (cur_leaf)
	{
		if (cur_leaf->token->redirect_type == T_INPUT)
			input = cur_leaf;
		cur_leaf = cur_leaf->left_child;
	}
	data->cmd[data->cmd_idx].infile_fd = open(input->left_child->token->str, O_RDONLY);
	check_file(data->cmd[data->cmd_idx].infile_fd, data);
	dup2(data->cmd[data->cmd_idx].infile_fd, STDIN_FILENO);
}

void	output_redirect(t_data *data, t_leaf *cur_leaf)
{
	t_leaf	*output;

	while (cur_leaf)
	{
		if (cur_leaf->token->redirect_type == T_OUTPUT \
			|| cur_leaf->token->redirect_type == T_APPEND)
			output = cur_leaf;
		cur_leaf = cur_leaf->left_child;
	}
	if (cur_leaf->token->redirect_type == T_OUTPUT)
		data->cmd[data->cmd_idx].outfile_fd = open (cur_leaf->left_child->token->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (cur_leaf->token->redirect_type == T_APPEND)
		data->cmd[data->cmd_idx].outfile_fd = open (cur_leaf->left_child->token->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
	check_file(data->cmd[data->cmd_idx].outfile_fd, data);
	dup2(data->cmd[data->cmd_idx].outfile_fd, STDOUT_FILENO);
}

void	check_file(int fd,t_data *data)
{
	if (fd < 0)
	{
		close(fd);
		g_exit_status = 1;
		if (data->parent ==0) // 자식에서 종료 or 부모에서 종료 확인해주기 
			exit(1);
	}
}

#include "../../incs/minishell.h"

void		redirect(t_data *data, t_leaf *cur_root);
void		redirect_input(t_data *data, t_leaf *cur_leaf);
void		redirect_output(t_data *data, t_leaf *cur_leaf);
static void	check_file(t_data *data, int fd);

void	redirect(t_data *data, t_leaf *cur_root)
{
	t_leaf	*tmp;

	tmp = cur_root->left_child->left_child;
	while (tmp)
	{
		if (tmp->token->redirect_type == T_HEREDOC)
			heredoc(data, cur_root);
		else if (tmp->token->redirect_type == T_INPUT)
			redirect_input(data, tmp);
		else if (tmp->token->redirect_type == T_OUTPUT \
			|| tmp->token->redirect_type == T_APPEND)
			redirect_output(data, tmp);
		tmp = tmp->left_child;
	}
}

void	redirect_input(t_data *data, t_leaf *cur_leaf)
{
	if (data->cmd[data->cmd_idx].infile_fd)
		close(data->cmd[data->cmd_idx].infile_fd); //에러처리
	data->cmd[data->cmd_idx].infile_fd = open(cur_leaf->left_child->token->str, O_RDONLY);
	check_file(data, data->cmd[data->cmd_idx].infile_fd);
}

void	redirect_output(t_data *data, t_leaf *cur_leaf)
{
	if (cur_leaf->token->redirect_type == T_OUTPUT)
		data->cmd[data->cmd_idx].outfile_fd = open (cur_leaf->left_child->token->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (cur_leaf->token->redirect_type == T_APPEND)
		data->cmd[data->cmd_idx].outfile_fd = open (cur_leaf->left_child->token->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
	check_file(data, data->cmd[data->cmd_idx].outfile_fd);
}

static void	check_file(t_data *data, int fd)
{
	if (fd < 0)
	{
		close(fd);
		g_exit_status = 1;
		if (data->parent ==0) // 자식에서 종료 or 부모에서 종료 확인해주기 
			exit(1);
	}
}

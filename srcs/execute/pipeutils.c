#include "../../incs/minishell.h"

void	count_pipe(t_data*data)
{
	t_leaf	*temp;

	temp = data->root;
	while (temp)
	{
		data->info->pipe_num++;
		temp = temp->right_child;
	}
	if (data->info->pipe_num != 0)
		data->info->pipe_num--;
	data->pipe->com = (t_pid *)ft_calloc(data->info->pipe_num + 1, \
	sizeof(t_pid));
	if (!data->pipe->com)
		program_error_exit("bash");
}

void	heredoc_flag(t_leaf *leaf, t_data *data)
{
	if (!leaf)
		return ;
	if (leaf->token)
	{
		if (leaf->token->type == T_REDIRECT)
		{
			if (leaf->token->redirect_type == T_HEREDOC)
			{
				if (leaf->left_child == NULL)
					return ;
				data->info->heredoc_flag++;
			}
		}
	}
	heredoc_flag(leaf->left_child, data);
	heredoc_flag(leaf->right_child, data);
}

void	recover_std(t_data *data)
{
	if (dup2(data->info->oristdin, STDIN_FILENO) == -1)
		error_back_readline(data, "Bad file descriptor", EBADF, 1);
	close(data->info->oristdin);
	if (dup2(data->info->oristdout, STDOUT_FILENO) == -1)
		error_back_readline(data, "Bad file descriptor", EBADF, 1);
	close(data->info->oristdin);
}

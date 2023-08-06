#include "../../incs/minishell.h"

void	count_pipe(t_data*data)
{
 	t_leaf *temp = data->root;
	while(temp)
	{
 		data->info->pipe_num++;
		temp= temp->right_child;
	}
	if(data->info->pipe_num!=0)
		data->info->pipe_num--; // 파이프가 1나일때 2개가됨 
	data->pipe->com = (t_pid *)ft_calloc(data->info->pipe_num+1,sizeof(t_pid));// 하나를 여유롭게 생성하는이유는 herdoc 때문에 하나를 여유롭게생성
	if(!data->pipe->com)
		program_error_exit("bash");
}

void	heredoc_flag(t_leaf *leaf,t_data *data) 
{
	if (!leaf)
		return ;
	if (leaf->token)
	{
		if (leaf->token->type == T_REDIRECT)
		{
			if (leaf->token->redirect_type == T_HEREDOC)
				data->info->heredoc_flag++;		
		}
	}
	heredoc_flag(leaf->left_child,data);
	heredoc_flag(leaf->right_child,data);
}



void recover_std(t_data *data)
{
    dup2(data->info->oristdin,STDIN_FILENO);
    close(data->info->oristdin);
    dup2(data->info->oristdout,STDOUT_FILENO);
    close(data->info->oristdin);
}

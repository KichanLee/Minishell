#include "../../incs/minishell.h"

void	heredoc_flag(t_leaf *leaf,t_data *data) 
{
	if (!leaf)
		return ;
	if (leaf->token)
	{
		if (leaf->token->type == T_REDIRECT)
		{
			if (leaf->token->redirect_type == T_HEREDOC)
				data->info->heredoc_flag = 1;		
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



// char **join_cmd(t_leaf * com_leaf)
// {
// 	int cnt =1;

// 	t_leaf *temp = com_leaf;
// 	t_leaf *leaf = com_leaf;
	
// 	while(temp && temp->right_child)
// 	{
// 		temp= temp->right_child;
// 		cnt++;
// 	}
// 	char **str = (char **)ft_calloc(cnt + 1, sizeof(char *));
// 	if(!str)
// 		return NULL;
// 	int i=1;
// 	str[0]= leaf->token->str;
// 	while(leaf)
//     {
//         if (leaf->right_child)
//         {
//             str[i] = leaf->right_child->token->str;
//             leaf = leaf->right_child;
//             i++;
//         }
//         else
//             break;
//     }
// 	return str;
// }

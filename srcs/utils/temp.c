//테스트용 임시 함수들

#include "../incs/minishell.h"

void	tree_print(t_leaf *leaf);
void	print_token(t_data *data);
void	env_array_print(t_data *data);
void	check_leak();

//트리 전위순회 출력
void	tree_print(t_leaf *leaf)
{
	if (!leaf)
		return ;
	if (!leaf->parent)
		printf("\n\n--------------tree preorder--------------\n");
	if (leaf->token)
	{
		if (leaf->token->type == T_CMD)
			printf("CMD, str: %s\n", leaf->token->str);
		else if (leaf->token->type == T_ARG)
			printf("ARG, str: %s\n", leaf->token->str);
		else if (leaf->token->type == T_REDIRECT)
		{
			printf("REDIRECT, ");
			if (leaf->token->redirect_type == T_INPUT)
				printf("type: <\n");
			else if (leaf->token->redirect_type == T_OUTPUT)
				printf("type: >\n");
			else if (leaf->token->redirect_type == T_HEREDOC)
				printf("type: <<\n");
			else if (leaf->token->redirect_type == T_APPEND)
				printf("type: >>\n");
		}
	}
	else
	{
		if (leaf->leaf_type == T_PIPE)
			printf("\nPIPE, exist: %d\n", leaf->exist);
		else
			printf("CMD\n");
	}
	tree_print(leaf->left_child);
	tree_print(leaf->right_child);
}

//토큰 리스트 출력용
void	print_token(t_data *data)
{
	t_list *tmp = data->tokens;
	printf("\n\n--------------token list--------------\n");
	while (tmp)
	{
		if (tmp->token->type == T_PIPE)
			printf("token: pipe\n");
		else if (tmp->token->type == T_REDIRECT)
		{
			printf("token: redirect, ");
			if (tmp->token->redirect_type == T_INPUT)
				printf("type: <\n");
			else if (tmp->token->redirect_type == T_OUTPUT)
				printf("type: >\n");
			else if (tmp->token->redirect_type == T_HEREDOC)
				printf("type: <<\n");
			else if (tmp->token->redirect_type == T_APPEND)
				printf("type: >>\n");
		}
		else if (tmp->token->type == T_WORD)
		{
			printf("token: word, ");
			printf("str: %s\n", tmp->token->str);
		}
		else if (tmp->token->type == T_CMD)
		{
			printf("token: cmd, ");
			printf("str: %s\n", tmp->token->str);
		}
		else if (tmp->token->type == T_ARG)
		{
			printf("token: arg, ");
			printf("str: %s\n", tmp->token->str);
		}
		tmp = tmp->next;
	}
}

//배열에 넣은 환경변수 출력용
void	env_array_print(t_data *data)
{
	char **array = env_to_array(data);

	for(int i=0; array[i]; i++)
		printf("%s\n", array[i]);
}

void	check_leak()
{
	system("leaks minishell");
}
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
	if (leaf->token)
		printf("exist: %d, token: %d, redirect: %d, str: %s\n", leaf->exist, leaf->token->type, leaf->token->redirect_type, leaf->token->str);
	else
		printf("exist: %d\n", leaf->exist);
	tree_print(leaf->left_child);
	tree_print(leaf->right_child);
}

//토큰 리스트 출력용
void	print_token(t_data *data)
{
	t_list *tmp = data->tokens;
	while (tmp)
	{
		printf("token: %d, redirect: %d, str: %s\n", tmp->token->type, tmp->token->redirect_type, tmp->token->str);
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
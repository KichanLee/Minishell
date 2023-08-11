#include "../../incs/minishell.h"

int check_bulitin(t_data * data)
{
    int bulit;

    bulit = check_bulitin_func(data->root->left_child->right_child->token->str);
    if(data->root->left_child->right_child == NULL) //no command but redirection 존재
    {
		check_redirect(data->root,data); // redirection 실행 
        recover_std(data); // 다시 돌려놔줘야함 안그러면 redirect로 바꾼곳으로 계속출력됨
        // free(data);
        return (TRUE);
    }
    if(bulit != 0)
    {
        check_redirect(data->root,data);
        exec_bulitin(bulit,data);// flag 에 따라 return  부모 프로세스 or exit 자식  쿠
        recover_std(data); // 커맨드가 하나이기 때문에 바로 종료 
        // free(data);
        return (TRUE);
    }
    return (FALSE);
}
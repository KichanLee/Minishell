#include "../../incs/minishell.h"

int	check_bulitin1(char * str)
{
	if (str)
	{
		if (!ft_strncmp("cd", str, ft_strlen(str)) \
			&& !ft_strncmp("cd", str, 2))
            return 1;
		else if (!ft_strncmp("export", str, ft_strlen(str)) \
			&& !ft_strncmp("export", str, 5))
            return 1;
		else if (!ft_strncmp("unset", str, ft_strlen(str)) \
			&& !ft_strncmp("unset", str, 5))
            return 1;
		else if (!ft_strncmp("exit", str, ft_strlen(str)) \
			&& !ft_strncmp("exit", str, 4))
            return 1;
	}
	return (0);
}


int	check_bulitin2(char * str)
{
	if (str)
	{
		if (!ft_strncmp("echo", str, ft_strlen(str)) \
			&& !ft_strncmp("echo", str, 4))
             return 1;
		else if (!ft_strncmp("pwd", str, ft_strlen(str)) \
			&& !ft_strncmp("pwd", str, 3))
             return 1;
		else if (!ft_strncmp("env", str, ft_strlen(str)) \
			&& !ft_strncmp("env", str, 3))
             return 1;
	}
	return (0);
}


int confirm_bulitin(char *str) // bulitin 확인하기 
{
    if(check_bulitin1(str)|| check_bulitin2(str))
        return 1;
    return 0;
}


int check_bulitin(t_data * data)
{
    if(data->root->left_child->right_child==NULL) //no cmmand but redirection 존재
    {
		check_redirect(data->root,data); // redirection 실행 
        recover_std(data); // 다시 돌려놔줘야함 안그러면 redirect로 바꾼곳으로 계속출력됨
        // free(data);
        return 1;
    }
    if(confirm_bulitin(data->root->left_child->right_child->token->str))
    {
        check_redirect(data->root,data);
        // do_bulitin(data,0);// flag 에 따라 return  부모 프로세스 or exit 자식  쿠
        recover_std(data); // 커맨드가 하나이기 때문에 바로 종료 
        // free(data);
        return 1;
    }
    return 0;
}
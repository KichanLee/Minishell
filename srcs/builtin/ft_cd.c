/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong < donghong@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 02:31:18 by kichan            #+#    #+#             */
/*   Updated: 2023/08/03 17:11:24 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void      ft_cd(t_data *data, t_leaf *cur_root);
static int  change_directory(t_data *data, char *path);

void    ft_cd(t_data *data, t_leaf *cur_root)
{
    char    *option;
    char    pwd[1024];
    option = NULL;
    
    if(!(cur_root->left_child->right_child->right_child))
        change_directory(data, "~");
    else if(change_directory(data,cur_root->left_child->right_child->right_child->token->str) != 0)
    {
        option = cur_root->left_child->right_child->right_child->token->str;
        printf("bash: %s: No such file or directory\n", option);
    }
    else
    {
        getcwd(pwd, 1024);
        printf("current directory : %s\n",pwd);
		update_env(data, "OLDPWD", env_search(data, "PWD")->env);
		update_env(data, "PWD", pwd);
    }
    // return (TRUE);
}

static int  change_directory(t_data *data, char *path)
{
	char	*buf;
	int		res;
    char    pwd[1024];
    
	if (!ft_strncmp(path, "~", 1))
		buf = ft_strdup(env_search(data, "HOME")->env + 5);
	else if (!ft_strncmp(path, "-", 1))
		buf = ft_strdup(env_search(data, "OLDPWD")->env + 7);
	else
		buf = ft_strdup(path);
	if (!buf)
		exit(1);
	res = chdir(buf);
    getcwd(pwd, 1024);
    free(buf);
	return (res);
}

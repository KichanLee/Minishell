/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 02:31:18 by kichan            #+#    #+#             */
/*   Updated: 2023/07/22 15:08:48 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_bool      ft_cd(t_data *data, t_leaf *cur_root);
static int  change_directory(t_data *data, char *path);

t_bool    ft_cd(t_data *data, t_leaf *cur_root)
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
		update_env(data, "OLDPWD", env_search(data->input, "PWD")->env);
		update_env(data, "PWD", pwd);
    }
    return (TRUE);
}

static int  change_directory(t_data *data, char *path)
{
	char	*buf;
	int		res;
    char    pwd[1024];
    
	printf("\npath : %s\n", path);
	if (!ft_strncmp(path, "~", 1))
		buf = ft_strdup(env_search(data->input, "HOME")->env + 5);
	else if (!ft_strncmp(path, "-", 1))
		buf = ft_strdup(env_search(data->input, "OLDPWD")->env + 7);
	else
		buf = ft_strdup(path);
	if (!buf)
		exit(1);
    printf("buf val : %s\n", buf);
	res = chdir(buf);
    getcwd(pwd, 1024);
    printf("current directory : %s\n",pwd);
    free(buf);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 02:31:18 by kichan            #+#    #+#             */
/*   Updated: 2023/07/20 22:27:49 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	change_directory(t_data *data, char *path)
{
	char	*buf;
	int		res;
    char    pwd[1024];
    
	printf("\npath : %s\n", path);
	if (!ft_strncmp(path, "~", 1))
		buf = ft_strdup(env_search(data, "HOME")->env + 5);
	else if (!ft_strncmp(path, "-", 1))
		buf = ft_strdup(env_search(data, "OLDPWD")->env + 7);
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

void    ft_cd(t_data *data)
{
    char    *option;
    char    pwd[1024];
    option = NULL;
    
    if(!(data->root->left_child->right_child->right_child))
        change_directory(data, "~");
    else if(change_directory(data,data->root->left_child->right_child->right_child->token->str) != 0)
    {
        option = data->root->left_child->right_child->right_child->token->str;
        printf("bash: %s: No such file or directory\n", option);
    }
    else
    {
        getcwd(pwd, 1024);
        printf("current directory : %s\n",pwd);
		update_env(data, "OLDPWD", env_search(data, "PWD")->env);
		update_env(data, "PWD", pwd);
    }
}
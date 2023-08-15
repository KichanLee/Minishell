/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 02:31:18 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/15 00:41:11 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void		ft_cd(t_data *data, t_leaf *cur_root);
static int	change_directory(t_data *data, char *path);
static int	change_home(void);

void	ft_cd(t_data *data, t_leaf *cur_root)
{
	char	*option;
	char	pwd[1024];

	option = NULL;
	if (!(cur_root->left_child->right_child->right_child))
		change_directory(data, "HOME");
	else if (change_directory(data, \
	cur_root->left_child->right_child->right_child->token->str) != 0)
	{
		option = cur_root->left_child->right_child->right_child->token->str;
		printf("bash: %s: No such file or directory\n", option);
		data->error_code = 1;
	}
	else
	{
		getcwd(pwd, 1024);
		printf("current directory : %s\n", pwd);
		ft_update_env_cd(data, "OLDPWD", env_search(data, "PWD", TRUE)->env);
		ft_update_env_cd(data, "PWD", pwd);
	}
}

static int	change_directory(t_data *data, char *path)
{
	char	*buf;
	int		res;
	char	pwd[1024];

	if (!ft_strncmp(path, "HOME", 5))
	{
		if (env_search(data, "HOME", TRUE) == NULL)
			return (change_home());
		else
			buf = ft_strdup(env_search(data, "HOME", TRUE)->env + 5);
	}
	else
		buf = ft_strdup(path);
	if (!buf)
		perror("ft_strdup fail!\n");
	res = chdir(buf);
	getcwd(pwd, 1024);
	free(buf);
	return (res);
}

static int	change_home(void)
{
	printf("bash: cd: HOME not set\n");
	return (-1);
}

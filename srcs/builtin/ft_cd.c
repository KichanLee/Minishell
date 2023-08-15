/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 02:31:18 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/15 22:39:21 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_bool		ft_cd(t_data *data);
static int	change_directory(t_data *data, char *path);
static int	change_home(void);

t_bool	ft_cd(t_data *data)
{
	char	*option;
	char	*pwd;

	option = NULL;
	pwd = (char *)ft_calloc(1024, sizeof(char));
	if (!pwd)
		program_error_exit("bash");
	if (!(data->root->left_child->right_child->right_child))
	{
		change_directory(data, "HOME");
		free(pwd);
	}
	else if (change_directory(data, \
			data->root->left_child->right_child->right_child->token->str) != 0)
	{
		option = data->root->left_child->right_child->right_child->token->str;
		printf("bash: %s: No such file or directory\n", option);
		free(pwd);
		return (FALSE);
	}
	else
	{
		getcwd(pwd, 1024);
		ft_update_env_cd(data, ft_strdup("OLDPWD"), \
							ft_strdup(env_search(data, "PWD", TRUE)->env + 4));
		ft_update_env_cd(data, ft_strdup("PWD"), pwd);
	}
	return (TRUE);
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
		program_error_exit("bash");
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 02:31:18 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/16 15:54:01 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool			ft_cd(t_data *data);
static int		change_directory(t_data *data, char *path);
static int		change_home(void);
static t_bool	is_failuer(t_data *data, char *pwd, char *option);
static void		is_success(t_data *data, char *pwd);

t_bool	ft_cd(t_data *data)
{
	char	*option;
	char	*pwd;

	option = NULL;
	pwd = (char *)ft_calloc(BUF_SIZE, sizeof(char));
	if (!pwd)
		program_error_exit("bash");
	if (!(data->root->left_child->right_child->right_child))
	{
		change_directory(data, "HOME");
		free(pwd);
	}
	else if (change_directory(data, \
		data->root->left_child->right_child->right_child->token->str) != 0)
		return (is_failuer(data, pwd, option));
	else
		is_success(data, pwd);
	return (TRUE);
}

static int	change_directory(t_data *data, char *path)
{
	char	*buf;
	int		res;
	char	pwd[BUF_SIZE];

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
	getcwd(pwd, BUF_SIZE);
	free(buf);
	return (res);
}

static int	change_home(void)
{
	printf("bash: cd: HOME not set\n");
	return (-1);
}

static t_bool	is_failuer(t_data *data, char *pwd, char *option)
{
	option = data->root->left_child->right_child->right_child->token->str;
	printf("bash: %s: No such file or directory\n", option);
	free(pwd);
	return (FALSE);
}

static void	is_success(t_data *data, char *pwd)
{
	getcwd(pwd, BUF_SIZE);
	ft_update_env_cd(data, ft_strdup("OLDPWD"), \
						ft_strdup(env_search(data, "PWD", TRUE)->env + 4));
	ft_update_env_cd(data, ft_strdup("PWD"), pwd);
}

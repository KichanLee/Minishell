/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>             +#+  +:+       +#+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:15:04 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/07 14:49:51 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void		ft_env(t_data *data, t_leaf *cur_root);
static void	ft_env_count(t_data *data, char *str);
static void	ft_env_count_else(t_data *data, char *str);
static char	*check_keyval(t_data *data, char *str);

void	ft_env(t_data *data, t_leaf *cur_root)
{
	char	**cmd;
	int		arg_cnt;

	cmd = ft_join_cmd(cur_root->left_child->right_child);
	if (!cmd)
		program_error_exit("bash");
	arg_cnt = ft_cnt_args(cmd);
	if (arg_cnt == 1)
		env_print(data);
	else if (arg_cnt != 2)
		printf("env: %s: No such file or directory\n", cmd[1]);
	else
		ft_env_count(data, cmd[1]);
	free(cmd);
}

static void	ft_env_count(t_data *data, char *str)
{
	int	flag;

	flag = check_equal(str);
	if (flag == 1 && str[0] != '=')
	{	
		env_print(data);
		printf("%s\n", str);
	}
	else if (flag == 1 && str[0] == '=')
		printf("env: setenv %s: Invalid argument\n", str);
	else
		ft_env_count_else(data, str);
}

static void	ft_env_count_else(t_data *data, char *str)
{
	if (str[0] == '$')
	{
		if (ft_strlen(str) == 1)
		{
			printf("env: %s: No such file or directory\n", str);
			data->error_code = 127;
		}
		else if (check_keyval(data, str) == NULL)
			env_print(data);
		else
			printf("%s", env_search(data, str, TRUE)->env);
	}
	else
	{
		printf("env: %s: No such file or directory\n", str);
		data->error_code = 127;
	}
}

static char	*check_keyval(t_data *data, char *str)
{
	t_list	*tmp;

	if (!str)
		return (NULL);
	tmp = env_search(data, str, TRUE);
	if (tmp == NULL)
		return (NULL);
	else
		return (tmp->env);
}

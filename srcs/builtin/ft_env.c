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

void	ft_env(t_data *data, t_leaf *cur_root);

void	update_env(t_data *data, char *key, char *value)
{
	t_list	*tmp;
	char	*key_equal;

	tmp = env_search(data, key,TRUE);
	if (!tmp)
		add_env_front(data, key, value);
	else
	{
		free(tmp->env);
		key_equal = (char *)ft_calloc(sizeof(char), ft_strlen(key) + 2);
		key_equal = ft_strdup(key);
		key_equal[ft_strlen(key)] = '=';
		key_equal[ft_strlen(key) + 1] = '\0';
		tmp->env = ft_strjoin(key_equal, value);
	}
}

char	*check_keyval(t_data *data, char *str)
{
	t_list	*tmp;

	if(!str)
		return (NULL);
	tmp = env_search(data, str,TRUE);
	if (tmp == NULL)
		return (NULL);
	else
		return (tmp->env);
}

void	ft_env(t_data *data, t_leaf *cur_root)
{
	char	**cmd;
	int		arg_cnt;
	char	**env_path;	
	int		flag;
	t_list *tmp;
	// int cnt;
	// cnt = 0;
	tmp = data->tokens;

	while (tmp)
	{
		if(tmp->token->blank)
			// cnt++;
		tmp = tmp->next;
	}
	cmd = join_cmd(cur_root->left_child->right_child);
	arg_cnt = count_args(cmd);
	env_path = NULL;

	int k = 0;

	while (cmd[k])
	{
		printf("cmd : %s\n", cmd[k]);
		++k;
	}
	if (arg_cnt == 1)
		env_print(data);
	else if(arg_cnt != 2)
		printf("env: %s: No such file or directory\n", cmd[2]);
	else
	{
		flag = check_equal(cmd[1]);
		printf("flag!\n");
		if(flag == 1 && cmd[1][0] != '=')
		{	
			env_path = ft_split(cmd[1], '=');
			if(!env_path || !env_path[0])
			{
				printf("error!\n");
				return ;
			}
			env_print(data);
			printf("%s\n", cmd[1]);
		}
		else if(flag == 1 && cmd[1][0] == '=')
		{
			printf("env: setenv %s: Invalid argument\n", cmd[1]);
		}
		else 
		{
			printf("else start!!\n");
			if (cmd[1][0] == '$')
			{
				if (ft_strlen(cmd[1]) == 1)
				{
					printf("env: %s: No such file or directory\n", cmd[1]);
					data->error_code = 127;
				}
				else if (check_keyval(data, cmd[1]) == NULL)
					env_print(data);
				else
					printf("%s", env_search(data, cmd[1],TRUE)->env);
			}
			else
			{
				printf("env: %s: No such file or directory\n", cmd[1]);
				data->error_code = 127;
			}
		}
	}
}

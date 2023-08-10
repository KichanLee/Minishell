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

char	*check_keyval(t_data *data, char *str)
{
	t_list	*tmp;

	tmp = env_search(data, str);
	if (tmp == NULL)
		return (NULL);
	else
		return (tmp->env);
}

void	ft_env(t_data *data, t_leaf *cur_root)
{
	char	**cmd;

	cmd = join_cmd(cur_root->left_child->right_child);
	if (!cmd[1])
		env_print(data);
	else
	{
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
				printf("%s", env_search(data, cmd[1])->env);
		}
		else
		{
			printf("env: %s: No such file or directory\n", cmd[1]);
			data->error_code = 127;
		}
	}
}

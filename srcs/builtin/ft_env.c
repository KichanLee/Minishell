/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:15:04 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/07 19:46:36 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void		ft_env(t_data *data, t_leaf *cur_root);
static char	*check_keyval(t_data *data, char *str);

/**
 *  1. cmd cnt 를 해주고 cmd가 1개 인경우는
 *      -> env_print 실행
 *  2. cmd cnt 가 1개가 아닐때
 *      -> $가 있을때
 *          $뒤 path가 존재 할때 $뒤를 검색한 다음에 해당하는 path만 반환
 *          $뒤 path가 존재 없을때  env_print 실행
 *      -> $가 없을때 해당 문자열
 *           env: 문자열: No such file or directory
 *
 * 
 *      export $kichlee 있는 거면  kichlee
 *      export $aaa 없는 거면 $aaaa
*/

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

static char	*check_keyval(t_data *data, char *str)
{
	t_list	*tmp;

	tmp = env_search(data, str);
	if (tmp == NULL)
		return (NULL);
	else
		return (tmp->env);
}

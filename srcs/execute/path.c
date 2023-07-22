/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:50:41 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/22 15:40:08 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void			abs_path(t_data *data, t_cmd *cmd);
void			set_path(t_leaf *cur_root, t_cmd *cmd);
static char		**get_path_envp(char **env);
static t_bool	check_path(char *str);
static char		*search_path(t_cmd *cmd);

void	abs_path(t_data *data, t_cmd *cmd)
{
	int		i;
    char *tmp;

	i = 0;
    data->input->env_array = env_to_array(data->input); // 환경 변수 array에 담아주기
    cmd->cmd_abs = get_path_envp(data->input->env_array); 
	if (!cmd->cmd_abs)
		exit(1);
	while (cmd->cmd_abs[i])
	{
		tmp = cmd->cmd_abs[i];
		cmd->cmd_abs[i] = ft_strjoin(tmp, "/");// 절대 경로 만들어주기
		free(tmp);
		i++;
	}
}

void	set_path(t_leaf *cur_root, t_cmd *cmd)
{
	char	*tmp;
	
	cmd->cmd_list = join_cmd(cur_root->left_child->right_child); //ls - l - y -t 
	if (!cmd->cmd_list[0][0])
		exit(1);
	if (check_path(cmd->cmd_list[0]) == TRUE)
	{
		tmp = ft_strdup(cmd->cmd_list[0]);
		if (access(tmp, X_OK) == 0)
		{
			cmd->cmd_path = tmp;
			return ;
		}
		free(tmp);
	}
	else
		cmd->cmd_path = search_path(cmd);
}

static char	**get_path_envp(char **env)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	if (*env == NULL)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			path = env[i];
		i++;
	}
	if (path == NULL)
		return (NULL);
	return (ft_split(path, ':'));
}

static t_bool	check_path(char *str)
{
	if (!ft_strncmp("./", str, 2) || \
		!ft_strncmp("../", str, 3) || \
		!ft_strncmp("/", str, 1))
		return (TRUE);
	return (FALSE);
}

static char	*search_path(t_cmd *cmd)
{
	char	*tmp;
	int		k;

	k = 0;
	while (cmd->cmd_abs[k])
	{
		tmp = ft_strjoin(cmd->cmd_abs[k], cmd->cmd_list[0]);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
		k++;
	}
	return (NULL);
}

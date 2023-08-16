/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:43:04 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/17 01:32:53 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char		*set_path(t_data *data, t_leaf *leaf);
void		abs_path(t_data *data);
static int	check_path(char *str);
static char	*search_path(t_pipe *base);
static char	**get_path_envp(char **env);

char	*set_path(t_data *data, t_leaf *leaf)
{
	char	*tmp;
	t_pipe	*base;

	base = data->pipe;
	base->cmd_path = ft_join_cmd(leaf);
	if (!base->cmd_path)
		exit(1);
	if (check_path(base->cmd_path[0]) == 1)
	{
		tmp = ft_strdup(base->cmd_path[0]);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
		return (NULL);
	}
	else
		return (search_path(base));
}

void	abs_path(t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	data->pipe->cmd_abs = get_path_envp(data->env_array);
	if (!data->pipe->cmd_abs)
		return ;
	while (data->pipe->cmd_abs[i])
	{
		temp = data->pipe->cmd_abs[i];
		data->pipe->cmd_abs[i] = ft_strjoin(temp, "/");
		free(temp);
		i++;
	}
}

static int	check_path(char *str)
{
	if (!ft_strncmp("./", str, 2) || \
		!ft_strncmp("../", str, 3) || \
		!ft_strncmp("/", str, 1))
		return (1);
	return (0);
}

static char	*search_path(t_pipe *base)
{
	char	*tmp;
	int		k;

	k = 0;
	if (!base->cmd_abs)
	{
		error_print(base->cmd_path[0], 0, 1);
		exit (127);
	}
	while (base->cmd_abs[k])
	{
		tmp = ft_strjoin(base->cmd_abs[k], base->cmd_path[0]);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
		k++;
	}
	return (NULL);
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
		{
			path = env[i];
			return (ft_split(path, ':'));
		}
		i++;
	}
	return (NULL);
}

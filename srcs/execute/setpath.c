#include "../../incs/minishell.h"

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

void	abs_path(t_data *data)
{
	int		i;
	t_pipe *pipe = data->pipe;
    char *temp;

	i = 0;
    data->env_array = env_to_array(data); // 환경 변수 array에 담아주기
    pipe->cmd_abs = get_path_envp(data->env_array); 
	if (!pipe->cmd_abs)
		program_error_exit("bash");
	while (pipe->cmd_abs[i])
	{
		temp = pipe->cmd_abs[i];
		pipe->cmd_abs[i] = ft_strjoin(temp, "/");// 절대 경로 만들어주기
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

char	*set_path(t_data *data, t_leaf *leaf)
{
	char	*tmp;
	t_pipe *base;
	
	base= data->pipe;
	base->cmd_path=join_cmd(leaf); //ls - l - y -t 
	if (!base->cmd_path[0][0])
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

char	*search_path(t_pipe *base)
{
	char	*tmp;
	int		k;

	k = 0;
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

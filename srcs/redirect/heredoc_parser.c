/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:43:30 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/08 11:53:27 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	heredoc_parser(t_data *data, int fd, char *str);
char	*heredoc_expand(t_data *data, char *str, char *tmp, int *i);

void	heredoc_parser(t_data *data, int fd, char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strdup("");
	while (str[++i])
	{
		if (str[i] == '$')
			tmp = heredoc_expand(data, str, tmp, &i);
		else
			tmp = ft_strncat(tmp, &str[i], 1);
	}
	write(fd, tmp, ft_strlen(tmp));
	write(fd, "\n", 1);
	free(str);
}

char	*heredoc_expand(t_data *data, char *str, char *tmp, int *i)
{
	char	*name;
	t_list	*env;
	int		j;

	*i += 1;
	name = ft_strdup("");
	while (str[*i] != '\0' && str[*i] != ' ' && str[*i] != '\t')
	{
		name = ft_strncat(name, &str[*i], 1);
		*i += 1;
	}
	env = env_search(data, name);
	if (!env)
	{
		tmp = ft_strncat(tmp, "$", 1);
		if (!tmp)
			program_error_exit("bash");
		tmp = ft_strncat(tmp, name, ft_strlen(name));
		if (!tmp)
			program_error_exit("bash");
	}
	else
	{
		j = 0;
		while (env->env[j] != '=')
			j++;
		tmp = ft_strncat(tmp, \
			&env->env[j + 1], ft_strlen(&env->env[j + 1]));
		if (!tmp)
			program_error_exit("bash");
	}
	if (str[*i] != '\0')
		*i -= 1;
	return (tmp);
}

static char	*get_env_name(char *str, int *i)
{
	
}
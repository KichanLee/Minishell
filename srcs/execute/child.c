/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:36:58 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/17 01:24:10 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	do_cmd(t_data *data);
void	exec_fork(t_data *data);
void	check_errortype(char *str, int flag);

void	do_cmd(t_data *data)
{
	int		builtnum;
	t_leaf	*temp;

	temp = data->root->left_child->right_child;
	if (data->info->pipe_num >= 300)
	{
		printf("%s\n", E_SYNTAX_PIPE);
		exit(258);
	}
	if (temp != NULL)
		builtnum = check_builtin_func(temp->token->str);
	if (data->root->left_child->left_child != NULL)
		check_redirect (data->root, data);
	if (temp == NULL)
		exit(0);
	if (builtnum != 0)
	{
		exec_builtin(builtnum, data);
		exit(0);
	}
	else
		exec_fork(data);
}

void	exec_fork(t_data *data)
{
	t_pipe	*base;

	base = data->pipe;
	if (!data->root->left_child->right_child)
		return ;
	abs_path(data);
	base->command = set_path(data, data->root->left_child->right_child);
	if (!base->command)
	{
		error_print(base->cmd_path[0], 0, 0);
		exit(127);
	}
	execve(base->command, base->cmd_path, data->env_array);
}

char	*ft_strjoinstr(char *s1, char *s2)
{
	char	*tmp;
	size_t	lena;
	size_t	lenb;

	if (s1 == 0 || s2 == 0)
		return (0);
	lena = ft_strlen(s1);
	lenb = ft_strlen(s2);
	tmp = (char *)malloc(sizeof(char) * (lena + lenb + 1));
	if (!tmp)
		return (0);
	tmp[0] = '\0';
	ft_strlcat(tmp, s1, lena + 1);
	ft_strlcat(tmp, s2, lena + lenb + 1);
	tmp[lena + lenb] = '\0';
	return (tmp);
}

void	error_print(char *cmd, char *option, int flag)
{
	char	*tmp;
	char	*str;

	str = ft_strdup (cmd);
	tmp = str;
	str = ft_strjoinstr ("bash: ", str);
	free(tmp);
	if (option)
	{
		tmp = str;
		str = ft_strjoin(str, ": ");
		free(tmp);
		tmp = str;
		str = ft_strjoin(str, option);
		free(tmp);
	}
	check_errortype(str, flag);
}

void	check_errortype(char *str, int flag)
{
	char	*tmp;

	tmp = str;
	if (flag == 0)
		str = ft_strjoinstr(str, ": command not found\n");
	else if (flag == 1)
		str = ft_strjoinstr(str, ": No such file or directory\n");
	free(tmp);
	write(2, str, ft_strlen (str));
	free(str);
}

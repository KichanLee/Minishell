/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:21:48 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/17 21:31:47 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int			fork_heredoc(t_data *data);
static void	mk_heredoc_pipe(t_data *data);
static char	*mk_filename(void);
static void	mk_num(char *str, int num);
static void	do_heredoc(t_leaf *leaf, t_data *data);

int	fork_heredoc(t_data *data)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal (SIGINT, child_handler);
		mk_heredoc_pipe(data);
		execute_cmd(data, 1);
		exit(g_error_code);
	}
	else
	{
		signal (SIGINT, SIG_IGN);
		waitpid(-1, &status, 0);
		g_error_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			g_error_code = WTERMSIG (status);
			ft_putendl_fd("", STDERR_FILENO);
			return (1);
		}
	}
	return (1);
}

static void	mk_heredoc_pipe(t_data *data)
{
	t_leaf	*pipe;

	pipe = data->root;
	while (pipe)
	{
		data->info->heredoc_file[data->info->index] = mk_filename();
		if (pipe->left_child->left_child \
		&& pipe->left_child->left_child->token->redirect_type == T_HEREDOC)
		{
			do_heredoc(pipe->left_child->left_child, data);
			data->info->index++;
		}
		pipe = pipe->right_child;
	}
}

static char	*mk_filename(void)
{
	char	*str;
	int		exist;
	int		i;

	str = ft_strdup("/tmp/here_doc000");
	i = 0;
	exist = 0;
	while (exist == 0)
	{
		mk_num(str, i++);
		exist = access(str, F_OK);
		if (exist != 0)
			unlink(str);
	}
	return (str);
}

static void	mk_num(char *str, int num)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (i < 3)
	{
		if (i == 0)
		{
			str[13 + i++] = num / 100 + '0';
			num %= 100;
		}
		str[13 + i++] = num / (100 / (j * 10)) + '0';
		num %= (100 / (j * 10));
		j *= 10;
	}
}

static void	do_heredoc(t_leaf *leaf, t_data *data)
{
	int			fd;
	t_leaf		*temp;

	temp = leaf;
	while (temp)
	{
		if (temp->token->redirect_type == T_HEREDOC)
		{
			fd = open(data->info->heredoc_file[data->info->index], \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
			write_str(data, temp->left_child->token->str, fd);
		}
		temp = temp ->left_child;
	}
}

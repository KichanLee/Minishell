/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:33:58 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/08 11:49:25 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	write_str(char *content, int fd, t_data *data)
{
	char	*str;

	while (1)
	{
		str = readline ("> ");
		if (!str \
			|| (!ft_strncmp(content, str, ft_strlen(content)) \
			&& (ft_strlen(content) == (ft_strlen(str)))))
		{
			free(str);
			close(fd);
			return ;
		}
		heredoc_parser(data, fd, str);
	}
}

void	mk_num(char *str, int num)
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

// doc000 doc100 doc 200 순으로접근 유효성검사
char	*mk_filename(void)
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
		if (!exist)
			unlink(str);
	}
	return (str);
}

void	mk_heredoc_pipe(t_data *data)
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

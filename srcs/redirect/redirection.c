/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:36:30 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/08 11:40:20 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	do_input_redirect(t_leaf *leaf, t_data *data)
{
	int		fd;
	t_leaf	*temp;

	fd = 0;
	temp = leaf;
	if (temp->token->redirect_type == T_HEREDOC) // heredoc 일경우 전에만들어 준 heredoc 으로 접근해줘야함
	{
		fd = open (data->info->heredoc_file[data->info->index - 1], O_RDONLY);// 만들어지면 바로 ++을해줘서 인덱스 -1 로 접근을해야 전에 만들어진 heredoc으로 접근 
		dup2(fd, STDIN_FILENO);
		return ;
	}
	else if (temp->token->redirect_type == T_INPUT)
		fd = open(temp->left_child->token->str, O_RDONLY);
	check_file (fd, data);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	do_output_redirect(t_leaf *leaf, t_data *data)
{
	int		fd;
	t_leaf	*temp;

	fd = 0;
	temp = leaf;
	if (temp->token->redirect_type == T_APPEND)
		fd = open (temp->left_child->token->str, \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (temp->token->redirect_type == T_OUTPUT)
		fd = open (temp->left_child->token->str, \
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	check_file(fd, data);
	dup2 (fd, STDOUT_FILENO);
	close (fd);
}

void	check_redirect(t_leaf *leaf, t_data *data)
{
	t_leaf	*temp;

	*temp = leaf->left_child->left_child;
	while (temp)
	{
		if (temp->token->redirect_type == T_INPUT \
			|| temp->token->redirect_type == T_HEREDOC)
		{
			do_input_redirect(temp, data);
		}
		else if (temp->token->redirect_type == T_OUTPUT \
			|| temp->token->redirect_type == T_APPEND)
			do_output_redirect(temp, data);
		temp = temp->left_child;
	}
}

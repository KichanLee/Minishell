/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:16:07 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/17 22:04:51 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int			check_redirect(t_leaf *leaf, t_data *data);
static int	do_input_redirect(t_leaf *leaf, t_data *data);
static void	do_output_redirect(t_leaf *leaf, t_data *data);

int	check_redirect(t_leaf *leaf, t_data *data)
{
	t_leaf	*temp;

	temp = leaf->left_child->left_child;
	while (temp)
	{
		if (temp->token->redirect_type == T_INPUT \
		||temp->token->redirect_type == T_HEREDOC)
		{
			if (!do_input_redirect(temp, data))
				return (0);
		}
		else if (temp->token->redirect_type == T_OUTPUT \
		||temp->token->redirect_type == T_APPEND)
			do_output_redirect(temp, data);
		temp = temp->left_child;
	}
	return (1);
}

static int	do_input_redirect(t_leaf *leaf, t_data *data)
{
	int		fd;
	t_leaf	*temp;

	fd = 0;
	temp = leaf;
	if (temp->token->redirect_type == T_HEREDOC)
	{
		fd = open (data->info->heredoc_file[data->info->index - 1], \
		O_RDONLY);
		dup2 (fd, STDIN_FILENO);
		return (1);
	}
	else if (temp->token->redirect_type == T_INPUT)
		fd = open (temp->left_child->token->str, O_RDONLY);
	if (!check_file (fd, data))
		return (0);
	dup2 (fd, STDIN_FILENO);
	close (fd);
	return (1);
}

static void	do_output_redirect(t_leaf *leaf, t_data *data)
{
	int		fd;
	t_leaf	*temp;

	fd = 0;
	temp = leaf;
	if (temp->token->redirect_type == T_APPEND)
	{
		fd = open(temp->left_child->token->str, \
		O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
	else if (temp->token->redirect_type == T_OUTPUT)
	{
		fd = open(temp->left_child->token->str, \
		O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	check_file(fd, data);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

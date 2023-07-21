/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:42:18 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/21 21:39:57 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool	builtin(t_data *data)
{
	if (ft_strncmp(data->input->root->left_child->right_child->token->str, "cd", 3) == 0)
	{
		// printf("cd check!");
		ft_cd(data);
		printf("data name : %s\n", data->input->root->left_child->right_child->right_child->token->str);
		// printf("%s", env_search(data, "HOME")->env);
		return (TRUE);
	}
	if (ft_strncmp(data->input->root->left_child->right_child->token->str, "echo", 5) == 0)
	{
		// printf("echo check!");
		ft_echo(data);
		return (TRUE);
	}
	if (ft_strncmp(data->input->root->left_child->right_child->token->str, "exit", 5) == 0)
	{
		// printf("exit check!");
		ft_exit(data);
		return (TRUE);
	}
	if (ft_strncmp(data->input->root->left_child->right_child->token->str, "pwd", 4) == 0)
	{
		// printf("pwd check!");
		ft_pwd();
		return (TRUE);
	}
	if (ft_strncmp(data->input->root->left_child->right_child->token->str, "unset", 6) == 0)
	{
		// printf("unset check!");
		ft_unset(data);
		return (TRUE);
	}
	if (ft_strncmp(data->input->root->left_child->right_child->token->str, "export", 7) == 0)
	{
		// printf("export check!");
		ft_export(data);
		return (TRUE);
	}
	return (FALSE);
}
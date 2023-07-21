/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:06:49 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/21 17:38:18 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_data *data;
	char *command = NULL;
	(void)argc;
	(void)argv;
	init(&data, envp);

	while (1)
	{
		sig(command);
		command = readline("minishell$ ");
		if (!command)
		{
			printf("exit\n");
			return (0);
		}
		data->input = ft_substr(command, 0, ft_strlen(command));
		lexer(data);
		syntax(data);
		parser(data);

	if (ft_strncmp(data->root->left_child->right_child->token->str, "cd", 2) == 0)
	{
		// printf("cd check!");
		ft_cd(data);
		printf("data name : %s\n", data->root->left_child->right_child->right_child->token->str);
		// printf("%s", env_search(data, "HOME")->env);
	}
	if (ft_strncmp(data->root->left_child->right_child->token->str, "echo", 4) == 0)
	{
		// printf("echo check!");
		ft_echo(data);
	}
	if (ft_strncmp(data->root->left_child->right_child->token->str, "exit", 4) == 0)
	{
		// printf("exit check!");
		ft_exit(data);
	}
	if (ft_strncmp(data->root->left_child->right_child->token->str, "pwd", 3) == 0)
	{
		// printf("pwd check!");
		ft_pwd();
	}
	if (ft_strncmp(data->root->left_child->right_child->token->str, "unset", 5) == 0)
	{
		// printf("unset check!");
		ft_unset(data);
	}
	if (ft_strncmp(data->root->left_child->right_child->token->str, "export", 5) == 0)
	{
		// printf("export check!");
		ft_export(data);
	}

		// print_token(data);
		// printf("\n\n");
		// tree_print(data->root);
	}

	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:06:49 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/15 20:40:32 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*command = NULL;
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
			return(0);
		}
		data->input = ft_substr(command, 0, ft_strlen(command) - 1); //-1 개행 떼기
		lexer(data);
		syntax(data);
		parser(data);

		print_token(data);
		printf("\n\n");
		tree_print(data->root);
	}

	return (0);
}

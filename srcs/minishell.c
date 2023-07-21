/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:06:49 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/21 18:41:52 by eunwolee         ###   ########.fr       */
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

	while (TRUE)
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

		count_pipe(data);
		execute(data);
		builtin(data);

		input_free(data);
	}

	return (0);
}

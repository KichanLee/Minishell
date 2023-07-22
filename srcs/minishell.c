/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:06:49 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/22 10:16:24 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_data *data;

	(void)argc;
	(void)argv;
	init(&data, envp);
	while (TRUE)
	{
		get_input(data);
		sig();

		set_pipe(data);
		builtin(data);
		execute(data);

		free_input(data->input);
	}

	return (0);
}

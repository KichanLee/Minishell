/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:06:49 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/07 17:17:15 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	// atexit(check_leak);
	
	(void)argc;
	(void)argv;
	init(&data, envp);
	init_base(argc);
	while (TRUE)
	{
		sig();
		get_input(data);
		execute(data);
		input_free(data);
	}
	// data_free(data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:06:49 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/15 21:42:25 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	init(&data, envp);
	init_base(argc);
	data->env_array = env_to_array(data);
	if (!data->env_array)
		program_error_exit("bash");
	// for (int i =0; i<10; i++)
	while (TRUE)
	{
		sig();
		if (get_input(data) == FALSE)
			continue ;
		execute(data);
		input_free(data);
		check_leak();
	}
	data_free(data);
	return (0);
}

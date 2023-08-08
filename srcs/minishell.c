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

// int	main(int argc, char **argv, char **envp)
// {
// 	t_data	*data;

// 	(void)argc;
// 	(void)argv;
// 	init(&data, envp);
// 	init_base(argc);
	


// 	char *str = get_next_line(0);
// 	data->input = ft_substr(str, 0, ft_strlen(str) - 1); //-1 개행 떼기

// 	sig();
// 	get_input(data);
// 	system("leaks minishell");
// 	execute(data);
// 	input_free(data);
	
// 	// data_free(data);
// 	// atexit(check_leak);
// 	return (0);
// }



int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	init(&data, envp);
	init_base(argc);
	
	while (TRUE)
	{
		sig();
		// system("leaks minishell");
		get_input(data);
		execute(data);
		input_free(data);
	}
	// system("leaks minishell");
	data_free(data);
	// atexit(check_leak);
	return (0);
}

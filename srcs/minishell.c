/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:06:49 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/11 06:58:06 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*abs_home;

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	init(&data, envp);
	init_base(argc);
	
	abs_home = ft_strdup(env_search(data, "HOME")->env + 5);

	sig();
	while (TRUE)
	{
		// abs_init(data);
		// system("leaks minishell");
		// printf("abs home : %s\n", data->abs_home);
		if (get_input(data) == FALSE)
			continue ;
		execute(data);
		input_free(data);
	}
	// free(data->abs_home);
	// system("leaks minishell");
	data_free(data);
	// atexit(check_leak);
	return (0);
}

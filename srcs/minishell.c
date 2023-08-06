/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:06:49 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/06 18:10:35 by eunwolee         ###   ########.fr       */
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


	// execute(data);
	// while (TRUE)
	// {
		// count_pipe(data);
		get_input(data);
		execute(data);
		// input_free(data);
	// }
	// while (TRUE)
	// for(int i=0; i<1; i++)
	// {
	// 	char *str = get_next_line(0);
	// 	data->input = ft_substr(str, 0, ft_strlen(str) - 1); //-1 개행 떼기
	// 	if (*data->input)
	// 	{
	// 		lexer(data);
	// 		if (syntax(data) == FALSE)
	// 			return (0); //free하고 다시 input 받기
	// 		parser(data);

	// 		// print_token(data);
	// 		// printf("\n\n");
	// 		// tree_print(data->root);
	// 		// printf("\n\n");
			// input_free(data);
	// 	}
		
	// 	execute(data);
	// }
	// data_free(data);
	return (0);
}

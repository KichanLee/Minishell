/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 20:37:23 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/21 21:39:04 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	get_input(t_data *data)
{
	data->input->line = readline("minishell$ ");
	if (!data->input->line)
		program_error_exit("bash");
	lexer(data->input);
	syntax(data->input);
	parser(data->input);
}
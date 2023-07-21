/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 21:52:27 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/21 21:59:01 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	set_pipe(t_data *data)
{
	data->cmd = (t_cmd *)ft_calloc(data->input->pipe_num + 2, sizeof(t_cmd));// herdoc 때문에 하나를 여유롭게생성(ㅇㅗㅐ +2??)
	if(!data->cmd)
		program_error_exit("bash");
}
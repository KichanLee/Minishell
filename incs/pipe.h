#ifndef PIPE_H
# define PIPE_H

# include "struct.h"

int	g_exit_status;

void	set_pipe(t_data *data);
void	link_pipe(t_data *data, t_cmd *cur_cmd, t_cmd *pre_cmd);

void	redirect(t_data *data, t_leaf *cur_root);


#endif
#include "../../incs/minishell.h"

// void	free_cmd(t_pipe *base)
// {
// 	int	i;

// 	i = 0;
// 	while (base->cmd_abs[i])
// 	{
// 		free(base->cmd_abs[i]);
// 		i++;
// 	}
// 	free(base->cmd_path);
// 	free(base->com);
// }


void	close_pipe(int i, t_pipe *base,t_data *data)
{
	if (i == data->info->pipe_num)
		close(base->com[i - 1].fd[0]);
	else if (i == 0)
		close(base->com[i].fd[1]);
	else
	{
		close(base->com[i - 1].fd[0]);
		close(base->com[i].fd[1]);
	}
}

void	check_file(int fd,t_data *data)
{
	if (fd < 0)
	{
		close(fd);
		g_exit_status = 1;
		if (data->info->parent ==0) // 자식에서 종료 or 부모에서 종료 확인해주기 
			exit(1);
	}
}

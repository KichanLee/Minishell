#include "../incs/minishell.h"

void    ft_pasterror(t_data *data)
{
    printf("bash : %d: command not found\n", data->error_code);
}
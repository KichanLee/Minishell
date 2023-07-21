#ifndef EXEC_H
# define EXEC_H

# include "struct.h"
 
void    sig(char *command);
void    ft_cd(t_data *data);
void	ft_echo(t_data *data);
void	ft_exit(t_data *data);
void	ft_pwd();
void    ft_unset(t_data *data);
void    ft_export(t_data *data);
char    **join_cmd(t_leaf * com_leaf);
int     count_args(char **args);
void	update_env(t_data *data, char *key, char *value);
void    print_export_order(t_data *data);

#endif
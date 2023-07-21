#ifndef EXEC_H
# define EXEC_H

<<<<<<< HEAD
# include "struct.h"
 
void    sig(char *command);
=======
# include "../incs/struct.h"
 
void    sig(char *command);
void	sig_init(void);
>>>>>>> 568d9f62bcec9cbc64147565fd0f66fcf8aaab4e
void    ft_cd(t_data *data);
void	ft_echo(t_data *data);
void	ft_exit(t_data *data);
void	ft_pwd();
void    ft_unset(t_data *data);
void    ft_export(t_data *data);
char    **join_cmd(t_leaf * com_leaf);
int     count_args(char **args);
void	update_env(t_data *data, char *key, char *value);
<<<<<<< HEAD
=======
t_list	*env_search(t_data *data, char *key);
>>>>>>> 568d9f62bcec9cbc64147565fd0f66fcf8aaab4e
void    print_export_order(t_data *data);

#endif
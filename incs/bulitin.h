#ifndef  BULITIN_H
# define BULITIN_H

# include "struct.h"
 
 /*signal*/
void    sig(void);
void    handle_sigint(int sig);

/*builtin*/
void    exec_bulitin(int bulitnum,t_data *data , t_leaf *leaf);
int     check_bulitin_func(char *name);
void	ft_cd(t_data *data, t_leaf *cur_root);
void	ft_echo(t_leaf *cur_root);
void	ft_exit(t_data *data, t_leaf *cur_root);
void	ft_pwd(t_data *data, t_leaf *cur_root);
void	ft_unset(t_data *data, t_leaf *cur_root);
void	ft_export(t_data *data, t_leaf *cur_root);

/*builtin utils*/
char    **join_cmd(t_leaf * com_leaf);
int     count_args(char **args);
t_list	*create_env_node(char *key, char *value);
void	add_env_back(t_data *head, char *key, char *value);
void	update_env(t_data *data, char *key, char *value);

/*execute*/
void	get_input(t_data *data);

#endif
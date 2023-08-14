#ifndef  BULITIN_H
# define BULITIN_H

# include "struct.h"

# define LLONG_MAX 9223372036854775807
# define LLONG_MIN -9223372036854775808ULL

 /*signal*/
void		sig(void);
void		handle_sigint(int sig);
void		init_base(int ac);
void		child_handler(int signum);

/*builtin*/
int			check_equal(char *str);
void		ft_echo(t_leaf *cmd);
void		exec_bulitin(int bulitnum,t_data *data);
int			check_bulitin_func(char *name);
void		ft_cd(t_data *data, t_leaf *cur_root);
void		ft_exit(t_data *data, t_leaf *cur_root);
void		ft_pwd(t_data *data, t_leaf *cur_root);
void		ft_unset(t_data *data, t_leaf *cur_root);
void		update_env_export(t_data *data, char *key, char *value);
void		update_env(t_data *data, char *key, char *value);
void		ft_export(t_data *data);
void		ft_env(t_data *data, t_leaf *cur_root);
char		*check_keyval(t_data *data, char *str);
char		**sort_bubble(char **str, int size);
int			check_name(char *str);
int			check_underbar(char ch);
char		**sort_bubble(char **str, int size);
long long	char_to_long_long(char *str, int *flag);
int			is_num_str(char *str);
void		exit_not_num(t_data *data, char *str);
void        print_export_order(t_data *data);
int         plus_flag(char *str);
void        shiftstringleft(char *str);

/*builtin utils*/
char		**join_cmd(t_leaf * com_leaf);
int			count_args(char **args);
t_list		*create_env_node(char *key, char *value);
void		add_env_front(t_data *head, char *key, char *value);

#endif
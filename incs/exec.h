#ifndef EXEC_H
# define EXEC_H

# include "struct.h"
 
void    sig(void);

/*builtin*/
char	*(*get_builtin_func(char *name))(t_data *, t_leaf *);
t_bool	ft_cd(t_data *data, t_leaf *cur_root);
t_bool	ft_echo(t_data *data, t_leaf *cur_root);
t_bool	ft_exit(t_data *data, t_leaf *cur_root);
t_bool	ft_pwd(t_data *data, t_leaf *cur_root);
t_bool	ft_unset(t_data *data, t_leaf *cur_root);
t_bool	ft_export(t_data *data, t_leaf *cur_root);

/*builtin utils*/
char    **join_cmd(t_leaf * com_leaf);
int     count_args(char **args);
void	update_env(t_data *data, char *key, char *value);

void	get_input(t_data *data);

t_bool	execute(t_data *data);
void	exec_cmd(t_data *data);
t_bool	command(t_data *data, t_leaf *cur_root);

t_bool	heredoc(t_data *data, t_leaf *cur_root);
void	make_heredoc(t_data *data, t_leaf *heredoc);
char	*make_filename(void);
void	make_unique_num(char *str, int num);
void	read_heredoc(t_data *data, char *content, int fd);

#endif
#ifndef EXEC_H
# define EXEC_H

# include "struct.h"
 
 /*signal*/
void    sig(void);
void    handle_sigint(int sig);

/*builtin*/
t_bool	(*get_builtin_func(char *name))(t_data *, t_leaf *);
t_bool	ft_cd(t_data *data, t_leaf *cur_root);
t_bool	ft_echo(t_data *data, t_leaf *cur_root);
t_bool	ft_exit(t_data *data, t_leaf *cur_root);
t_bool	ft_pwd(t_data *data, t_leaf *cur_root);
t_bool	ft_unset(t_data *data, t_leaf *cur_root);
t_bool	ft_export(t_data *data, t_leaf *cur_root);

/*builtin utils*/
char    **join_cmd(t_leaf * com_leaf);
int     count_args(char **args);
t_list	*create_env_node(char *key, char *value);
void	add_env_back(t_data *head, char *key, char *value);
void	update_env(t_data *data, char *key, char *value);

/*execute*/
void	get_input(t_data *data);

t_bool	execute(t_data *data);

/*heredoc*/
t_bool	heredoc(t_data *data, t_leaf *cur_root);
void	make_heredoc(t_data *data, t_leaf *heredoc);
char	*make_filename(void);
void	make_unique_num(char *str, int num);
void	read_heredoc(t_data *data, char *content, int fd);

/*redirect*/
void	input_redirect(t_data *data, t_leaf *cur_leaf);
void	output_redirect(t_data *data, t_leaf *cur_leaf);

/*pipe*/
void	set_pipe(t_data *data);
void	link_pipe(t_data *data, t_cmd *cur_cmd, t_cmd *pre_cmd);
void	close_pipe(t_data *data, t_cmd *cur_cmd, t_cmd *pre_cmd);
void	recover_std(t_data *data);

/*path*/
void	abs_path(t_data *data, t_cmd *cmd);
void	set_path(t_leaf *cur_root, t_cmd *cmd);

#endif
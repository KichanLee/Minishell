/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulitin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:03:26 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/15 23:00:42 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  BULITIN_H
# define BULITIN_H

# include "struct.h"

# define LLONG_MAX 9223372036854775807
# define LLONG_MIN -9223372036854775808ULL

/*builtin*/
int			check_bulitin_func(char *name);
t_bool		exec_bulitin(int bulitnum, t_data *data);

void		ft_pwd(void);
t_bool		ft_cd(t_data *data);
void		ft_echo(t_leaf *cmd);
void		ft_exit(t_data *data);
t_bool		ft_export(t_data *data);
void		ft_env(t_data *data, t_leaf *cur_root);

/*ft_unset*/
void		ft_unset(t_data *data, t_leaf *cur_root);
void		update_env_double_char(t_data *data);

int			ft_cnt_args(char **args);
char		**ft_join_cmd(t_leaf *com_leaf);
long long	ft_atolong(char *str, int *flag);
void		ft_add_env_front(t_data *head, char *key, char *value);
void		ft_update_env_cd(t_data *data, char *key, char *value);
void		ft_update_env_export(t_data *data, char *key, char *value);


/*ft_export_print*/
void		print_export_order(t_data *data);
void		devide_equal(char *src, char **str1, char **str2, \
							t_bool key_need_equal);

/*ft_export_check*/
int			check_plus(char *str);
int			check_name(char *str);
int			check_equal(char *str);
int			check_underbar(char ch);
t_bool		check_env(t_data *data, char *key, char *value);

#endif
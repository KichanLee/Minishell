/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulitin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:03:26 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/14 22:14:52 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  BULITIN_H
# define BULITIN_H

# include "struct.h"

# define LLONG_MAX 9223372036854775807
# define LLONG_MIN -9223372036854775808ULL

/*builtin*/
void		ft_export(t_data *data);
void		update_env_export(t_data *data, char *key, char *value);
int			check_bulitin_func(char *name);
void		exec_bulitin(int bulitnum, t_data *data);

void		ft_pwd(void);
void		ft_echo(t_leaf *cmd);
void		ft_cd(t_data *data, t_leaf *cur_root);
void		ft_env(t_data *data, t_leaf *cur_root);
void		ft_exit(t_data *data, t_leaf *cur_root);
void		ft_unset(t_data *data, t_leaf *cur_root);

int			ft_count_args(char **args);
char		**ft_join_cmd(t_leaf *com_leaf);
long long	ft_atolong(char *str, int *flag);
void		ft_add_env_front(t_data *head, char *key, char *value);

/*ft_export_print*/
void		print_export_order(t_data *data);

/*ft_export_check*/
int			check_plus(char *str);
int			check_name(char *str);
int			check_equal(char *str);
int			check_underbar(char ch);
void		check_env(t_data *data, char *key, char *value);

#endif
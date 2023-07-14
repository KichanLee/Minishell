/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:03:31 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/12 18:25:49 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_lstdelone(t_list *lst);
void	ft_lstclear(t_list **lst);

void	ft_lstdelone(t_list *lst)
{
	if (!lst)
		return ;
	if (lst->token)
		free(lst->token);
	if (lst->env)
		free(lst->env);
	free(lst);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*cur;
	t_list	*tmp;

	if (!lst)
		return ;
	cur = *lst;
	while (cur)
	{
		tmp = cur->next;
		ft_lstdelone(cur);
		cur = tmp;
	}
	*lst = NULL;
}

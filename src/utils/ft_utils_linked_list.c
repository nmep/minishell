/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_linked_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:03:49 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/10 21:04:44 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_linked_list(t_lst_exec *lst_exec)
{
	t_lst_exec	*tmp;

	tmp = lst_exec;
	while (tmp)
	{
		print_tab_tab(tmp->args);
		tmp = tmp->next;
	}
}

int	ft_linked_list_size(t_lst_exec *lst)
{
	int	len;

	len = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

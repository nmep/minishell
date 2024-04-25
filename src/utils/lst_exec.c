/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:33:48 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/10 20:25:15 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst_exec	*ft_new_lst_exec(char **args, int fd_in, \
		int fd_out, t_expand **expand)
{
	t_lst_exec	*new;

	new = malloc(sizeof(t_lst_exec));
	if (new == NULL)
		return (NULL);
	if (args == NULL)
	{
		new->args = NULL;
		new->expand = NULL;
	}
	else
	{
		new->args = ft_strdup_2d(args);
		if (new->args == NULL)
			return (NULL);
		new->expand = ft_dup_array_expand(expand, ft_strlen_2d(args));
		if (new->expand == NULL)
			return (NULL);
	}
	new->next = NULL;
	new->prev = NULL;
	new->fd_in = fd_in;
	new->fd_out = fd_out;
	return (new);
}

t_lst_exec	*ft_lst_exec_last(t_lst_exec *lst_exec)
{
	if (lst_exec == NULL)
		return (NULL);
	while (lst_exec->next != NULL)
		lst_exec = lst_exec->next;
	return (lst_exec);
}

int	ft_lst_exec_add_back(t_lst_exec **lst_exec, t_lst_exec *new)
{
	if (new == NULL)
	{
		return (ERROR_MALLOC);
	}
	if (*lst_exec == NULL)
	{
		*lst_exec = new;
		return (SUCCESS);
	}
	new->prev = ft_lst_exec_last(*lst_exec);
	ft_lst_exec_last(*lst_exec)->next = new;
	return (SUCCESS);
}

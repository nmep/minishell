/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 01:02:19 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/05 11:51:34 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expand	*ft_new_expand(int act)
{
	t_expand	*new;

	new = malloc (sizeof(t_expand));
	if (new == NULL)
		return (NULL);
	new->act = act;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_expand	*ft_last_expand(t_expand *expand)
{
	if (expand == NULL)
		return (NULL);
	while (expand->next != NULL)
		expand = expand->next;
	return (expand);
}

int	ft_add_back_expand(t_expand **expand, t_expand *new)
{
	if (new == NULL)
		return (ERROR_MALLOC);
	if (*expand == NULL)
		*expand = new;
	else
	{
		new->prev = ft_last_expand(*expand);
		ft_last_expand(*expand)->next = new;
	}
	return (SUCCESS);
}

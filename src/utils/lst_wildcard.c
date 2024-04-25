/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:21:43 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/05 11:52:43 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_wildcard	*ft_lst_wildcard_new(char *str)
{
	t_wildcard	*new;

	new = malloc(sizeof(t_wildcard));
	if (new == NULL)
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	new->str = ft_strdup(str);
	if (new->str == NULL)
		return (free(new), NULL);
	return (new);
}

t_wildcard	*ft_lst_wildcard_last(t_wildcard *ls)
{
	while (ls->next != NULL)
		ls = ls->next;
	return (ls);
}

int	ft_lst_wildcard_add_back(t_wildcard **ls, t_wildcard *new)
{
	if (new == NULL)
		return (ERROR_MALLOC);
	if (*ls == NULL)
	{
		*ls = new;
		return (SUCCESS);
	}
	new->prev = ft_lst_wildcard_last(*ls);
	ft_lst_wildcard_last(*ls)->next = new;
	return (SUCCESS);
}

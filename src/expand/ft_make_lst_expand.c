/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_lst_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 01:23:54 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/05 10:37:12 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_make_lst_expand(t_expand **expand, t_data_parse *data_parse)
{
	if (data_parse->single_quote_open == CLOSE)
	{
		if (ft_add_back_expand(expand, ft_new_expand(CHANGE)) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else
	{
		if (ft_add_back_expand(expand, ft_new_expand(KEEP)) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	return (SUCCESS);
}

int	ft_size_expand(t_expand **expand)
{
	int	len;

	len = 0;
	while (expand != NULL && expand[len] != NULL)
		len++;
	return (len);
}

int	ft_complete_expand(t_expand ***expand, t_expand *add, int size)
{
	t_expand	**new;
	int			index;

	new = malloc ((size + 1) * sizeof(t_expand *));
	if (new == NULL)
		return (ERROR_MALLOC);
	index = 0;
	while (*expand != NULL && index < size - 1)
	{
		new[index] = (*expand)[index];
		index++;
	}
	new[index++] = add;
	free(*expand);
	*expand = new;
	return (SUCCESS);
}

t_expand	**ft_dup_array_expand(t_expand **expand, int size)
{
	t_expand	**new;
	int			index;

	new = malloc(size * sizeof(t_expand));
	if (new == NULL)
		return (NULL);
	index = 0;
	while (index <= size)
	{
		new[index] = expand[index];
		index++;
	}
	free(expand);
	return (new);
}

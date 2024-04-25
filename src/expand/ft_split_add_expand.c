/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_add_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:08:43 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/10 22:36:39 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_split_add_expand_part1(char ***split, char **new_str, \
		int *add_next, int *add_start)
{
	*split = ft_split(*new_str, ' ');
	if (*split == NULL)
		return (ERROR_MALLOC);
	if ((*new_str)[0] != ' ' && *add_next != -1)
		*add_start = 1;
	else
		*add_start = 0;
	if ((*new_str)[ft_strlen(*new_str)] == ' ')
		*add_next = 0;
	else
		*add_next = 1;
	return (SUCCESS);
}

int	ft_set_split_add_expand_part2(char ***new, char ***res, char **split)
{
	int	index;

	*new = malloc(sizeof(char *));
	if (*new == NULL)
		return (free_2d(split), ERROR_MALLOC);
	(*new)[0] = NULL;
	index = -1;
	while ((*res)[++index])
	{
		*new = ft_add_to_2d_expand(*new, (*res)[index]);
		if (*new == NULL)
			return (free_2d(split), ERROR_MALLOC);
	}
	return (SUCCESS);
}

int	ft_clear_buffer_in_split_expand(int index, char ***new, \
		int add_start, char **split)
{
	int	len;

	len = ft_strlen_2d(*new);
	if (len != 0 && index == 0 && add_start == 1)
	{
		(*new)[len - 1] = ft_strjoin_1_malloc((*new)[len - 1], split[index]);
		if ((*new)[len - 1] == NULL)
			return (free_2d(split), free_2d(*new), ERROR_MALLOC);
	}
	else
	{
		*new = ft_add_to_2d_expand(*new, split[index]);
		if (*new == NULL)
			return (free_2d(split), ERROR_MALLOC);
	}
	return (SUCCESS);
}

int	ft_not_found(char **split, char ***new, int add_start)
{
	int	len;

	len = ft_strlen_2d(*new);
	if (len != 0 && add_start == 1)
	{
		(*new)[len - 1] = ft_strjoin_1_malloc((*new)[len - 1], "\0");
		if ((*new)[len - 1] == NULL)
			return (free_2d(split), free_2d(*new), ERROR_MALLOC);
	}
	else
	{
		*new = ft_add_to_2d_expand(*new, "\0");
		if (*new == NULL)
			return (free_2d(split), ERROR_MALLOC);
	}
	return (SUCCESS);
}

int	ft_split_add_expand(char *new_str, char ***res, int *add_next)
{
	char	**split;
	char	**new;
	int		add_start;
	int		index;

	if (ft_set_split_add_expand_part1(&split, &new_str, add_next, \
				&add_start) != SUCCESS)
		return (ERROR_MALLOC);
	if (ft_set_split_add_expand_part2(&new, res, split) != SUCCESS)
		return (ERROR_MALLOC);
	index = -1;
	if (split[0] == NULL)
	{
		if (ft_not_found(split, &new, add_start) != SUCCESS)
			return (ERROR_MALLOC);
	}
	while (split[++index])
	{
		if (ft_clear_buffer_in_split_expand(index, &new, \
					add_start, split) != SUCCESS)
			return (ERROR_MALLOC);
	}
	free_2d(*res);
	*res = new;
	return (free_2d(split), SUCCESS);
}

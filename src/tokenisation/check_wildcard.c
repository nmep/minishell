/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:15:27 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/12 14:53:16 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchr_wildcard(char *str, char *find, int index_str)
{
	int	i;
	int	j;

	i = index_str;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == find[j])
		{
			j++;
			if (j == ft_strlen(find))
			{
				return ((i - index_str) + j);
			}
		}
		i++;
		if (i > ft_strlen(str) - ft_strlen(find))
			return (0);
	}
	return (0);
}

int	ft_check_all(char **split, char *str)
{
	int	index_split;
	int	index_str;
	int	tmp;
	int	len_str;

	len_str = ft_strlen(str);
	index_split = 0;
	index_str = 0;
	while (split[index_split] && index_str < len_str)
	{
		tmp = ft_strchr_wildcard(str, split[index_split++], index_str);
		if (tmp == 0)
			return (0);
		index_str += tmp;
	}
	if (split[index_split] != NULL)
		return (0);
	return (1);
}

int	ft_check_before(char *to_find, char **split, char *str)
{
	if (to_find[0] == '*')
		return (1);
	if (ft_strncmp(split[0], str, ft_strlen(split[0])))
		return (0);
	return (1);
}

int	ft_check_after(char *to_find, char **split, char *str)
{
	int	index;

	if (to_find[ft_strlen(to_find) - 1] == '*')
		return (1);
	index = ft_strlen(str) - ft_strlen(split[ft_strlen_2d(split) - 1]);
	if (index < 0)
		return (0);
	if (ft_strncmp(split[ft_strlen_2d(split) - 1], &str[index], \
				ft_strlen(split[ft_strlen_2d(split) - 1])))
		return (0);
	return (1);
}

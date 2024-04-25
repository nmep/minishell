/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:39:11 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/07 16:21:42 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int	ft_strlen(char *str)
{
	int	index;

	if (str == NULL)
		return (0);
	index = 0;
	while (str[index])
		index++;
	return (index);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
	{
		return (1);
	}
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_occ(char *str, char c)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (str[index])
	{
		if (str[index] == c)
			count++;
		index++;
	}
	return (count);
}

int	ft_strchr(char *str, char *find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == find[j])
		{
			j++;
			if (j == ft_strlen(find))
				return (1);
		}
		i++;
		if (i > ft_strlen(str) - ft_strlen(find))
			return (0);
	}
	return (0);
}

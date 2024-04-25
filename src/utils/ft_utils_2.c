/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:56:45 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/09 23:16:59 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_size_malloc_long_long(long long nb)
{
	int	count;

	count = 0;
	if (nb >= 0 && nb <= 9)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		count++;
	}
	while (nb > 0)
	{
		count++;
		nb /= 10;
	}
	return (count);
}

char	*ft_itoa_long_long(long long nb)
{
	char	*str;
	int		count;
	int		index;

	count = ft_size_malloc_long_long(nb);
	str = malloc ((count + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	index = count - 1;
	while (index >= 0)
	{
		str[index--] = (nb % 10) + 48;
		nb /= 10;
	}
	str[count] = '\0';
	return (str);
}

char	*ft_str_cat_long_long(char *new_str, long long status)
{
	char	*exit;
	char	*cat;
	int		i;
	int		j;

	exit = ft_itoa_long_long(status);
	if (exit == NULL)
		return (free(new_str), NULL);
	cat = malloc ((ft_strlen(new_str) + ft_strlen(exit) + 1) * sizeof(char));
	if (cat == NULL)
		return (free(exit), free(new_str), NULL);
	i = -1;
	while (new_str[++i])
		cat[i] = new_str[i];
	j = -1;
	while (exit[++j])
		cat[i + j] = exit[j];
	cat[i + j] = '\0';
	return (free(exit), free(new_str), cat);
}

char	**ft_add_2d_to_2d(char **base, char **add)
{
	char	**new;
	int		index;
	int		index_2;

	new = malloc((ft_strlen_2d(base) + ft_strlen_2d(add) + 1) * sizeof(char *));
	if (new == NULL)
		return (NULL);
	index = 0;
	while (base[index])
	{
		new[index] = ft_strdup(base[index]);
		if (new[index] == NULL)
			return (NULL);
		index++;
	}
	index_2 = 0;
	while (add[index_2])
	{
		new[index + index_2] = ft_strdup(add[index_2]);
		if (new[index + index_2] == NULL)
			return (NULL);
		index_2++;
	}
	new[++index] = NULL;
	return (new);
}

char	**ft_add_to_2d(char **base, char *add)
{
	char	**new;
	int		index;

	new = malloc((ft_strlen_2d(base) + 2) * sizeof(char *));
	if (new == NULL)
		return (NULL);
	index = 0;
	while (base != NULL && base[index])
	{
		new[index] = ft_strdup(base[index]);
		if (new[index] == NULL)
			return (NULL);
		index++;
	}
	new[index] = ft_strdup(add);
	if (new[index] == NULL)
		return (NULL);
	new[++index] = NULL;
	if (base != NULL)
		free_2d(base);
	return (new);
}

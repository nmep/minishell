/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:13:46 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/23 10:03:05 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_char(char *str, char c)
{
	char	*join;
	int		i;

	join = malloc ((ft_strlen(str) + 2) * sizeof(char));
	if (join == NULL)
		return (free(str), NULL);
	i = -1;
	while (str[++i])
		join[i] = str[i];
	join[i++] = c;
	join[i] = '\0';
	return (free(str), join);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*join;
	int		i;
	int		j;

	if (str2 == NULL)
		return (str1);
	join = malloc ((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
	if (join == NULL)
		return (NULL);
	i = -1;
	while (str1[++i])
		join[i] = str1[i];
	j = -1;
	while (str2[++j])
		join[i + j] = str2[j];
	join[i + j] = '\0';
	return (join);
}

char	**ft_strdup_2d(char **str)
{
	char	**new;
	int		index;

	new = malloc((ft_strlen_2d(str) + 1) * sizeof(char *));
	if (new == NULL)
		return (free_2d(str), NULL);
	index = -1;
	while (str[++index])
	{
		new[index] = ft_strdup(str[index]);
		if (new[index] == NULL)
			return (free_2d(str), ft_free_2d_index(new, index), NULL);
	}
	new[index] = NULL;
	return (new);
}

char	*ft_strjoin_1_malloc_expand(char *str1, char *str2)
{
	char	*join;
	int		i;
	int		j;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	if (str2 == NULL)
		return (ft_strdup(str1));
	if (str1 == NULL)
		return (ft_strdup(str2));
	join = malloc ((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
	if (join == NULL)
		return (free(str1), NULL);
	i = -1;
	while (str1[++i])
		join[i] = str1[i];
	j = -1;
	while (str2[++j])
		join[i + j] = str2[j];
	join[i + j] = '\0';
	return (free(str1), join);
}

void	ft_end_1(int size, int *exit_status)
{
	if (size == -1)
		*exit_status = 130;
}

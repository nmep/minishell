/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 05:46:43 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/06 15:17:05 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_2d_index(char **str, int index)
{
	while (--index)
		free(str[index]);
	free(str);
}

int	ft_strlen_2d(char **str)
{
	int	index;

	if (str == NULL)
		return (0);
	index = 0;
	while (str[index])
		index++;
	return (index);
}

char	**ft_join_2d_args_null(char *str, char **new)
{
	int	index;

	index = 0;
	new[index] = ft_strdup(str);
	if (new[index] == NULL)
		return (free(new), NULL);
	new[++index] = NULL;
	return (new);
}

char	**ft_join_2d(char **args_cmd, char *str)
{
	char	**new;
	int		index;

	new = malloc((ft_strlen_2d(args_cmd) + 2) * sizeof(char *));
	if (new == NULL)
		return (free_2d(args_cmd), NULL);
	if (args_cmd == NULL)
		return (ft_join_2d_args_null(str, new));
	index = -1;
	while (args_cmd[++index])
	{
		new[index] = ft_strdup(args_cmd[index]);
		if (new[index] == NULL)
			return (ft_free_2d_index(new, index), free_2d(args_cmd), NULL);
	}
	new[index] = ft_strdup(str);
	if (new[index] == NULL)
		return (ft_free_2d_index(new, index), free_2d(args_cmd), NULL);
	new[++index] = NULL;
	return (free_2d(args_cmd), new);
}

int	is_input_only_whitespace(char *str)
{
	int	index;

	if (str == NULL)
		return (0);
	index = 0;
	while (str[index])
	{
		if (str[index] != ' ' && (str[index] < 9 || str[index] > 13))
			return (1);
		index++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:31:46 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/12 03:00:01 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_ls(t_wildcard **ls)
{
	struct dirent	*entry;
	DIR				*directory;

	directory = opendir(".");
	if (directory == NULL)
	{
		printf("minishell: opendir failed\n");
		return (ERROR);
	}
	while (1)
	{
		entry = readdir(directory);
		if (entry == NULL)
			break ;
		if (ft_lst_wildcard_add_back(ls, \
		ft_lst_wildcard_new(entry->d_name)) != SUCCESS)
		{
			closedir(directory);
			return (ft_print_error_malloc(), ERROR_MALLOC);
		}
	}
	closedir(directory);
	return (SUCCESS);
}

int	ft_set_add_wildcard(char ***split, char *add, char ***new)
{
	*new = NULL;
	*split = ft_split(add, '*');
	if (*split == NULL)
		return (ERROR_MALLOC);
	return (SUCCESS);
}

char	**ft_no_wildcard(char *add, char **base)
{
	char	**new;

	new = ft_add_to_2d(base, add);
	if (new == NULL)
		return (free(add), NULL);
	return (free(add), new);
}

int	ft_condition_wildcard(int *found, char **base, char ***new, t_wildcard *ls)
{
	if (*found == 0)
	{
		*new = ft_add_to_2d(base, ls->str);
		if (*new == NULL)
			return (ERROR_MALLOC);
	}
	else
	{
		*new = ft_add_to_2d(*new, ls->str);
		if (*new == NULL)
			return (ERROR_MALLOC);
	}
	*found = 1;
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_name_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:13:02 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/14 00:07:02 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_export_name(char *str)
{
	int		i;
	int		j;
	char	*export_name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	export_name = malloc(i + 1);
	if (!export_name)
		return (NULL);
	j = 0;
	while (j < i)
	{
		export_name[j] = str[j];
		j++;
	}
	export_name[j] = '\0';
	return (export_name);
}

void	ft_export_name2(int *i, int *j, int *count)
{
	*i = -1;
	*j = -1;
	*count = -1;
}

int	ft_export_name(char *str, char **export_name)
{
	int	i;
	int	j;
	int	count;

	ft_export_name2(&i, &j, &count);
	*export_name = malloc(ft_strlen(str) + 1);
	if (!(*export_name))
		return (ERROR_MALLOC);
	while (str[++i] && str[i] != '=')
	{
		if (str[i] == '\\' && count == 1)
		{
			(*export_name)[++j] = '\\';
			count = 0;
		}
		if (str[i] == '\\')
			count = 1;
		else
			(*export_name)[++j] = str[i];
	}
	(*export_name)[i] = '\0';
	if (!ft_find_back_s(*export_name))
		return (0);
	ft_add_export_value(export_name, str);
	return (1);
}

char	*assign_export_empty_value(char *export)
{
	int		i;
	char	*new_export;

	i = 0;
	while (export[i] && export[i] != '=')
		i++;
	if (!export[i])
	{
		i = -1;
		new_export = malloc(ft_strlen(export) + 2);
		while (export[++i])
			new_export[i] = export[i];
		export[i++] = '=';
		export[i++] = '\0';
	}
	if (export[i] == '=')
	{
		new_export = malloc(ft_strlen(export) + 1);
		i = -1;
		while (export[++i])
			new_export[i] = export[i];
		new_export[i++] = '\0';
	}
	free(export);
	return (new_export);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:36:06 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/09 16:15:07 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_empty_export(char *export)
{
	char	*export_equal;
	char	*export_non_equal;
	int		res;

	res = 0;
	export_equal = export_and_equal(export);
	export_non_equal = export_and_empty(export);
	if (!equal_or_nothing(export))
	{
		if (!ft_strcmp(export_equal, export))
			res = 1;
	}
	else
	{
		if (!ft_strcmp(export_non_equal, export))
			res = 2;
	}
	free(export_equal);
	free(export_non_equal);
	if (res == 1)
		return (1);
	else if (res == 2)
		return (2);
	return (0);
}

char	*add_equal_null_char(char *export)
{
	char	*new_export;
	int		i;

	i = 0;
	new_export = malloc(ft_strlen(export) + 1);
	if (!new_export)
		return (NULL);
	while (export[i])
	{
		new_export[i] = export[i];
		i++;
	}
	new_export[i++] = '\0';
	free(export);
	return (new_export);
}

char	*add_null(char *export)
{
	char	*new_export;
	int		i;

	i = 0;
	new_export = malloc(ft_strlen(export) + 2);
	if (!new_export)
		return (NULL);
	while (export[i])
	{
		new_export[i] = export[i];
		i++;
	}
	new_export[i++] = '=';
	new_export[i++] = '\0';
	free(export);
	return (new_export);
}

int	value_start_equal(char *export)
{
	int	i;

	i = 0;
	while (export[i] && export[i] != '=')
		i++;
	if (export[i] && ((export[i] == '=' && export[i + 1] == '\0')
			|| (export[i] == '=' && export[i + 1] == '=')))
		return (1);
	return (0);
}

char	*add_quote_to_value(char *export)
{
	int		i;
	int		j;
	char	*new_export;

	i = -1;
	new_export = malloc(ft_strlen(export) + 4);
	while (export[++i] != '=')
		new_export[i] = export[i];
	j = i;
	new_export[i++] = '=';
	new_export[i++] = '\'';
	while (export[++j])
	{
		new_export[i] = export[j];
		i++;
	}
	new_export[i] = '\'';
	new_export[++i] = '\0';
	free(export);
	return (new_export);
}

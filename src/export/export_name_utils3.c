/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_name_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:34:46 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/29 19:34:59 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_back_s(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (str[i] == '\\')
			count++;
		i++;
	}
	if (count > 1)
		return (0);
	return (1);
}

int	equal_or_nothing(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (0);
	return (1);
}

char	*export_and_equal(char *export)
{
	char	*export_equal;
	int		i;

	i = 0;
	export_equal = (char *) malloc(sizeof(char) * (ft_strlen(export) + 1));
	if (!export_equal)
		perror("malloc export_and equal\n");
	while (export[i])
	{
		export_equal[i] = export[i];
		i++;
	}
	export_equal[i] = '\0';
	return (export_equal);
}

char	*export_and_empty(char *export)
{
	char	*export_empty;
	int		i;

	export_empty = malloc(ft_strlen(export) + 1);
	if (!export_empty)
		perror("export and empty\n");
	i = -1;
	while (export[++i])
		export_empty[i] = export[i];
	export_empty[i] = '\0';
	return (export_empty);
}

int	check_after_equal(char *export)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (export[i])
	{
		if (export[i] && (export[i] == '=' && export[i + 1] == '='))
			return (1);
		if ((export[i] != '=' && flag == 1))
			return (1);
		if (export[i] == '=')
			flag = 1;
		i++;
	}
	return (0);
}

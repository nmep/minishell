/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_name_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:10:21 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/14 00:16:13 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_export_name(char *str)
{
	int				i;
	int				j;
	char			*except;

	j = 0;
	except = ft_get_str("!\\[]@#$%^&*-()+=/?.,`~\" ");
	while (except[j])
	{
		i = 0;
		while (str[i] && str[i] != '=')
		{
			if (str[i] == except[j])
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

void	ft_add_export_value(char **export, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1] != '=')
		i++;
	while (str[i])
	{
		(*export)[i] = str[i];
		i++;
	}
	(*export)[i] = '\0';
}

int	ft_is_export_in_env(char **env, char *str)
{
	char	*export_name;
	char	*export_name_env;
	int		i;

	export_name = ft_find_export_name(str);
	if (!export_name)
		return (-1);
	i = 0;
	while (env[i] != NULL)
	{
		export_name_env = ft_find_export_name(env[i]);
		if (ft_strcmp(export_name, export_name_env) == 0)
		{
			free(export_name_env);
			free(export_name);
			return (i);
		}
		free(export_name_env);
		i++;
	}
	free(export_name);
	return (-1);
}

void	ft_change_export(char ***env, char *str)
{
	int	index_export;

	index_export = ft_find_export_index(*env, str);
	if (index_export == -1)
		return ;
	free((*env)[index_export]);
	(*env)[index_export] = ft_str_dup_env(str, (*env)[index_export]);
}

int	ft_find_export_index(char **env, char *str)
{
	int		i;
	char	*export_name;
	char	*export_name_env;

	i = 0;
	export_name = ft_find_export_name(str);
	while (env[i])
	{
		export_name_env = ft_find_export_name(env[i]);
		if (ft_strcmp(export_name_env, export_name) == 0)
		{
			free(export_name_env);
			free(export_name);
			return (i);
		}
		free(export_name_env);
		i++;
	}
	free(export_name);
	return (-1);
}

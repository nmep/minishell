/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:01:18 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/20 01:10:00 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_unset_index(char **env, char *unset_str)
{
	int		i;
	int		finded;
	char	*export_name;

	i = 0;
	finded = 0;
	while (env[i])
	{
		export_name = ft_find_export_name(env[i]);
		if (ft_strcmp(export_name, unset_str) == 0)
		{
			finded = 1;
			free(export_name);
			break ;
		}
		free(export_name);
		i++;
	}
	if (finded == 1)
		return (i);
	return (-1);
}

int	ft_copy_env_exept_unset(char **env, int unset_index)
{
	int		i;

	i = -1;
	while (++i < unset_index)
		;
	if (env[i + 1] == NULL)
	{
		free(env[i]);
		env[i] = NULL;
		return (0);
	}
	while (env[i + 1])
	{
		free(env[i]);
		env[i] = ft_str_dup_env(env[i + 1], env[i]);
		if (env[i] == NULL)
			return (free_tab_tab(env), ERROR_MALLOC);
		i++;
	}
	if (env[i - 1] != NULL)
	{
		free(env[i]);
		env[i] = NULL;
	}
	return (0);
}

int	ft_unset_is_in_env(char **env, char *unset_str)
{
	int		i;
	char	*unset_name;
	char	*env_name;

	i = -1;
	unset_name = ft_find_export_name(unset_str);
	while (env[++i])
	{
		env_name = ft_find_export_name(env[i]);
		if (ft_strcmp(env_name, unset_name) == 0)
		{
			free(env_name);
			free(unset_name);
			return (0);
		}
		free(env_name);
	}
	free(unset_name);
	return (1);
}

int	ft_unset2(char ***env, char *unset_str)
{
	int	unset_index;
	int	status;

	if (!unset_str)
		return (0);
	else if (unset_str[0] == '\0')
		return (0);
	if (ft_unset_is_in_env(*env, unset_str) == 1)
		return (0);
	unset_index = ft_find_unset_index(*env, unset_str);
	if (unset_index == -1)
		return (0);
	status = ft_copy_env_exept_unset(*env, unset_index);
	if (ft_realloc_env(env, 0) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	return (status);
}

int	ft_unset(char ***env, char **cmd)
{
	int	i;
	int	status;

	i = 0;
	if (!cmd[1])
		return (0);
	while (cmd[++i])
		status = ft_unset2(env, cmd[i]);
	return (status);
}

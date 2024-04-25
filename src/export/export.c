/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:51:52 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/14 00:12:44 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_parsing(char *export_str, char **export, int *res)
{
	*res = 0;
	if (export_str[0] == '=' || !ft_check_export_name(export_str)
		|| !ft_is_ascii(export_str[0]))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(export_str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		*res = 1;
		return ;
	}
	if (!ft_export_name(export_str, export))
	{
		ft_putstr_fd("export: not valid in this context: ", 2);
		ft_putstr_fd(*export, 2);
		ft_putstr_fd("\n", 2);
		*res = 1;
		return (free(*export));
	}
}

char	*ft_get_export_value(char *str)
{
	int		i;
	int		j;
	char	*export_value;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	while (str[j])
		j++;
	export_value = malloc(j + 1);
	if (!export_value)
		return (NULL);
	j = 0;
	while (str[++i])
	{
		export_value[j] = str[i];
		j++;
	}
	export_value[j] = '\0';
	return (export_value);
}

int	ft_do_the_export(char ***env, char *export_str)
{
	char	*export;
	int		i;
	int		res;

	if (ft_check_shlvl_export(env, export_str) == 0)
		return (0);
	ft_export_parsing(export_str, &export, &res);
	if (res != 0)
		return (res);
	if (ft_is_export_in_env(*env, export) != -1)
	{
		ft_change_export(env, export);
		return (free(export), 0);
	}
	i = ft_realloc_env(env, 1);
	(*env)[i] = ft_str_dup_env(export, (*env)[i]);
	(*env)[i + 1] = NULL;
	free(export);
	return (0);
}

int	ft_export(char ***env, char **arg, int free)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!arg[1])
	{
		ft_print_env_ascii_order(*env);
		return (0);
	}
	while (arg[i])
	{
		status = ft_do_the_export(env, arg[i]);
		i++;
	}
	if (free)
		free_tab_tab(arg);
	return (status);
}

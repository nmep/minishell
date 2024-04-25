/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:41:27 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/13 22:52:41 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_env_value(char ***new_env)
{
	int	i;

	i = -1;
	while ((*new_env)[++i])
	{
		if (value_start_equal((*new_env)[i]) == 1)
		{
			(*new_env)[i] = add_quote_to_value((*new_env)[i]);
		}
	}
}

int	ft_check_shlvl_export(char ***env, char *export_str)
{
	int		i;
	char	*export_name;
	char	*export_value;

	export_name = ft_find_export_name(export_str);
	if (!export_name)
		return (ERROR_MALLOC);
	if (ft_strcmp(export_name, "SHLVL") != 0)
		return (free(export_name), 2);
	i = 0;
	free(export_name);
	while ((*env)[i])
	{
		export_name = ft_find_export_name((*env)[i]);
		if (ft_strcmp(export_name, "SHLVL") == 0)
		{
			export_value = ft_get_export_value(export_str);
			free((*env)[i]);
			(*env)[i] = ft_change_shlvl_export(export_value);
			return (free(export_value), free(export_name), 0);
		}
		free(export_name);
		i++;
	}
	return (2);
}

int	ft_check_if_i_print_env_i(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '=')
			flag++;
		i++;
	}
	if (flag > 0)
		return (1);
	return (0);
}

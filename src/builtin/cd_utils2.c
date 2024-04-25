/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:21:48 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/14 04:08:13 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_msg_err_getcwd(void)
{
	ft_putstr_fd("sh: 0 : getcwd() failed: No such file or directory\n", 2);
}

int	ft_get_env_value3(char *env, int len, char **env_value)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (env[j] && env[j] != '=')
		j++;
	k = 0;
	*env_value = malloc(len + 1);
	if (!(*env_value))
		return (ERROR_MALLOC);
	while (env[++j])
		(*env_value)[k++] = env[j];
	(*env_value)[k] = '\0';
	return (0);
}

int	ft_get_env_value2(char **env_name, char *env, char *str, char **env_value)
{
	int		len;

	len = 1;
	*env_name = ft_find_export_name(env);
	if (!(*env_name))
		return (ERROR_MALLOC);
	if (ft_strcmp(*env_name, str) == 0)
	{
		len = ft_strlen(env) - ft_strlen(*env_name);
		free(*env_name);
		if (len == 0)
		{
			*env_value = malloc(1);
			(*env_value)[0] = '\0';
			return (0);
		}
		if (ft_get_env_value3(env, len, env_value) == ERROR_MALLOC)
			return (ERROR_MALLOC);
		return (0);
	}
	return (free(*env_name), 1);
}

char	*ft_get_env_value(char **env, char *str)
{
	int		i;
	int		check;
	char	*env_value;
	char	*env_name;

	i = -1;
	env_value = NULL;
	while (env[++i])
	{
		check = ft_get_env_value2(&env_name, env[i], str, &env_value);
		if (check == 1)
			;
		else if (check == ERROR_MALLOC)
			return (NULL);
		else
			return (env_value);
	}
	return (NULL);
}

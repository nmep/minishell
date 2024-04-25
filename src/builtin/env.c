/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:28:44 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/13 22:55:40 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pustr_builtin_env(char *str)
{
	char	*env_val;

	env_val = ft_strjoin_wihtout_free(str, "\n");
	if (write(1, env_val, ft_strlen(env_val)) == -1)
	{
		ft_putstr_fd("env: write error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		free(env_val);
		return (125);
	}
	free(env_val);
	return (0);
}

int	ft_env(char **env)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	if (getenv("PATH") == NULL && is_export_name_in_env(env, "PATH") != -1)
		i = 0;
	while (env[++i])
	{
		if (ft_check_if_i_print_env_i(env[i]) == 0)
			continue ;
		status = ft_pustr_builtin_env(env[i]);
		if (status == 125)
			return (status);
	}
	return (status);
}

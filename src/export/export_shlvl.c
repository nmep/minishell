/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:10:37 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/12 22:05:26 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi_int_shlvl_export(char *nb)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (nb[0] == '+')
		i++;
	while (nb[i])
	{
		if (nb[i] < '0' || nb[i] > '9')
			return (0);
		i++;
	}
	i = 0;
	while (nb[i])
	{
		if (nb[i] < '0' || nb[i] > '9')
			return (0);
		res = res * 10 + nb[i] - 48;
		i++;
	}
	return (res);
}

char	*ft_change_shlvl_export(char *shlvl)
{
	char	*res_val;
	char	*res;

	res_val = ft_itoa_shlvl(ft_atoi_int_shlvl_export(shlvl));
	if (!res_val)
		return (NULL);
	res = ft_strjoin_wihtout_free("SHLVL=", res_val);
	free(res_val);
	return (res);
}

int	ft_copy_env_2(char ***env, char **envp_name, char **envp, int *i)
{
	*envp_name = ft_find_export_name(envp[*i]);
	if (ft_strcmp(*envp_name, "SHLVL") == 0)
	{
		(*env)[*i] = ft_change_shlvl(envp, getenv("SHLVL"));
		free(*envp_name);
		(*i)++;
		return (1);
	}
	free(*envp_name);
	(*env)[*i] = ft_str_dup_env(envp[*i], (*env)[*i]);
	(*i)++;
	return (0);
}

char	**ft_copy_env(char **envp)
{
	char	**env;
	int		len_envp;
	int		i;
	char	*envp_name;

	len_envp = ft_strlen_2d(envp);
	i = 0;
	ft_get_path_in_env(envp, &env, &i);
	if (!env)
		return (NULL);
	if (!envp[0])
	{
		ft_check_missing_env(&env, &i);
		return (env);
	}
	while (envp[i])
		ft_copy_env_2(&env, &envp_name, envp, &i);
	ft_check_missing_env(&env, &i);
	env[i] = NULL;
	return (env);
}

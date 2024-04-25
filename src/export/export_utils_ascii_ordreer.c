/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_ascii_ordreer.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:07:38 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/09 22:46:11 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp_ascii_order(char *s1, char *s2)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while ((s1[i] || s2[i]) && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	print_tab_tab_ascii_order(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], "_=", 2) == 0
			|| ft_strncmp(tab[i], "PATH=", 5) == 0)
		{
			i++;
			continue ;
		}
		printf("declare -x %s\n", tab[i]);
		i++;
	}
}

void	ft_print_env_ascii_ordrer_2(int i, char ***new_env)
{
	int		j;
	char	*tmp;
	char	*export_name_i;
	char	*export_name_j;

	j = i;
	while ((*new_env)[j])
	{
		export_name_i = ft_find_export_name((*new_env)[i]);
		export_name_j = ft_find_export_name((*new_env)[j]);
		if (ft_strcmp_ascii_order(export_name_i, export_name_j) > 0)
		{
			tmp = ft_str_dup_env((*new_env)[i], tmp);
			free((*new_env)[i]);
			(*new_env)[i] = ft_str_dup_env((*new_env)[j], (*new_env)[i]);
			free((*new_env)[j]);
			(*new_env)[j] = ft_str_dup_env(tmp, (*new_env)[j]);
			free(tmp);
		}
		free(export_name_i);
		free(export_name_j);
		j++;
	}
}

void	ft_print_env_ascii_order(char **env)
{
	char	**new_env;
	int		i;

	i = -1;
	new_env = dup_env_ascii_order(env);
	clean_env_value(&new_env);
	while (new_env[++i])
		ft_print_env_ascii_ordrer_2(i, &new_env);
	print_tab_tab_ascii_order(new_env);
	free_tab_tab(new_env);
}

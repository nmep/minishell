/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cat_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 07:36:28 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/13 01:11:02 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lim_isolate(char *str, int index)
{
	index++;
	while (ft_isalphanum(str[index]) || str[index] == '*')
		index++;
	return (index);
}

char	*ft_str_isolate(char *str, int index_debut, int index_fin)
{
	char	*new_str;
	int		index_new_str;

	index_debut++;
	new_str = malloc((index_fin - index_debut + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	index_new_str = 0;
	while (index_debut + index_new_str < index_fin)
	{
		new_str[index_new_str] = str[index_debut + index_new_str];
		index_new_str++;
	}
	new_str[index_new_str] = '\0';
	return (new_str);
}

char	*ft_add_env(char *str, char *new_str, int index, char **env)
{
	char	*str_isolate;
	char	*res;
	char	*tmp;

	str_isolate = ft_str_isolate(str, index, ft_lim_isolate(str, index));
	if (str_isolate == NULL)
		return (free(new_str), NULL);
	if (str_isolate[0] == '\0')
	{
		free(str_isolate);
		new_str = ft_join_char(new_str, '$');
		if (new_str == NULL)
			return (NULL);
		return (new_str);
	}
	tmp = ft_get_env_value(env, str_isolate);
	res = ft_strjoin(new_str, tmp);
	if (res == NULL)
		return (free(str_isolate), free(tmp), free(new_str), NULL);
	if (res[0] != '\0')
		free(new_str);
	return (free(str_isolate), free(tmp), res);
}

char	*ft_cat_env_variable(char *new_str, char *str, int *index, char **env)
{
	new_str = ft_add_env(str, new_str, *index, env);
	if (new_str == NULL)
		return (NULL);
	*index = ft_lim_isolate(str, *index) - 1;
	return (new_str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 01:17:08 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/13 02:06:10 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_env_expand_hd(char *str, char *new_str, int index, char **env)
{
	char	*str_isolate;
	char	*tmp;
	char	*res;

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
	if (tmp == NULL)
		return (free(str_isolate), NULL);
	res = ft_strjoin(new_str, tmp);
	if (res == NULL)
		return (free(str_isolate), free(tmp), free(new_str), NULL);
	return (free(str_isolate), free(tmp), free(new_str), res);
}

char	*ft_cat_env_variable_expand_hd(char *new_str, \
		char *str, int *index, char **env)
{
	new_str = ft_add_env_expand_hd(str, new_str, *index, env);
	if (new_str == NULL)
		return (NULL);
	*index = ft_lim_isolate(str, *index) - 1;
	return (new_str);
}

char	*ft_expand_here_doc(char *str, char **env, int status)
{
	char	*new_str;
	int		index;
	int		single_quotes;
	int		double_quotes;

	if (ft_set_expand_hd(&new_str, &index, &single_quotes, &double_quotes))
		return (NULL);
	while (str[++index])
	{
		if (str[index] == '$' && str[index + 1] == '?' && single_quotes)
		{
			if (rep_status_expand_here_doc(&index, &new_str, status))
				return (NULL);
		}
		else if (str[index] == '$' && single_quotes == CLOSE)
		{
			new_str = ft_cat_env_variable_expand_hd(new_str, str, &index, env);
			if (new_str == NULL)
				return (NULL);
		}
		else if (ft_not_replace_expand_hd(str, &new_str, index, single_quotes))
			return (NULL);
		ft_change_quotes(str, &single_quotes, &double_quotes, index);
	}
	return (new_str);
}

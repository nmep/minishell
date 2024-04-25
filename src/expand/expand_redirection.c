/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 06:57:07 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/10 18:41:29 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_ambiguous_redirect(char *str, char **split, char *new)
{
	int	index;

	index = -1;
	while (split[++index])
		free(split[index]);
	free(split);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	free(str);
	free(new);
	return (NULL);
}

char	*transfo_expand(char *str, t_expand *expand, t_data_parse *data_parse)
{
	char		*new;

	new = ft_replace_env_variable(str, expand, data_parse->env, \
			data_parse->exit_status);
	if (new == NULL)
		return (NULL);
	return (new);
}

int	ft_set_replace_env_variable(char **new_str, int *index)
{
	*index = 0;
	*new_str = malloc(sizeof(char));
	if (*new_str == NULL)
		return (ERROR_MALLOC);
	*new_str[0] = '\0';
	return (SUCCESS);
}

char	*ft_replace_env_variable(char *str, t_expand *expand, \
		char **env, int status)
{
	char	*new_str;
	int		index;

	new_str = NULL;
	if (ft_set_replace_env_variable(&new_str, &index) == ERROR_MALLOC)
		return (NULL);
	while (str[index])
	{
		if (str[index] == '$' && str[index + 1] == '?' && expand->act == CHANGE)
		{
			if (rep_status(&index, &new_str, status, &expand) == ERROR_MALLOC)
				return (NULL);
		}
		else if (str[index] == '$' && expand->act == CHANGE)
		{
			new_str = ft_cat_env_variable(new_str, str, &index, env);
			if (new_str == NULL)
				return (NULL);
			expand = expand->next;
		}
		else if (ft_not_replace(str, &new_str, index, &expand) == ERROR_MALLOC)
			return (NULL);
		index++;
	}
	return (new_str);
}

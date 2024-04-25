/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_env_variable_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:11:33 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/13 00:08:00 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_not_replace(char *str, char **new_str, int index, t_expand **expand)
{
	if (str[index] == '$' && str[index + 1] == '?' && (*expand)->act == KEEP)
	{
		*new_str = ft_join_char(*new_str, str[index]);
		if (*new_str == NULL)
			return (ERROR_MALLOC);
		*expand = (*expand)->next;
	}
	else if (str[index] == '$' && (*expand)->act == KEEP)
	{
		*new_str = ft_join_char(*new_str, str[index]);
		if (new_str == NULL)
			return (ERROR_MALLOC);
		*expand = (*expand)->next;
	}
	else
	{
		*new_str = ft_join_char(*new_str, str[index]);
		if (*new_str == NULL)
			return (ERROR_MALLOC);
	}
	return (SUCCESS);
}

int	rep_status(int *index, char **new_str, int status, t_expand **expand)
{
	(*index)++;
	*new_str = ft_str_cat_long_long(*new_str, status);
	if (new_str == NULL)
		return (ERROR_MALLOC);
	*expand = (*expand)->next;
	return (SUCCESS);
}

char	**ft_add_to_2d_expand(char **base, char *add)
{
	char	**new;
	int		index;

	new = malloc((ft_strlen_2d(base) + 2) * sizeof(char *));
	if (new == NULL)
		return (free_2d(base), NULL);
	index = 0;
	while (base != NULL && base[index])
	{
		new[index] = ft_strdup(base[index]);
		if (new[index] == NULL)
			return (free_2d(base), NULL);
		index++;
	}
	new[index] = ft_strdup(add);
	if (new[index] == NULL)
		return (free_2d(base), NULL);
	new[++index] = NULL;
	if (base != NULL)
		free_2d(base);
	return (new);
}

int	ft_add_replace_status(t_data_expand *data_expand, \
		char ***res, char **new_str, t_expand **expand)
{
	if (reset_the_buffer(data_expand, res, new_str, 0) != SUCCESS)
		return (ERROR_MALLOC);
	if (rep_status(&data_expand->index, new_str, \
				data_expand->status, expand) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	if (ft_split_add_expand(*new_str, res, &data_expand->add_next) != SUCCESS)
		return (free(*new_str), free_2d(*res), ERROR_MALLOC);
	free(*new_str);
	*new_str = malloc(sizeof(char));
	if (*new_str == NULL)
		return (free_2d(*res), ERROR_MALLOC);
	(*new_str)[0] = '\0';
	return (SUCCESS);
}

int	ft_add_classique(t_data_expand *data_expand, \
		char ***res, char **new_str, char *str)
{
	if (reset_the_buffer(data_expand, res, new_str, 0) != SUCCESS)
		return (ERROR_MALLOC);
	*new_str = ft_cat_env_variable(*new_str, str, &data_expand->index, \
			data_expand->env);
	if (*new_str == NULL)
		return (ERROR_MALLOC);
	if (ft_split_add_expand(*new_str, res, &data_expand->add_next) != SUCCESS)
	{
		return (free(*new_str), free_2d(*res), ERROR_MALLOC);
	}
	free(*new_str);
	*new_str = malloc(sizeof(char));
	if (*new_str == NULL)
		return (free_2d(*res), ERROR_MALLOC);
	(*new_str)[0] = '\0';
	return (SUCCESS);
}

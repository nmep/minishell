/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_env_variable_1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 07:05:34 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/12 23:23:20 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_add(char ***res, char **new_str, \
		char **new_args, t_data_expand *data_expand)
{
	int	index;

	data_expand->add_next = -1;
	index = -1;
	*res = malloc(sizeof(char *));
	if (*res == NULL)
		return (ERROR_MALLOC);
	(*res)[0] = NULL;
	while (new_args[++index])
	{
		*res = ft_add_to_2d(*res, new_args[index]);
		if (res == NULL)
			return (free_2d(new_args), ERROR_MALLOC);
	}
	free_2d(new_args);
	*new_str = malloc(sizeof(char));
	if (*new_str == NULL)
		return (free_2d(*res), ERROR_MALLOC);
	(*new_str)[0] = '\0';
	data_expand->index = -1;
	return (SUCCESS);
}

int	reset_the_buffer(t_data_expand *data_expand, char ***res, \
		char **new_str, int len)
{
	if (*new_str[0] != '\0')
	{
		len = ft_strlen_2d(*res);
		if (len == 0 || data_expand->add_next != 1)
		{
			*res = ft_add_to_2d_expand(*res, *new_str);
			if (*res == NULL)
				return (free(*new_str), ERROR_MALLOC);
		}
		else
		{
			(*res)[len - 1] = ft_strjoin_1_malloc((*res)[len - 1], *new_str);
			if ((*res)[len - 1] == NULL)
				return (free_2d(*res), free(*new_str), ERROR_MALLOC);
		}
		free(*new_str);
		*new_str = malloc(sizeof(char));
		if (*new_str == NULL)
			return (free_2d(*res), ERROR_MALLOC);
		(*new_str)[0] = '\0';
		if (data_expand->add_next == -1)
			data_expand->add_next = 1;
	}
	return (SUCCESS);
}

char	**end_add(char *new_str, char ***res, \
		t_data_expand *data_expand, char *str)
{
	int	len;

	if (new_str[0] != '\0')
	{
		len = ft_strlen_2d(*res);
		if (len == 0 || data_expand->add_next != 1 || strcmp(new_str, str) == 0)
		{	
			*res = ft_add_to_2d_expand(*res, new_str);
			if (*res == NULL)
				return (free(new_str), NULL);
		}
		else
		{
			(*res)[len - 1] = ft_strjoin_1_malloc_expand((*res)[len - 1], \
					new_str);
			if ((*res)[len - 1] == NULL)
				return (free_2d(*res), free(new_str), NULL);
		}
	}
	return (free(new_str), *res);
}

char	**ft_add_and_replace_env_variable(char *str, t_expand *expand, \
		t_data_expand *d_e, char **new_args)
{
	if (ft_set_add(&d_e->res, &d_e->new_str, new_args, d_e) != SUCCESS)
		return (NULL);
	while (str[++d_e->index])
	{
		if (str[d_e->index] == '$' && str[d_e->index + 1] \
				== '?' && expand->act == CHANGE)
		{
			if (ft_add_replace_status(d_e, &d_e->res, \
						&d_e->new_str, &expand) != SUCCESS)
				return (free(d_e->new_str), free_tab_tab(d_e->res), NULL);
		}
		else if (str[d_e->index] == '$' && expand->act == CHANGE)
		{
			if (ft_add_classique(d_e, &d_e->res, &d_e->new_str, str) != SUCCESS)
				return (free(d_e->new_str), (NULL));
			expand = expand->next;
		}
		else
		{
			if (ft_not_replace(str, &d_e->new_str, \
						d_e->index, &expand) == ERROR_MALLOC)
				return (NULL);
		}
	}
	return (end_add(d_e->new_str, &d_e->res, d_e, str));
}

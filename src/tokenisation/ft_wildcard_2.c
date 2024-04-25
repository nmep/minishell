/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:32:22 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/10 18:06:18 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_isol_word(t_data_parse *data_parse)
{
	char	*isol;

	isol = malloc(sizeof(char));
	if (isol == NULL)
		return (NULL);
	isol[0] = '\0';
	while (data_parse->input[data_parse->index] != ' '
		&& data_parse->input[data_parse->index] != '\0')
	{
		isol = ft_join_char(isol, data_parse->input[data_parse->index]);
		if (isol == NULL)
			return (NULL);
		data_parse->index++;
	}
	return (isol);
}

int	ft_condition_wildcard_2(int *found, char **wildcard, t_wildcard *ls)
{
	*wildcard = ft_strjoin_1_malloc(*wildcard, ls->str);
	if (*wildcard == NULL)
		return (ERROR_MALLOC);
	*wildcard = ft_join_char(*wildcard, ' ');
	if (*wildcard == NULL)
		return (ERROR_MALLOC);
	*found = 1;
	return (SUCCESS);
}

int	ft_all_wildcard(t_wildcard *ls, char **wildcard)
{
	while (ls != NULL)
	{
		if (ls->str[0] != '.')
		{
			*wildcard = ft_strjoin_1_malloc(*wildcard, ls->str);
			if (*wildcard == NULL)
				return (ERROR_MALLOC);
			*wildcard = ft_join_char(*wildcard, ' ');
			if (*wildcard == NULL)
				return (ERROR_MALLOC);
		}
		if (ls->next == NULL)
			break ;
		ls = ls->next;
	}
	return (SUCCESS);
}

int	ft_set_maybe_a_wildcard(char **isol, char ***split, t_wildcard *ls,
		t_data_parse *data_parse)
{
	*isol = ft_isol_word(data_parse);
	if (*isol == NULL)
		return (ft_free_wildcard(&ls), ERROR_MALLOC);
	data_parse->wildcard = malloc(sizeof(char));
	if (data_parse->wildcard == NULL)
		return (ft_free_wildcard(&ls), free(*isol), ERROR_MALLOC);
	data_parse->wildcard[0] = '\0';
	if (ft_occ(*isol, '*') == 0)
	{
		free(data_parse->wildcard);
		data_parse->wildcard = *isol;
		return (ft_free_wildcard(&ls), SUCCESS);
	}
	if (*isol[0] == '*' && ft_strlen(*isol) == 1)
	{
		if (ft_all_wildcard(ls, &data_parse->wildcard) != SUCCESS)
			return (ft_free_wildcard(&ls), free(*isol), ERROR_MALLOC);
		return (free(*isol), ft_free_wildcard(&ls), SUCCESS);
	}
	*split = ft_split(*isol, '*');
	if (*split == NULL)
		return (free(*isol), free(data_parse->wildcard), ft_free_wildcard(&ls),
			ERROR_MALLOC);
	return (SUCCESS_SQUARE);
}

int	ft_end_maybe_wildcard(int found, t_data_parse *data_parse, char *isol,
		char **split)
{
	free_2d(split);
	if (found == 0)
	{
		free(data_parse->wildcard);
		data_parse->wildcard = isol;
	}
	else
	{
		free(isol);
	}
	return (SUCCESS);
}

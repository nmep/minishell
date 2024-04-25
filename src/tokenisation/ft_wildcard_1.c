/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:43:13 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/12 03:11:38 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	condition_maybe_wildcard(char **isol, char ***split, t_wildcard *ls, \
		t_data_parse *data_parse)
{
	if (ft_check_before(*isol, *split, ls->str) && ft_check_after(*isol, \
				*split, ls->str) && ft_check_all(*split, \
					ls->str) && ls->str[0] != '.')
	{
		if (ft_condition_wildcard_2(&data_parse->found, &data_parse->wildcard,
				ls) == ERROR_MALLOC)
			return (ft_free_wildcard(&ls), free(*isol), free_2d(*split),
				ERROR_MALLOC);
	}
	return (SUCCESS);
}

int	ft_maybe_a_wildcard(t_data_parse *data_parse)
{
	char		*isol;
	char		**split;
	t_wildcard	*ls;

	ls = NULL;
	data_parse->found = 0;
	if (set_ls(&ls) != SUCCESS)
		return (ERROR_MALLOC);
	data_parse->tmp_wildcard = ft_set_maybe_a_wildcard(&isol, &split, ls,
			data_parse);
	if (data_parse->tmp_wildcard != SUCCESS_SQUARE)
		return (data_parse->tmp_wildcard);
	while (ls != NULL)
	{
		if (condition_maybe_wildcard(&isol, &split, ls, data_parse) != SUCCESS)
			return (ERROR_MALLOC);
		if (ls->next == NULL)
			break ;
		ls = ls->next;
	}
	return (ft_free_wildcard(&ls), ft_end_maybe_wildcard(data_parse->found, \
				data_parse, isol, split));
}

int	ft_set_wildcard(t_data_parse *data_parse)
{
	data_parse->single_quote_open = CLOSE;
	data_parse->double_quote_open = CLOSE;
	data_parse->str = malloc(sizeof(char));
	if (data_parse->str == NULL)
		return (ERROR_MALLOC);
	data_parse->str[0] = '\0';
	data_parse->index = 0;
	return (SUCCESS);
}

char	*ft_wildcard(t_data_parse *data_parse)
{
	if (ft_set_wildcard(data_parse) != SUCCESS)
		return (NULL);
	while (data_parse->input[data_parse->index])
	{
		ft_change_status_quotes(data_parse);
		if (data_parse->single_quote_open == CLOSE
			&& data_parse->double_quote_open == CLOSE)
		{
			if (ft_maybe_a_wildcard(data_parse) == ERROR_MALLOC)
				return (NULL);
			data_parse->str = ft_strjoin_1_malloc(data_parse->str,
					data_parse->wildcard);
			if (data_parse->str == NULL)
				return (free(data_parse->wildcard), NULL);
			free(data_parse->wildcard);
		}
		if (data_parse->input[data_parse->index])
		{
			data_parse->str = ft_join_char(data_parse->str, \
					data_parse->input[data_parse->index++]);
			if (data_parse->str == NULL)
				return (NULL);
		}
	}
	return (free(data_parse->input), data_parse->str);
}

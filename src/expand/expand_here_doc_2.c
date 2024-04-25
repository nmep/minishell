/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:54:38 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/13 02:06:11 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_expand_hd(char **new_str, int *index, \
		int *single_quotes, int *double_quotes)
{
	*index = -1;
	*new_str = malloc(sizeof(char));
	if (*new_str == NULL)
		return (ERROR_MALLOC);
	*new_str[0] = '\0';
	*single_quotes = CLOSE;
	*double_quotes = CLOSE;
	return (SUCCESS);
}

int	ft_is_an_end(char *str, int index)
{
	while (str[++index])
	{
		if (str[index] == '\'')
			return (1);
	}
	return (0);
}

void	ft_change_quotes(char *str, int *single_quotes, \
		int *double_quotes, int index)
{
	if (str[index] == '\'' && *single_quotes == OPEN && \
			*double_quotes == CLOSE)
		*single_quotes = CLOSE;
	else if (str[index] == '"' && *single_quotes == CLOSE && \
			*double_quotes == OPEN)
		*double_quotes = CLOSE;
	else if (str[index] == '\'' && *single_quotes == CLOSE && \
			*double_quotes == CLOSE && ft_is_an_end(str, index))
		*single_quotes = OPEN;
	else if (str[index] == '"' && *single_quotes == CLOSE && \
			*double_quotes == CLOSE)
		*double_quotes = OPEN;
}

int	rep_status_expand_here_doc(int *index, char **new_str, int status)
{
	(*index)++;
	*new_str = ft_str_cat_long_long(*new_str, status);
	if (new_str == NULL)
		return (ERROR_MALLOC);
	return (SUCCESS);
}

int	ft_not_replace_expand_hd(char *str, char **new_str, \
		int index, int single_quotes)
{
	if (str[index] == '$' && str[index + 1] == '?' && single_quotes == OPEN)
	{
		*new_str = ft_join_char(*new_str, str[index]);
		if (*new_str == NULL)
			return (ERROR_MALLOC);
	}
	else if (str[index] == '$' && single_quotes == OPEN)
	{
		*new_str = ft_join_char(*new_str, str[index]);
		if (new_str == NULL)
			return (ERROR_MALLOC);
	}
	else
	{
		*new_str = ft_join_char(*new_str, str[index]);
		if (*new_str == NULL)
			return (ERROR_MALLOC);
	}
	return (SUCCESS);
}

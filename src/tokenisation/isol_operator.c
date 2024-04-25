/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isol_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:29:01 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/08 20:53:10 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_add_in_opperator(t_data_parse *data_parse)
{
	data_parse->condition_1[0] = '<';
	data_parse->condition_1[1] = '>';
	data_parse->condition_1[2] = '&';
	data_parse->condition_1[3] = '|';
	data_parse->res_1[0] = ft_get_str(" << ");
	data_parse->res_1[1] = ft_get_str(" >> ");
	data_parse->res_1[2] = ft_get_str(" && ");
	data_parse->res_1[3] = ft_get_str(" || ");
	data_parse->condition_2[0] = '<';
	data_parse->condition_2[1] = '>';
	data_parse->condition_2[2] = '(';
	data_parse->condition_2[3] = ')';
	data_parse->condition_2[4] = '|';
	data_parse->res_2[0] = ft_get_str(" < ");
	data_parse->res_2[1] = ft_get_str(" > ");
	data_parse->res_2[2] = ft_get_str(" ( ");
	data_parse->res_2[3] = ft_get_str(" ) ");
	data_parse->res_2[4] = ft_get_str(" | ");
}

int	ft_add_in_opperator_suite(t_data_parse *data_parse)
{
	int	index;

	index = -1;
	while (++index < 5)
	{
		if (data_parse->input[data_parse->index] == \
				data_parse->condition_2[index])
		{
			data_parse->str = ft_strjoin_1_malloc(data_parse->str, \
					data_parse->res_2[index]);
			if (data_parse->str == NULL)
				return (ERROR_MALLOC);
			data_parse->index++;
			return (SUCCESS);
		}
	}
	data_parse->str = ft_join_char(data_parse->str, \
			data_parse->input[data_parse->index]);
	if (data_parse->str == NULL)
		return (ERROR_MALLOC);
	data_parse->index++;
	return (SUCCESS);
}

int	ft_add_in_opperator(t_data_parse *data_parse)
{
	int	index;

	ft_set_add_in_opperator(data_parse);
	index = -1;
	while (++index < 4)
	{
		if (data_parse->input[data_parse->index] == \
				data_parse->condition_1[index] && \
				data_parse->input[data_parse->index + 1] == \
				data_parse->condition_1[index])
		{
			data_parse->str = ft_strjoin_1_malloc(data_parse->str, \
					data_parse->res_1[index]);
			if (data_parse->str == NULL)
				return (ERROR_MALLOC);
			data_parse->index += 2;
			return (SUCCESS);
		}
	}
	return (ft_add_in_opperator_suite(data_parse));
}

void	ft_change_status_quotes(t_data_parse *data_parse)
{
	if (data_parse->input[data_parse->index] == '\'' \
			&& data_parse->single_quote_open == OPEN)
		data_parse->single_quote_open = CLOSE;
	else if (data_parse->input[data_parse->index] == '"' \
			&& data_parse->double_quote_open == OPEN)
		data_parse->double_quote_open = CLOSE;
	else if (data_parse->input[data_parse->index] == '\'' \
			&& data_parse->single_quote_open == CLOSE \
			&& data_parse->double_quote_open == CLOSE)
		data_parse->single_quote_open = OPEN;
	else if (data_parse->input[data_parse->index] == '"' \
			&& data_parse->single_quote_open == CLOSE \
			&& data_parse->double_quote_open == CLOSE)
		data_parse->double_quote_open = OPEN;
}

char	*ft_isol_operator(t_data_parse *data_parse)
{
	data_parse->single_quote_open = CLOSE;
	data_parse->double_quote_open = CLOSE;
	data_parse->str = malloc (sizeof(char));
	if (data_parse->str == NULL)
		return (NULL);
	data_parse->str[0] = '\0';
	data_parse->index = 0;
	while (data_parse->input[data_parse->index])
	{
		ft_change_status_quotes(data_parse);
		if (data_parse->single_quote_open == CLOSE \
				&& data_parse->double_quote_open == CLOSE)
		{
			if (ft_add_in_opperator(data_parse) == ERROR_MALLOC)
				return (NULL);
		}
		else
		{
			data_parse->str = ft_join_char(data_parse->str, \
					data_parse->input[data_parse->index++]);
			if (data_parse->str == NULL)
				return (NULL);
		}
	}
	return (free(data_parse->input), data_parse->str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:37:36 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/13 01:02:01 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_make_token(t_data_parse *data_parse)
{
	data_parse->str = malloc(sizeof(char));
	if (data_parse->str == NULL)
		return (ERROR_MALLOC);
	data_parse->str[0] = '\0';
	data_parse->single_quote_open = CLOSE;
	data_parse->double_quote_open = CLOSE;
	while (data_parse->input[data_parse->index] \
			&& (data_parse->input[data_parse->index] == ' '))
		data_parse->index++;
	return (SUCCESS);
}

int	ft_gestion_quotes_close(t_data_parse *data_parse, \
		t_expand *expand, t_token **token)
{
	if (data_parse->input[data_parse->index] == '\'' \
			&& data_parse->single_quote_open == OPEN)
	{
		if ((data_parse->input[data_parse->index + 1] == ' ' \
					|| data_parse->input[data_parse->index + 1] == '\0') \
				&& data_parse->str[0] != '\0')
			return (ft_add_and_return(data_parse, token, expand));
		data_parse->single_quote_open = CLOSE;
	}
	else if (data_parse->input[data_parse->index] == '"' \
			&& data_parse->double_quote_open == OPEN)
	{
		if ((data_parse->input[data_parse->index + 1] == ' ' \
					|| data_parse->input[data_parse->index + 1] == '\0') \
				&& data_parse->str[0] != '\0')
			return (ft_add_and_return(data_parse, token, expand));
		data_parse->double_quote_open = CLOSE;
	}
	return (SUCCESS);
}

int	ft_gestion_quotes(t_data_parse *data_parse, \
t_expand *expand, t_token **token)
{
	if ((data_parse->input[data_parse->index] == '\'' \
				&& data_parse->single_quote_open == OPEN) \
			|| (data_parse->input[data_parse->index] == '"' \
				&& data_parse->double_quote_open == OPEN))
		return (ft_gestion_quotes_close(data_parse, expand, token));
	else if (data_parse->input[data_parse->index] == '\'' \
			&& data_parse->single_quote_open == CLOSE \
			&& data_parse->double_quote_open == CLOSE)
		data_parse->single_quote_open = OPEN;
	else if (data_parse->input[data_parse->index] == '"' \
			&& data_parse->single_quote_open == CLOSE \
			&& data_parse->double_quote_open == CLOSE)
		data_parse->double_quote_open = OPEN;
	else
	{
		data_parse->str = ft_join_char(data_parse->str, \
				data_parse->input[data_parse->index]);
		if (data_parse->str == NULL)
			return (ERROR_MALLOC);
	}
	return (SUCCESS);
}

int	ft_maybe_empty(t_data_parse *data_parse)
{
	if (data_parse->input[data_parse->index] == '\0')
	{
		free(data_parse->str);
		data_parse->str = NULL;
		return (SUCCESS_SQUARE);
	}
	return (SUCCESS);
}

int	ft_make_token(t_data_parse *data_parse, t_token **token)
{
	t_expand	*expand;

	expand = NULL;
	if (ft_set_make_token(data_parse) != SUCCESS)
		return (ERROR_MALLOC);
	if (ft_maybe_empty(data_parse) == SUCCESS_SQUARE)
		return (SUCCESS);
	while (data_parse->input[data_parse->index] \
			&& (data_parse->input[data_parse->index] != ' ' \
				|| data_parse->single_quote_open == OPEN \
				|| data_parse->double_quote_open == OPEN))
	{
		if (data_parse->input[data_parse->index] == '$')
		{
			if (ft_make_lst_expand(&expand, data_parse) == ERROR_MALLOC)
				return (ERROR_MALLOC);
		}
		data_parse->tmp = ft_gestion_quotes(data_parse, expand, token);
		if (data_parse->tmp == SUCCESS_SQUARE)
			return (SUCCESS);
		if (data_parse->tmp == ERROR_MALLOC)
			return (ERROR_MALLOC);
		data_parse->index++;
	}
	return (ft_add_token(token, data_parse, expand));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenisation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 05:06:05 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/12 07:52:40 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
on parcourt tout l'input et on fait des tokens avec
*/
int	ft_tokenisation(t_token **token, t_data_parse *data_parse)
{
	if (ft_is_quote_close(data_parse->input, CLOSE, CLOSE) == OPEN)
		return (free(data_parse->input), WRONG_INPUT);
	data_parse->input = ft_isol_operator(data_parse);
	if (data_parse->input == NULL)
		return (ERROR_MALLOC);
	data_parse->input = ft_wildcard(data_parse);
	if (data_parse->input == NULL)
		return (ERROR_MALLOC);
	data_parse->index = 0;
	while (data_parse->input[data_parse->index])
	{
		if (ft_make_token(data_parse, token) != SUCCESS)
			return (free(data_parse->str), free(data_parse->input), ERROR);
		if (data_parse->str)
			free(data_parse->str);
	}
	free(data_parse->input);
	if (*token == NULL)
		return (WRONG_INPUT);
	ft_set_all_grammaire(token);
	return (GOOD_INPUT);
}

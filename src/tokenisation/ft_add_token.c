/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:49:27 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/13 00:55:56 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_add_token(t_data_parse *data_parse)
{
	data_parse->opp[0] = ft_get_str("<<");
	data_parse->opp[1] = ft_get_str(">>");
	data_parse->opp[2] = ft_get_str("<");
	data_parse->opp[3] = ft_get_str(">");
	data_parse->opp[4] = ft_get_str("&&");
	data_parse->opp[5] = ft_get_str("||");
	data_parse->opp[6] = ft_get_str("|");
	data_parse->opp[7] = ft_get_str("(");
	data_parse->opp[8] = ft_get_str(")");
	data_parse->type[0] = HEREDOC;
	data_parse->type[1] = APPEND;
	data_parse->type[2] = INFILE;
	data_parse->type[3] = OUTFILE;
	data_parse->type[4] = AND;
	data_parse->type[5] = OR;
	data_parse->type[6] = PIPE;
	data_parse->type[7] = OPEN_PARENTHESIS;
	data_parse->type[8] = CLOSE_PARENTHESIS;
}

int	ft_add_token_end(t_data_parse *data_parse)
{
	if (data_parse->str && data_parse->str[0] == '\0')
	{
		free(data_parse->str);
		data_parse->str = NULL;
	}
	return (SUCCESS);
}

/*
on ajoute le token avec le bon type
*/
int	ft_add_token(t_token **token, t_data_parse *data_parse, t_expand *expand)
{
	int	index;

	ft_set_add_token(data_parse);
	index = -1;
	while (++index < 9)
	{
		if (ft_strcmp(data_parse->str, data_parse->opp[index]) == 0 \
				&& data_parse->single_quote_open == CLOSE && \
				data_parse->double_quote_open == CLOSE)
		{
			if (ft_lst_add_back(token, ft_lstnew(data_parse->str, WORD, \
							data_parse->type[index], expand)) \
					== ERROR_MALLOC)
				return (ERROR_MALLOC);
			return (SUCCESS);
		}
	}
	if (data_parse->str[0] != '\0')
	{
		if (ft_lst_add_back(token, ft_lstnew(data_parse->str, WORD, \
						TEXT, expand)) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	return (ft_add_token_end(data_parse));
}

int	ft_add_and_return(t_data_parse *data_parse, \
		t_token **token, t_expand *expand)
{
	if (ft_lst_add_back(token, ft_lstnew(data_parse->str, WORD, TEXT, \
					expand)) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	data_parse->double_quote_open = CLOSE;
	data_parse->index++;
	return (SUCCESS_SQUARE);
}

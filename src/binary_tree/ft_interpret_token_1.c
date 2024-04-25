/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpret_token_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:08:56 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/04 17:56:21 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_token_type_1(t_token *token)
{
	if (token->type == OPEN_PARENTHESIS || token->type == CLOSE_PARENTHESIS \
	|| token->type == OR || token->type == AND)
		return (SUCCESS);
	return (ERROR);
}

int	ft_is_token_type_2(t_token *token)
{
	if (token->type == INFILE || token->type == OUTFILE \
	|| token->type == APPEND)
		return (SUCCESS);
	return (ERROR);
}

int	ft_interpret_token_suite(t_data_parse *data_parse, \
		t_lst_exec **lst_exec, t_token **token)
{
	if ((*token)->type == PIPE)
	{
		if (ft_exec_token_type_pipe(data_parse, lst_exec) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else
	{
		data_parse->args_tmp = ft_join_2d(data_parse->args_tmp, (*token)->str);
		if (data_parse->args_tmp == NULL)
			return (ft_free_pipes(data_parse->fd_pipes, data_parse->nb_pipes), \
			ft_print_error_malloc(), ERROR_MALLOC);
		if (ft_complete_expand(&data_parse->expand, (*token)->expand, \
					ft_strlen_2d(data_parse->args_tmp)) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	return (SUCCESS);
}

int	ft_interpret_token(t_data_parse *data_parse, \
		t_lst_exec **lst_exec, t_token **token)
{
	if (ft_is_token_type_1(*token) == SUCCESS)
	{
		if (ft_exec_token_type_1(data_parse, lst_exec, *token) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (ft_is_token_type_2(*token) == SUCCESS)
	{
		if (ft_exec_token_type_2(data_parse, *token) != SUCCESS)
			return (ERROR);
		*token = (*token)->next;
	}
	else if ((*token)->type == HEREDOC)
	{
		if (ft_exec_token_type_heredoc(data_parse, token) != SUCCESS)
			return (ERROR);
	}
	else
	{
		if (ft_interpret_token_suite(data_parse, \
					lst_exec, token) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	return (SUCCESS);
}

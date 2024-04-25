/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpret_token_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:00:46 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/11 16:15:52 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_token_type_1(t_data_parse *data_parse, \
		t_lst_exec **lst_exec, t_token *token)
{
	if (token->type == OPEN_PARENTHESIS)
	{
		if (ft_one_more_exec(data_parse, lst_exec) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (token->type == CLOSE_PARENTHESIS)
	{
		if (ft_one_more_exec(data_parse, lst_exec) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (token->type == OR)
	{
		if (ft_one_more_exec(data_parse, lst_exec) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (token->type == AND)
	{
		if (ft_one_more_exec(data_parse, lst_exec) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	return (SUCCESS);
}

int	ft_exec_token_type_infile(t_data_parse *data_parse, t_token *token)
{
	char	*str_tmp;
	int		fd_tmp;

	fd_tmp = 0;
	if (data_parse->fd_in == -1 || data_parse->fd_in == -2)
		fd_tmp = data_parse->fd_in;
	else if (data_parse->fd_in > 2)
		close(data_parse->fd_in);
	token = token->next;
	str_tmp = transfo_expand(token->str, token->expand, data_parse);
	if (str_tmp == NULL)
		return (free_mini_expand(token->expand), ERROR);
	free_mini_expand(token->expand);
	if (access(str_tmp, R_OK) != 0)
		data_parse->fd_in = -2;
	else
		data_parse->fd_in = open(str_tmp, O_RDONLY);
	free(str_tmp);
	if (fd_tmp == -1 || fd_tmp == -2)
	{
		if (data_parse->fd_in > 2)
			close(data_parse->fd_in);
		data_parse->fd_in = fd_tmp;
	}
	return (SUCCESS);
}

int	ft_exec_token_type_outfile(t_data_parse *data_parse, t_token *token)
{
	char	*str_tmp;
	int		fd_tmp;

	fd_tmp = 0;
	if (data_parse->fd_out == -1 || data_parse->fd_out == -2)
		fd_tmp = data_parse->fd_out;
	if (data_parse->fd_out > 2)
		close(data_parse->fd_out);
	token = token->next;
	str_tmp = transfo_expand(token->str, token->expand, data_parse);
	if (str_tmp == NULL)
		return (free_mini_expand(token->expand), ERROR);
	free_mini_expand(token->expand);
	data_parse->fd_out = open(str_tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(str_tmp);
	if (fd_tmp == -1 || fd_tmp == -2)
	{
		if (data_parse->fd_out > 2)
			close(data_parse->fd_out);
		data_parse->fd_out = fd_tmp;
	}
	return (SUCCESS);
}

int	ft_exec_token_type_append(t_data_parse *data_parse, t_token *token)
{
	char	*str_tmp;
	int		fd_tmp;

	fd_tmp = 0;
	if (data_parse->fd_out == -1 || data_parse->fd_out == -2)
		fd_tmp = data_parse->fd_out;
	if (data_parse->fd_out > 2)
		close(data_parse->fd_out);
	token = token->next;
	str_tmp = transfo_expand(token->str, token->expand, data_parse);
	if (str_tmp == NULL)
		return (free_mini_expand(token->expand), ERROR);
	free_mini_expand(token->expand);
	data_parse->fd_out = open(str_tmp, O_CREAT | O_WRONLY | O_APPEND, 0644);
	free(str_tmp);
	if (fd_tmp == -1 || fd_tmp == -2)
	{
		if (data_parse->fd_out > 2)
			close(data_parse->fd_out);
		data_parse->fd_out = fd_tmp;
	}
	return (SUCCESS);
}

int	ft_exec_token_type_2(t_data_parse *data_parse, t_token *token)
{
	if (token->type == INFILE)
		return (ft_exec_token_type_infile(data_parse, token));
	else if (token->type == OUTFILE)
		return (ft_exec_token_type_outfile(data_parse, token));
	else if (token->type == APPEND)
		return (ft_exec_token_type_append(data_parse, token));
	return (SUCCESS);
}

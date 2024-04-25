/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_lst_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:06:51 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/10 20:09:52 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_nb_lst_exec(t_token *token)
{
	int	count;

	count = 1;
	while (token != NULL)
	{
		if (token->type == AND || token->type == OR)
			count++;
		token = token->next;
	}
	return (count);
}

int	ft_one_more_exec(t_data_parse *data_parse, t_lst_exec **lst_exec)
{
	if (ft_lst_exec_add_back(lst_exec, \
	ft_new_lst_exec(data_parse->args_tmp, \
	data_parse->fd_in, data_parse->fd_out, \
	data_parse->expand)) == ERROR_MALLOC)
		return (ft_free_pipes(data_parse->fd_pipes, data_parse->nb_pipes), \
		free_2d(data_parse->args_tmp), ft_print_error_malloc(), \
		ERROR_MALLOC);
	free_2d(data_parse->args_tmp);
	data_parse->expand = NULL;
	data_parse->args_tmp = NULL;
	data_parse->fd_in = 0;
	data_parse->fd_out = 1;
	return (SUCCESS);
}

int	ft_set_exec(t_data_parse *data_parse, t_lst_exec **lst_exec, t_token *token)
{
	data_parse->nb_pipes = ft_nb_pipes(token);
	data_parse->fd_pipes = malloc (data_parse->nb_pipes * sizeof(int *));
	if (data_parse->fd_pipes == NULL)
		return (ft_print_error_malloc(), ERROR_MALLOC);
	data_parse->index_pipes = -1;
	while (++data_parse->index_pipes < data_parse->nb_pipes)
	{
		data_parse->fd_pipes[data_parse->index_pipes] = malloc(2 * sizeof(int));
		if (data_parse->fd_pipes[data_parse->index_pipes] == NULL)
			return (ft_pipes_fail(data_parse->fd_pipes, \
			data_parse->index_pipes), \
			ft_print_error_malloc(), ERROR_MALLOC);
		if (pipe(data_parse->fd_pipes[data_parse->index_pipes]) == -1)
			return (free(data_parse->fd_pipes[data_parse->index_pipes]), \
			ft_pipes_fail(data_parse->fd_pipes, data_parse->index_pipes), \
			ft_putstr_fd("minishell: pipes failed\n", 2), ERROR_PIPE);
	}
	data_parse->index_pipes = 0;
	data_parse->fd_in = 0;
	data_parse->fd_out = 1;
	data_parse->args_tmp = NULL;
	data_parse->expand = NULL;
	*lst_exec = NULL;
	return (SUCCESS);
}

int	ft_lst_exec(t_token *token, t_lst_exec **lst_exec, t_data_parse *data_parse)
{
	if (ft_set_exec(data_parse, lst_exec, token) != SUCCESS)
		return (ERROR);
	while (token != NULL)
	{
		if (ft_interpret_token(data_parse, lst_exec, &token) != SUCCESS)
		{
			while (++data_parse->index_pipes < data_parse->nb_pipes)
				free(data_parse->fd_pipes[data_parse->index_pipes]);
			free(data_parse->fd_pipes);
			return (ERROR);
		}
		if (token->next == NULL)
			break ;
		token = token->next;
	}
	if (ft_one_more_exec(data_parse, lst_exec) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	data_parse->index_pipes = -1;
	while (++data_parse->index_pipes < data_parse->nb_pipes)
		free(data_parse->fd_pipes[data_parse->index_pipes]);
	free(data_parse->fd_pipes);
	return (SUCCESS);
}

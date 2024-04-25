/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:04:20 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/04 13:16:12 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipes_fail(int **fd_pipes, int index_pipes)
{
	index_pipes--;
	while (index_pipes >= 0)
	{
		close(fd_pipes[index_pipes][0]);
		close(fd_pipes[index_pipes][1]);
		free(fd_pipes[index_pipes]);
		index_pipes--;
	}
	free(fd_pipes);
}

int	ft_nb_pipes(t_token *token)
{
	int	count;

	count = 0;
	while (token != NULL)
	{
		if (token->type == PIPE)
			count++;
	token = token->next;
	}
	return (count);
}

int	ft_exec_token_type_pipe(t_data_parse *data_parse, t_lst_exec **lst_exec)
{
	if (data_parse->fd_out != 1)
		close(data_parse->fd_pipes[data_parse->index_pipes][1]);
	else
		data_parse->fd_out = data_parse->fd_pipes[data_parse->index_pipes][1];
	if (ft_lst_exec_add_back(lst_exec, ft_new_lst_exec(data_parse->args_tmp, \
					data_parse->fd_in, data_parse->fd_out, \
					data_parse->expand)) == ERROR_MALLOC)
		return (ft_free_pipes(data_parse->fd_pipes, data_parse->nb_pipes), \
				free_2d(data_parse->args_tmp), \
				ft_print_error_malloc(), ERROR_MALLOC);
	free_2d(data_parse->args_tmp);
	data_parse->args_tmp = NULL;
	data_parse->expand = NULL;
	data_parse->fd_in = data_parse->fd_pipes[data_parse->index_pipes++][0];
	data_parse->fd_out = 1;
	return (SUCCESS);
}

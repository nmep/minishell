/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 02:23:35 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/22 19:12:03 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_token_type_heredoc(t_data_parse *data_parse, t_token **token)
{
	int	fd_tmp;

	fd_tmp = 0;
	if (data_parse->fd_in == -1 || data_parse->fd_in == -2)
		fd_tmp = data_parse->fd_in;
	else if (data_parse->fd_in > 2)
		close(data_parse->fd_in);
	*token = (*token)->next;
	data_parse->fd_in = \
		data_parse->array_hd[data_parse->index_here_doc--];
	if (fd_tmp == -1 || fd_tmp == -2)
	{
		if (data_parse->fd_in > 2)
			close(data_parse->fd_in);
		data_parse->fd_in = fd_tmp;
	}
	return (SUCCESS);
}

int	ft_nb_here_doc(t_token *token)
{
	int	count;

	count = 0;
	while (token != NULL)
	{
		if (token->type == HEREDOC)
			count++;
		token = token->next;
	}
	return (count);
}

int	ft_complete_here_doc(t_data_parse *d_p, t_token *token,
	int index, int *exit_status)
{
	d_p->array_hd = malloc (ft_nb_here_doc(token) * sizeof(int));
	if (d_p->array_hd == NULL)
		return (ERROR_MALLOC);
	while (token != NULL)
	{
		if (token->type == HEREDOC)
		{
			token = token->next;
			d_p->heredoc = ft_here_doc();
			if (d_p->heredoc == NULL)
				return (free(d_p->array_hd), ERROR);
			d_p->array_hd[index] = open(d_p->heredoc, \
					O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (ft_complete(d_p->array_hd[index], \
						token, d_p, exit_status) == ERROR)
				return (close_hd(d_p->array_hd, index), free(d_p->array_hd), \
				free(d_p->heredoc), ERROR);
			close(d_p->array_hd[index]);
			d_p->array_hd[index++] = open(d_p->heredoc, O_RDWR, 0644);
			unlink(d_p->heredoc);
			free(d_p->heredoc);
		}
		token = token->next;
	}
	return (SUCCESS);
}

int	ft_complete(int fd_in, t_token *token,
	t_data_parse *data_parse, int *exit_status)
{
	char	*line;
	char	*tmp;

	if (fd_in == -1)
		return (SUCCESS);
	ft_putstr_fd("> ", 1);
	line = new_readline(token->str, exit_status);
	if (line == NULL)
		return (ERROR);
	if (ft_strncmp(line, token->str, ft_strlen(token->str)) == 1 \
			|| ft_strlen(token->str) != ft_strlen(line) - 1)
	{
		tmp = ft_expand_here_doc(line, data_parse->env, \
				data_parse->exit_status);
		if (tmp == NULL)
			return (ERROR);
		ft_putstr_fd(tmp, fd_in);
		free(tmp);
		free(line);
		if (ft_complete(fd_in, token, data_parse, exit_status) == ERROR)
			return (ERROR);
	}
	else
		free(line);
	return (SUCCESS);
}

char	*ft_here_doc(void)
{
	char	*here_doc;
	char	*str;
	char	*str_index;
	int		index;

	str = ft_get_str("/tmp/.here_doc");
	index = 1;
	while (index <= 99999)
	{
		str_index = ft_itoa(index);
		if (str_index == NULL)
			return (ft_print_error_malloc(), NULL);
		here_doc = ft_strjoin(str, str_index);
		if (here_doc == NULL)
			return (free(str_index), ft_print_error_malloc(), NULL);
		free(str_index);
		if (access(here_doc, 0) != 0)
			return (here_doc);
		else
			free(here_doc);
		index++;
	}
	ft_putstr_fd("minishell: heredoc failed\n", 2);
	return (NULL);
}

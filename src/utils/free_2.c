/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 22:48:14 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/13 01:52:57 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mini_expand(t_expand *expand)
{
	t_expand	*tmp;

	while (expand != NULL)
	{
		tmp = expand;
		expand = expand->next;
		free(tmp);
	}
}

void	free_tab_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	ft_free_wildcard(t_wildcard **ls)
{
	t_wildcard	*tmp;

	while (*ls && (*ls)->prev != NULL)
		*ls = (*ls)->prev;
	while (*ls != NULL)
	{
		tmp = *ls;
		*ls = (*ls)->next;
		free(tmp->str);
		free(tmp);
	}
}

void	ft_free_pipes(int **fd_pipes, int nb_pipes)
{
	while (--nb_pipes >= 0)
	{
		free(fd_pipes[nb_pipes]);
	}
	free(fd_pipes);
}

void	close_hd(int *array, int index)
{
	while (index >= 0)
	{
		close(array[index]);
		index--;
	}
}

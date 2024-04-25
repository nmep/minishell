/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_close_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:55:03 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/10 20:58:16 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_expand(t_expand **expand, int len)
{
	t_expand	*tmp;
	int			index;

	index = 0;
	while (index < len)
	{
		while (expand && expand[index] != NULL)
		{
			tmp = expand[index];
			expand[index] = expand[index]->next;
			if (tmp != NULL)
				free(tmp);
		}
		index++;
	}
	if (expand != NULL)
		free(expand);
}

void	free_close_exec_list(t_lst_exec *exec)
{
	t_lst_exec	*tmp;

	while (exec->prev != NULL)
		exec = exec->prev;
	while (exec != NULL)
	{
		tmp = exec;
		free_expand(exec->expand, ft_strlen_2d(exec->args));
		free_2d(exec->args);
		if (exec->fd_in > 2)
			close(exec->fd_in);
		if (exec->fd_out > 2)
			close(exec->fd_out);
		exec = exec->next;
		free(tmp);
	}
}

void	free_close_tree(t_tree *tree)
{
	if (tree->left_child != NULL)
		free_close_tree(tree->left_child);
	if (tree->right_child != NULL)
		free_close_tree(tree->right_child);
	if (tree->lst_exec != NULL)
		free_close_exec_list(tree->lst_exec);
	free(tree);
	return ;
}

void	free_and_close_tree(t_tree *tree)
{
	if (tree == NULL)
		return ;
	while (tree->parent != NULL)
		tree = tree->parent;
	free_close_tree(tree);
}

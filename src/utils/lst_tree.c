/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:51:46 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/05 11:53:12 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_left_child(t_tree **tree, t_tree *new)
{
	if (new == NULL)
		return (ERROR_MALLOC);
	else if (*tree == NULL)
	{
		*tree = new;
		return (SUCCESS);
	}
	new->parent = *tree;
	(*tree)->left_child = new;
	return (SUCCESS);
}

int	ft_add_right_child(t_tree **tree, t_tree *new)
{
	if (new == NULL)
		return (ERROR_MALLOC);
	else if (*tree == NULL)
	{
		*tree = new;
		return (SUCCESS);
	}
	new->parent = *tree;
	(*tree)->right_child = new;
	return (SUCCESS);
}

t_tree	*ft_tree_new(int type)
{
	t_tree	*new;

	new = malloc (sizeof(t_tree));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->parent = NULL;
	new->left_child = NULL;
	new->right_child = NULL;
	new->lst_exec = NULL;
	return (new);
}

t_tree	*ft_first_empty_child(t_tree *tree)
{
	t_tree	*res;

	if (tree == NULL)
		return (NULL);
	if (tree->type == EXEC_LIST)
		return (NULL);
	if (tree->right_child != NULL)
	{
		res = ft_first_empty_child(tree->right_child);
		if (res != NULL)
			return (res);
	}
	if (tree->left_child != NULL)
	{
		res = ft_first_empty_child(tree->left_child);
		if (res != NULL)
			return (res);
	}
	if ((tree->left_child == NULL || tree->right_child == NULL) \
			&& tree->type != EXEC_LIST)
		return (tree);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tree_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 04:18:52 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/10 20:06:45 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_tree_null(t_tree **tree, t_tree *new, \
		t_token *token, t_data_parse *data_parse)
{
	if (ft_add_left_child(tree, new) == ERROR_MALLOC)
		return (ft_print_error_malloc(), ERROR_MALLOC);
	if ((*tree)->type == EXEC_LIST)
	{
		if (ft_lst_exec(token, &(*tree)->lst_exec, data_parse) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

int	ft_add_tree_no_null(t_tree **tree, t_tree *new, \
		t_token *token, t_data_parse *data_parse)
{
	if ((*tree)->right_child == NULL)
	{
		if (ft_add_right_child(tree, new) == ERROR_MALLOC)
			return (ft_print_error_malloc(), ERROR_MALLOC);
		if ((*tree)->right_child->type == EXEC_LIST)
		{
			if (ft_lst_exec(token, &(*tree)->right_child->lst_exec, \
						data_parse) != SUCCESS)
				return (ERROR);
		}
	}
	else if ((*tree)->left_child == NULL)
	{
		if (ft_add_left_child(tree, new) == ERROR_MALLOC)
			return (ft_print_error_malloc(), ERROR_MALLOC);
		if ((*tree)->left_child->type == EXEC_LIST)
		{
			if (ft_lst_exec(token, &(*tree)->left_child->lst_exec, \
						data_parse) != SUCCESS)
				return (ERROR);
		}
	}
	return (SUCCESS);
}

int	ft_add_tree(t_tree **tree, t_tree *new, \
		t_token *token, t_data_parse *data_parse)
{
	*tree = ft_first_empty_child(*tree);
	if (*tree == NULL)
	{
		if (ft_add_tree_null(tree, new, token, data_parse) != SUCCESS)
			return (ERROR);
	}
	else
	{
		if (ft_add_tree_no_null(tree, new, token, data_parse) != SUCCESS)
			return (ERROR);
	}
	while ((*tree)->parent != NULL)
		*tree = (*tree)->parent;
	return (SUCCESS);
}

int	ft_complete_tree_part_2(t_tree **tree, t_token *tmp, \
		t_token **new, t_data_parse *data_parse)
{
	if (ft_is_there_parenthesis(tmp) == 1)
	{
		*new = without_parenthesis(tmp);
		if (*new == NULL)
			return (ERROR_MALLOC);
		if (ft_complete_tree(tree, *new, data_parse) != SUCCESS)
			return (ft_free_token(new), ERROR);
		ft_free_token(new);
	}
	else
	{
		if (ft_add_tree(tree, ft_tree_new(EXEC_LIST), \
					tmp, data_parse) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

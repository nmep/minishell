/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tree_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 02:02:25 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/23 10:06:54 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_node(t_tree **tree, t_token *token, \
		t_data_parse *data_parse, t_token *tmp)
{
	if (token->type == AND)
	{
		if (ft_add_tree(tree, ft_tree_new(OPPERATOR_AND), \
					tmp, data_parse) != SUCCESS)
			return (ERROR);
	}
	else if (token->type == OR)
	{
		if (ft_add_tree(tree, ft_tree_new(OPPERATOR_OR), \
					tmp, data_parse) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

int	ft_suite_add_node(t_tree **tree, t_token *token, \
		t_token **new, t_data_parse *data_parse)
{
	*new = after_token(token);
	if (*new == NULL)
		return (ft_print_error_malloc(), ERROR_MALLOC);
	if (ft_complete_tree(tree, *new, data_parse) != SUCCESS)
		return (ft_free_token(new), ERROR);
	ft_free_token(new);
	*new = before_token(token);
	if (*new == NULL)
		return (ft_print_error_malloc(), ERROR_MALLOC);
	if (ft_complete_tree(tree, *new, data_parse) != SUCCESS)
		return (ft_free_token(new), ERROR);
	ft_free_token(new);
	return (SUCCESS);
}

void	ft_complete_tree_first_step(t_token **token, int *parenthesis_open)
{
	while ((*token)->next != NULL)
		*token = (*token)->next;
	while (*token != NULL)
	{
		if (*parenthesis_open == 0 && ((*token)->type == AND \
					|| (*token)->type == OR))
			break ;
		if ((*token)->type == OPEN_PARENTHESIS)
			(*parenthesis_open)++;
		if ((*token)->type == CLOSE_PARENTHESIS)
			(*parenthesis_open)--;
		*token = (*token)->prev;
	}
}

int	ft_complete_tree(t_tree **tree, t_token *token, t_data_parse *data_parse)
{
	t_token	*tmp;
	t_token	*new;
	int		parenthesis_open;

	tmp = token;
	parenthesis_open = 0;
	ft_complete_tree_first_step(&token, &parenthesis_open);
	if (token != NULL)
	{
		if (parenthesis_open == 0 && (token->type == AND || token->type == OR))
		{
			if (ft_add_node(tree, token, data_parse, tmp) != SUCCESS)
				return (ERROR);
			if (ft_suite_add_node(tree, token, &new, data_parse) != SUCCESS)
				return (ERROR);
		}
	}
	else
	{
		if (ft_complete_tree_part_2(tree, tmp, &new, data_parse) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

int	ft_create_tree(t_tree **tree, t_token *token,
	t_data_parse *data_parse, int *exit_status)
{	
	int	tmp;

	tmp = g_signal;
	g_signal = -100;
	data_parse->index_here_doc = ft_nb_here_doc(token) - 1;
	if (ft_complete_here_doc(data_parse, token, 0, exit_status) != SUCCESS)
	{
		g_signal = tmp;
		return (ERROR);
	}
	g_signal = tmp;
	if (ft_complete_tree(tree, token, data_parse) != SUCCESS)
		return (free(data_parse->array_hd), \
				free_and_close_tree(*tree), ERROR);
	ft_free_token(&token);
	free(data_parse->array_hd);
	return (SUCCESS);
}

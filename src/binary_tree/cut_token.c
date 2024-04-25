/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:02:52 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/04 17:56:09 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_there_parenthesis(t_token *token)
{
	while (token->prev != NULL)
		token = token->prev;
	if (token->type != OPEN_PARENTHESIS)
		return (0);
	while (token->next != NULL)
		token = token->next;
	if (token->type != CLOSE_PARENTHESIS)
		return (0);
	return (1);
}

t_token	*without_parenthesis(t_token *token)
{
	t_token	*new;
	t_token	*tmp;

	while (token->prev != NULL)
		token = token->prev;
	tmp = token->next;
	new = NULL;
	while (tmp->next != NULL)
	{
		if (ft_lst_add_back(&new, ft_lstnew_no_malloc(tmp->str, \
						tmp->quotes, tmp->type, tmp->expand)) == ERROR_MALLOC)
			return (NULL);
		tmp = tmp->next;
	}
	while (new->prev != NULL)
		new = new->prev;
	return (new);
}

t_token	*before_token(t_token *token)
{
	t_token	*new;
	t_token	*tmp;

	new = NULL;
	tmp = token;
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	while (tmp != token)
	{
		if (ft_lst_add_back(&new, ft_lstnew_no_malloc(tmp->str, \
						tmp->quotes, tmp->type, tmp->expand)) == ERROR_MALLOC)
			return (NULL);
		tmp = tmp->next;
	}
	while (new->prev != NULL)
		new = new->prev;
	return (new);
}

t_token	*after_token(t_token *token)
{
	t_token	*new;
	t_token	*tmp;

	new = NULL;
	tmp = token->next;
	while (tmp != NULL)
	{
		if (ft_lst_add_back(&new, ft_lstnew_no_malloc(tmp->str, \
						tmp->quotes, tmp->type, tmp->expand)) == ERROR_MALLOC)
			return (NULL);
		tmp = tmp->next;
	}
	while (new->prev != NULL)
		new = new->prev;
	return (new);
}

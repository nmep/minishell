/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:31:38 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/13 01:07:09 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstlast(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

t_token	*ft_lstnew(char *str, int quotes, int type, t_expand *expand)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->str = ft_strdup(str);
	if (new->str == NULL)
		return (free(new), free(str), NULL);
	new->quotes = quotes;
	new->type = type;
	new->expand = expand;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_token	*ft_lstnew_no_malloc(char *str, int quotes, int type, t_expand *expand)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->str = ft_strdup(str);
	if (new->str == NULL)
		return (free(new), NULL);
	new->quotes = quotes;
	new->expand = expand;
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int	ft_lst_add_back(t_token **token, t_token *new)
{
	if (new == NULL)
		return (ERROR_MALLOC);
	if (*token == NULL)
		*token = new;
	else
	{
		new->prev = ft_lstlast(*token);
		ft_lstlast(*token)->next = new;
	}
	return (SUCCESS);
}

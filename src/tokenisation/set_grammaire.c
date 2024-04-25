/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_grammaire.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:13:05 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/04 18:08:24 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_redirection_text(t_token **token)
{
	if ((*token)->type == INFILE && (*token)->next->type == TEXT)
	{
		*token = (*token)->next;
		(*token)->type = INFILE_TEXT;
	}
	else if ((*token)->type == OUTFILE && (*token)->next->type == TEXT)
	{
		*token = (*token)->next;
		(*token)->type = OUTFILE_TEXT;
	}
	else if ((*token)->type == HEREDOC && (*token)->next->type == TEXT)
	{
		*token = (*token)->next;
		(*token)->type = HEREDOC_TEXT;
	}
	else if ((*token)->type == APPEND && (*token)->next->type == TEXT)
	{
		*token = (*token)->next;
		(*token)->type = APPEND_TEXT;
	}
}

void	ft_set_cmd_args(t_token **token)
{
	while (*token != NULL)
	{
		if ((*token)->type == TEXT)
		{
			(*token)->type = CMD;
			if ((*token)->next == NULL)
				break ;
			*token = (*token)->next;
			while ((*token)->type == TEXT)
			{
				(*token)->type = ARGS;
				if ((*token)->next == NULL)
					break ;
				*token = (*token)->next;
			}
		}
		else
		{
			if ((*token)->next == NULL)
				break ;
			*token = (*token)->next;
		}
	}
}

/*on defini le type de tout les textes qui suivient des 
operateurs de redirections
puis on defini le type de tout le reste soit les cmd suivi d'args */
void	ft_set_all_grammaire(t_token **token)
{
	while ((*token)->next != NULL)
	{
		ft_set_redirection_text(token);
		if ((*token)->next == NULL)
			break ;
		*token = (*token)->next;
	}
	while ((*token)->prev != NULL)
		*token = (*token)->prev;
	ft_set_cmd_args(token);
	while ((*token)->prev != NULL)
		*token = (*token)->prev;
}

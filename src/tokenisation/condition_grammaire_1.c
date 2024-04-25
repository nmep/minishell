/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_grammaire_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:36:25 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/13 01:03:15 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_parenthesis(t_token *token)
{
	int	count_open;
	int	count_close;

	count_open = 0;
	count_close = 0;
	while (token != NULL)
	{
		if (token->type == OPEN_PARENTHESIS)
			count_open++;
		if (token->type == CLOSE_PARENTHESIS)
			count_close++;
		if (count_close > count_open)
			return (print_invalid_token(")"), WRONG_INPUT);
		token = token->next;
	}
	if (count_close != count_open)
		return (print_invalid_token("("), WRONG_INPUT);
	return (GOOD_INPUT);
}

int	ft_check_proximity_opperator_bonus_suite(t_token *token)
{
	if (token->type == OPEN_PARENTHESIS && token->next == NULL)
		return (print_invalid_token("("), WRONG_INPUT);
	if (token->type == AND && token->next == NULL)
		return (print_invalid_token("&&"), WRONG_INPUT);
	if (token->type == OR && token->next == NULL)
		return (print_invalid_token("||"), WRONG_INPUT);
	return (GOOD_INPUT);
}

int	ft_check_proximity_opperator_bonus(t_token *token)
{
	while (token->next != NULL)
	{
		if (token->type == OPEN_PARENTHESIS && \
		(token->next->type == CLOSE_PARENTHESIS || token->next->type == OR \
		|| token->next->type == AND))
			return (print_invalid_token("("), WRONG_INPUT);
		if (token->type == AND && (token->next->type == OR \
		|| token->next->type == CLOSE_PARENTHESIS))
			return (print_invalid_token("&&"), WRONG_INPUT);
		if (token->type == OR && (token->next->type == AND \
		|| token->next->type == CLOSE_PARENTHESIS))
			return (print_invalid_token("||"), WRONG_INPUT);
		if (token->type == CLOSE_PARENTHESIS && (token->next != NULL \
		&& token->next->type != OR && token->next->type != AND \
		&& token->next->type != CLOSE_PARENTHESIS))
			return (print_invalid_token(")"), WRONG_INPUT);
		if ((token->type != AND && token->type != OR \
		&& token->type != OPEN_PARENTHESIS) \
		&& (token->next->type == OPEN_PARENTHESIS))
			return (print_invalid_token("("), WRONG_INPUT);
		token = token->next;
	}
	return (ft_check_proximity_opperator_bonus_suite(token));
}

int	is_cmd_between_bonus_opperator(t_token *token)
{
	int	cmd_or_not;

	cmd_or_not = 0;
	while (token != NULL)
	{
		if (token->type == CMD)
			cmd_or_not = 1;
		if (token->type == AND || token->type == OR)
		{
			if (cmd_or_not == 0)
			{
				if (token->type == AND)
					print_invalid_token("&&");
				if (token->type == OR)
					print_invalid_token("||");
				return (WRONG_INPUT);
			}
			cmd_or_not = 0;
		}
		token = token->next;
	}
	return (GOOD_INPUT);
}

/* que le premier token n'est pas une pipe ni le dernier
que les pipes ne soit pas colle a des operateur bonus et redirection et pipe
que les ( sont autant que les ) et que les ) ne soit jamais plus que les (
que les ( ne soit pas colle avec && || )
que les && ne soit pas colle avec || )
que les || ne soit pas colle avec && )
que les ) ne soit pas colle avec (
qu'il y au moins une commande autour de chaque && et || (pas forcemment colle)
que les ) soit suivi par rien ou && || )
que les ( soit precede par rien ou && || (
on verifie que les operateur de redirections sont bien suivi par un mot */
int	ft_condition_grammaire(t_token *token)
{
	if (ft_check_pipes(token) == WRONG_INPUT)
		return (print_invalid_token("|"), WRONG_INPUT);
	if (ft_check_parenthesis(token) == WRONG_INPUT)
		return (WRONG_INPUT);
	if (ft_check_proximity_opperator_bonus(token) == WRONG_INPUT)
		return (WRONG_INPUT);
	if (is_cmd_between_bonus_opperator(token) == WRONG_INPUT)
		return (WRONG_INPUT);
	if (is_redirection_well_followed(token) == WRONG_INPUT)
		return (WRONG_INPUT);
	return (GOOD_INPUT);
}

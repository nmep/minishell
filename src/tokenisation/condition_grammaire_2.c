/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_grammaire_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:08:04 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/13 01:05:10 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_quote_close(char *input, int double_quote_open, int single_quote_open)
{
	int	index;

	index = 0;
	while (input[index])
	{
		if (input[index] == '"')
			double_quote_open = OPEN;
		else if (input[index] == '\'')
			single_quote_open = OPEN;
		index++;
		while (double_quote_open == OPEN && input[index])
		{
			if (input[index++] == '"')
				double_quote_open = CLOSE;
		}
		while (single_quote_open == OPEN && input[index])
		{
			if (input[index++] == '\'')
				single_quote_open = CLOSE;
		}
	}
	if (double_quote_open == OPEN || single_quote_open == OPEN)
		return (ft_putstr_fd("minishell: syntax error with open quotes\n", 2), \
		OPEN);
	return (CLOSE);
}

int	ft_check_pipes(t_token *token)
{
	if (token->type == PIPE || ft_lstlast(token)->type == PIPE)
		return (WRONG_INPUT);
	while (token->next != NULL)
	{
		if (token->type == PIPE && (token->next->type == OR \
		|| token->next->type == AND || token->next->type == OPEN_PARENTHESIS \
		|| token->next->type == CLOSE_PARENTHESIS))
			return (WRONG_INPUT);
		if ((token->type == OR || token->type == AND \
		|| token->type == OPEN_PARENTHESIS || token->type == CLOSE_PARENTHESIS) \
		&& token->next->type == PIPE)
			return (WRONG_INPUT);
		if (token->type == PIPE && token->next->type == PIPE)
			return (WRONG_INPUT);
		token = token->next;
	}
	return (GOOD_INPUT);
}

int	is_redirection_well_followed(t_token *token)
{
	while (token->next != NULL)
	{
		if (token->type == INFILE && token->next->type != INFILE_TEXT)
			return (print_invalid_token("<"), WRONG_INPUT);
		else if (token->type == OUTFILE && token->next->type != OUTFILE_TEXT)
			return (print_invalid_token(">"), WRONG_INPUT);
		else if (token->type == HEREDOC && token->next->type != HEREDOC_TEXT)
			return (print_invalid_token("<<"), WRONG_INPUT);
		else if (token->type == APPEND && token->next->type != APPEND_TEXT)
			return (print_invalid_token(">>"), WRONG_INPUT);
		token = token->next;
	}
	if (token->type == INFILE && token->next == NULL)
		return (print_invalid_token("<"), WRONG_INPUT);
	else if (token->type == OUTFILE && token->next == NULL)
		return (print_invalid_token(">"), WRONG_INPUT);
	else if (token->type == HEREDOC && token->next == NULL)
		return (print_invalid_token("<<"), WRONG_INPUT);
	else if (token->type == APPEND && token->next == NULL)
		return (print_invalid_token(">>"), WRONG_INPUT);
	return (GOOD_INPUT);
}

void	print_no_cmd(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
}

int	ft_no_cmd(t_token *token)
{
	while (token->next != NULL)
	{
		if (token->type == CMD)
			return (GOOD_INPUT);
		token = token->next;
	}
	if (token->type == CMD)
		return (GOOD_INPUT);
	return (WRONG_INPUT);
}

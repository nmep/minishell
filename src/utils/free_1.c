/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:02:59 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/06 15:29:26 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_token(t_token **token)
{
	t_token	*tmp;

	if (*token == NULL)
		return ;
	while ((*token)->prev != NULL)
		*token = (*token)->prev;
	while (*token != NULL)
	{
		if ((*token)->str != NULL)
			free((*token)->str);
		tmp = *token;
		*token = (*token)->next;
		free(tmp);
	}
}

void	free_tokenisation_2(t_token **token, t_data_parse *data_parse)
{
	t_token	*tmp;

	ft_print_error_malloc();
	free(data_parse->input);
	free(data_parse->str);
	while (token != NULL)
	{
		free((*token)->str);
		tmp = *token;
		*token = (*token)->next;
		free(tmp);
	}
}

void	free_tokenisation_1(char *input, t_token **token)
{
	t_token	*tmp;

	ft_print_error_malloc();
	free(input);
	while (token != NULL)
	{
		free((*token)->str);
		tmp = *token;
		*token = (*token)->next;
		free(tmp);
	}
}

void	free_2d(char **str)
{
	int	index;

	if (str == NULL)
		return ;
	if (str[0] == NULL)
	{
		free(str);
		return ;
	}
	index = -1;
	while (str[++index])
	{
		if (str[index] != NULL)
			free(str[index]);
	}
	free(str);
}

void	ft_print_error_malloc(void)
{
	ft_putstr_fd("minishell: malloc failed\n", 2);
}

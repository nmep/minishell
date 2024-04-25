/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 00:23:08 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/23 10:14:48 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse(t_tree **tree, t_data_parse *data_parse,
	char **env, int *exit_status)
{
	t_token	*token;

	if (is_input_only_whitespace(data_parse->input))
		add_history(data_parse->input);
	token = NULL;
	data_parse->exit_status = *exit_status;
	data_parse->env = ft_strdup_2d(env);
	if (data_parse->env == NULL)
		return (ERROR_MALLOC);
	if (ft_tokenisation(&token, data_parse) != SUCCESS)
		return (free_2d(data_parse->env), ERROR);
	if (ft_condition_grammaire(token) == WRONG_INPUT)
		return (free_2d(data_parse->env), ft_free_token(&token), WRONG_INPUT);
	if (ft_create_tree(tree, token, data_parse, exit_status) != SUCCESS)
		return (free_2d(data_parse->env), ft_free_token(&token), ERROR_MALLOC);
	return (free_2d(data_parse->env), GOOD_INPUT);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 06:51:13 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/12 11:16:30 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_no_empty(char **arg)
{
	int	index;

	index = -1;
	while (arg[++index])
	{
		if (arg[index][0] != '\0')
			return (0);
	}
	return (1);
}

char	**ft_without_empty(char **new_args)
{
	char	**res;
	int		index;

	if (is_no_empty(new_args))
		return (free_2d(new_args), NULL);
	res = malloc(sizeof(char *));
	if (res == NULL)
		return (NULL);
	res[0] = NULL;
	index = -1;
	while (new_args[++index])
	{
		if (new_args[index][0] != '\0')
		{
			res = ft_add_to_2d(res, new_args[index]);
			if (res == NULL)
				return (free_2d(new_args), NULL);
		}
	}
	return (free_2d(new_args), res);
}

char	**ft_new_args(t_lst_exec *lst_exec, int status, char **env)
{
	char			**new_args;
	int				index;
	t_data_expand	data_expand;

	if (lst_exec->args == NULL)
		return (NULL);
	data_expand.env = env;
	data_expand.status = status;
	lst_exec->len_expand = ft_strlen_2d(lst_exec->args);
	new_args = malloc (sizeof(char *));
	if (new_args == NULL)
		return (NULL);
	new_args[0] = NULL;
	index = 0;
	while (index < lst_exec->len_expand)
	{
		new_args = ft_add_and_replace_env_variable(lst_exec->args[index], \
				lst_exec->expand[index], &data_expand, new_args);
		if (new_args == NULL)
			return (NULL);
		index++;
	}
	return (ft_without_empty(new_args));
}

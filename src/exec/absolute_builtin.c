/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 07:43:04 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/04 08:14:36 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_absolute_path_builtin(char **arg)
{
	int		i;
	int		len;
	char	*cmd_name;

	i = 0;
	if (access(*arg, F_OK | X_OK) != 0)
		return (-1);
	len = ft_strlen(*arg) - 1;
	while ((*arg)[len] && (*arg)[len--] != '/')
		i++;
	cmd_name = malloc(i + 1);
	if (!cmd_name)
		return (ERROR_MALLOC);
	i = 0;
	len++;
	while ((*arg)[++len])
		cmd_name[i++] = (*arg)[len];
	cmd_name[i] = '\0';
	free(*arg);
	*arg = ft_str_dup_env(cmd_name, *arg);
	free(cmd_name);
	return (0);
}

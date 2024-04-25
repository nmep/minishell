/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_and_check_cmd_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 03:15:04 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/12 03:15:23 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_cmd_2(char **cmd, int *status, char ***env)
{
	int	fake_exit_status;

	fake_exit_status = 0;
	*status = ft_find_builtin(cmd[0], cmd, env, &fake_exit_status);
	if (*status == -1)
		return (1);
	free_tab_tab(cmd);
	free_tab_tab(*env);
	exit(*status);
}

int	ft_check_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

void	free_exit(char **env, char **cmd)
{
	free_tab_tab(env);
	free_tab_tab(cmd);
}

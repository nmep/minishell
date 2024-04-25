/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:32:17 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/20 04:38:57 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_builtin2(char *cmd, char **cmd_tab, char ***env, int *exit_flag)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd, "exit") == 0)
	{
		status = ft_exit(cmd_tab, exit_flag);
		return (status);
	}
	else if (ft_strcmp(cmd, "unset") == 0)
	{
		status = ft_unset(env, cmd_tab);
		return (status);
	}
	else if (ft_strcmp(cmd, "export") == 0)
	{
		status = ft_export(env, cmd_tab, 0);
		return (status);
	}
	else if (ft_strcmp(cmd, "env") == 0)
	{
		status = ft_env(*env);
		return (status);
	}
	return (-1);
}

int	ft_find_builtin(char *cmd, char **cmd_tab, char ***env, int *exit_flag)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd, "cd") == 0)
	{
		status = ft_cd(cmd_tab, env);
		return (status);
	}
	else if (ft_strcmp(cmd, "echo") == 0)
	{
		status = ft_echo(cmd_tab);
		return (status);
	}
	else if (ft_strcmp(cmd, "pwd") == 0)
	{
		status = ft_pwd(cmd_tab, *env);
		return (status);
	}
	else
		status = ft_find_builtin2(cmd, cmd_tab, env, exit_flag);
	return (status);
}

int	ft_is_builtin(char **cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(*cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(*cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(*cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(*cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(*cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(*cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(*cmd, "env") == 0)
		return (1);
	return (0);
}

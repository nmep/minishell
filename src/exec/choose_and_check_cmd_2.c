/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_and_check_cmd_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:48:10 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/12 11:16:53 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	find_cmd_2(char **cmd, int *status, char ***env)
// {
// 	int	fake_exit_status;

// 	fake_exit_status = 0;
// 	*status = ft_find_builtin(cmd[0], cmd, env, &fake_exit_status);
// 	if (*status == -1)
// 		return (1);
// 	free_tab_tab(cmd);
// 	free_tab_tab(*env);
// 	exit(*status);
// }

// int	ft_check_cmd(char *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '/')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// void	free_exit(char **env, char **cmd)
// {
// 	free_tab_tab(env);
// 	free_tab_tab(cmd);
// }

void	find_cmd_4(char **cmd, char ***env)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": cannot execute binary file:", 2);
	ft_putstr_fd(strerror(errno), 2);
	free_tab_tab(cmd);
	free_tab_tab(*env);
	exit (126);
}

void	find_cmd_5(char ***env, char **cmd)
{
	DIR	*dirp;

	dirp = opendir(cmd[0]);
	if (dirp != NULL)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(" : Is a directory\n", 2);
		free_exit(*env, cmd);
		closedir(dirp);
		exit (126);
	}
	closedir(dirp);
}

void	find_cmd_3(char ***env, char **cmd)
{
	find_cmd_5(env, cmd);
	if (access(cmd[0], F_OK | X_OK) == 0)
	{
		if (execve(cmd[0], cmd, *env) == -1)
			find_cmd_4(cmd, env);
	}
	if (access(cmd[0], F_OK) != 0)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		free_exit(*env, cmd);
		exit (127);
	}
	if (access(cmd[0], X_OK) != 0)
	{
		ft_putstr_fd("Permission denied\n", 2);
		free_exit(*env, cmd);
		exit (126);
	}
}

int	find_cmd(char ***env, char **cmd)
{
	int	status;

	status = 0;
	if (!ft_check_cmd(cmd[0]))
		find_cmd_3(env, cmd);
	if (ft_is_builtin(cmd))
		find_cmd_2(cmd, &status, env);
	else
	{
		if (access(cmd[0], F_OK | X_OK) == 0 && !ft_check_cmd(cmd[0]))
		{
			if (execve(cmd[0], cmd, *env) == -1)
			{
				ft_putstr_fd(cmd[0], 2);
				ft_putstr_fd(": cannot execute binary file:", 2);
				ft_putstr_fd(strerror(errno), 2);
				free_exit(*env, cmd);
				exit (126);
			}
		}
		ft_check_path_cmd(env, cmd);
	}
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_and_check_cmd_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:10:03 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/23 10:15:56 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_path_cmd(char **env)
{
	char	**path_split;
	char	*path;

	path = ft_get_env_value(env, "PATH");
	if (!path)
		return (NULL);
	path_split = ft_split(path, ':');
	if (!path_split)
		return (free(path), NULL);
	free(path);
	return (path_split);
}

void	ft_check_path_execve(char **path, char ***cmd, char ***env)
{
	if (execve(*path, *cmd, *env) == -1)
	{
		printf("minishell: %s: cannot execute binary file: \
			%s\n", (*cmd)[0], strerror(errno));
		free(*path);
		free_tab_tab(*cmd);
		free_tab_tab(*env);
		exit (126);
	}
}

void	free_check_path(char ***env, char ***cmd,
	char **msg_err, char ***path_split)
{
	if (env != NULL)
		free_tab_tab(*env);
	if (cmd != NULL)
		free_tab_tab(*cmd);
	if (msg_err != NULL)
		free(*msg_err);
	if (path_split != NULL)
		free_tab_tab(*path_split);
}

void	ft_check_path_cmd_2(char **path_split, char ***env, char **cmd)
{
	if (!path_split)
	{
		free_check_path(env, &cmd, NULL, NULL);
		exit (127);
	}
}

int	ft_check_path_cmd(char ***env, char **cmd)
{
	int		i;
	char	*cmd_path;
	char	**path_split;
	char	*msg_err;

	path_split = ft_get_path_cmd(*env);
	ft_check_path_cmd_2(path_split, env, cmd);
	i = -1;
	while (path_split[++i])
	{
		cmd_path = ft_strjoin_path_without_free(path_split[i], cmd[0]);
		if (cmd_path == NULL)
			return (ERROR_MALLOC);
		if (!access(cmd_path, F_OK | X_OK))
		{
			free_tab_tab(path_split);
			ft_check_path_execve(&cmd_path, &cmd, env);
		}
		free (cmd_path);
	}
	msg_err = ft_strjoin_wihtout_free(cmd[0], ": command not found\n");
	ft_putstr_fd(msg_err, 2);
	free_check_path(env, &cmd, &msg_err, &path_split);
	exit(127);
}

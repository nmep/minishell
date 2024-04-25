/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:42:46 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/20 04:02:44 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_parsing(char **path_tab)
{
	if (path_tab[1] && strcmp(path_tab[1], ".") == 0)
		return (1);
	if (ft_len_tab_tab(path_tab) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (ft_strlen(path_tab[1]) > 256)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path_tab[1], 2);
		ft_putstr_fd(": File name too long\n", 2);
		return (1);
	}
	return (0);
}

int	ft_cd_home(char ***env)
{
	char	current_path[PATH_MAX + 1];
	char	*oldpwd;
	char	new_path[PATH_MAX + 1];

	if (getcwd(current_path, PATH_MAX) == NULL)
		return (2);
	if (is_export_name_in_env(*env, "HOME") == -1)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 2);
	oldpwd = ft_get_env_value(*env, "HOME");
	if (chdir(oldpwd) != 0)
		return (ft_msg_err_chdir(oldpwd), free(oldpwd), 1);
	if (getcwd(new_path, PATH_MAX) == NULL)
		return (ft_msg_err_getcwd(), free(oldpwd), 1);
	free(oldpwd);
	ft_change_pwd_old_pwd(current_path, new_path, env);
	return (0);
}

int	ft_cd_dash(char ***env)
{
	char	current_path[PATH_MAX + 1];
	char	*oldpwd;
	char	new_path[PATH_MAX + 1];

	if (is_export_name_in_env(*env, "OLDPWD") == -1)
		return (ft_putstr_fd("minishell: cd:"\
			" OLDPWD not set\n", 2), 1);
	oldpwd = ft_get_env_value(*env, "OLDPWD");
	if (getcwd(current_path, PATH_MAX) == NULL)
		return (ft_msg_err_getcwd(), free(oldpwd), 1);
	if (chdir(oldpwd) != 0)
	{
		if (ft_msg_err_chdir(oldpwd) == ERROR_MALLOC)
			return (ERROR_MALLOC);
		return (free(oldpwd), 1);
	}
	if (getcwd(new_path, PATH_MAX) == NULL)
		return (ft_msg_err_getcwd(), free(oldpwd), 1);
	free(oldpwd);
	ft_change_pwd_old_pwd(current_path, new_path, env);
	return (0);
}

int	ft_cd_cdpath(char **path_tab, char ***env)
{
	char	current_path[PATH_MAX + 1];
	char	new_path[PATH_MAX + 1];

	if (getcwd(current_path, PATH_MAX) == NULL)
		return (2);
	if (is_export_name_in_env(*env, "CDPATH") != -1)
	{
		if (ft_cdpath(path_tab, *env) == 0)
		{
			if (getcwd(new_path, PATH_MAX) != NULL)
			{
				ft_change_pwd_old_pwd(current_path, new_path, env);
				return (0);
			}
			else
				return (ft_msg_err_getcwd(), 1);
		}
	}
	if (ft_msg_err_chdir(path_tab[1]) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	return (1);
}

int	ft_cd(char **path_tab, char ***env)
{
	char	*current_path;
	char	new_path[PATH_MAX + 1];

	current_path = ft_get_env_value(*env, "PWD");
	if (!current_path)
		return (ERROR_MALLOC);
	if (ft_cd_parsing(path_tab) != 0)
		return (free(current_path), 1);
	if (!path_tab[1] || ft_strcmp(path_tab[1], "~") == 0)
		return (free(current_path), ft_cd_home(env));
	if (ft_strcmp(path_tab[1], "-") == 0)
		return (free(current_path), ft_cd_dash(env));
	if (chdir(path_tab[1]) != 0)
	{
		return (free(current_path), ft_cd_cdpath(path_tab, env));
	}
	if (getcwd(new_path, PATH_MAX) == NULL)
	{
		printf("you are lost in the abysse of the shell\n");
		ft_change_pwd_old_pwd(current_path, "/lost", env);
		return (0);
	}
	ft_change_pwd_old_pwd(current_path, new_path, env);
	free(current_path);
	return (0);
}

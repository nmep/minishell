/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:26:44 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/22 13:08:47 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_builtin_err_msg(char *builtin)
{
	char	*builtin_msg;
	char	*err;
	char	*final_msg;

	err = NULL;
	builtin_msg = NULL;
	builtin_msg = ft_str_dup_env(builtin, builtin_msg);
	if (!builtin_msg)
		return (NULL);
	err = ft_str_dup_env(": write error: No space left on device\n", err);
	if (!err)
		return (NULL);
	final_msg = ft_strjoin(builtin_msg, err);
	free(builtin_msg);
	free(err);
	return (final_msg);
}

int	ft_pustr_builtin_pwd(char *str)
{
	char	*err_msg;
	char	*pwd_val;

	pwd_val = ft_strjoin_wihtout_free(str, "\n");
	if (!pwd_val)
		return (ERROR_MALLOC);
	err_msg = ft_get_builtin_err_msg("pwd");
	if (!err_msg)
		return (free(pwd_val), ERROR_MALLOC);
	if (write(1, pwd_val, ft_strlen(pwd_val)) == -1)
	{
		ft_putstr_fd(err_msg, 2);
		return (free(err_msg), free(pwd_val), 1);
	}
	free(pwd_val);
	free(err_msg);
	return (0);
}

int	ft_pwd(char **tab, char **env)
{
	char	*path;
	char	buf[PATH_MAX + 1];
	int		check;
	int		free_check;

	(void)tab;
	free_check = 1;
	path = ft_get_env_value(env, "PWD");
	if (!path)
	{
		path = getcwd(buf, PATH_MAX);
		free_check = 0;
	}
	check = ft_pustr_builtin_pwd(path);
	if (free_check == 1)
		free(path);
	return (check);
}

// int	main(int ac, char **av, char **envp)
// {
// 	(void)ac;
// 	ft_pwd(av + 1, envp);
// }
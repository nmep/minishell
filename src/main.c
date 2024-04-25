/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:52:38 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/23 10:27:40 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	set_main_1(t_tree **tree, int argc, char **argv)
{
	*tree = NULL;
	(void)argv;
	if (argc != 1)
		return (ERROR);
	if (ft_set_sig() == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	set_main_2(char ***env, char **envp, int *exit_status)
{
	*exit_status = 0;
	*env = ft_copy_env(envp);
	if (*env == NULL)
		return (ERROR_MALLOC);
	return (SUCCESS);
}

int	main_2(t_tree **tree, t_data_parse *data_parse,
	char ***env, int *exit_status)
{
	if (ft_parse(tree, data_parse, *env, exit_status) == GOOD_INPUT)
	{
		if (g_signal == 130)
			*exit_status = g_signal;
		g_signal = -100;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		*exit_status = ft_tree_exec(*tree, env, exit_status);
		if (*exit_status == ERROR_MALLOC)
			return (free_and_close_tree(*tree),
				free_tab_tab(*env), ERROR_MALLOC);
		free_and_close_tree(*tree);
		if (ft_change_sig() != SUCCESS)
			return (free_and_close_tree(*tree),
				free_tab_tab(*env), ERROR_MALLOC);
		g_signal = 0;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data_parse	data_parse;
	t_tree			*tree;
	int				exit_status;
	char			**env;

	if (set_main_2(&env, envp, &exit_status))
		return (ERROR);
	while (1)
	{
		set_main_1(&tree, argc, argv);
		data_parse.prompt = ft_get_prompt(env);
		if (data_parse.prompt == NULL)
			return (ERROR_PROMPT);
		data_parse.input = readline(data_parse.prompt);
		free(data_parse.prompt);
		if (data_parse.input == NULL)
			return (rl_clear_history(),
				ft_putstr_fd("exit\n", 1), free_tab_tab(env), 0);
		if (main_2(&tree, &data_parse, &env, &exit_status) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	return (exit_status);
}

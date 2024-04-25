/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:52:06 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/11 01:21:29 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_bool	ft_atoi(char *str, long long int *res)
{
	int	i;
	int	s;

	i = 0;
	*res = 0;
	s = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (__LONG_LONG_MAX__ / 10 < *res || (*res == __LONG_LONG_MAX__ / 10
				&& str[i] - 48 > __LONG_LONG_MAX__ % 10))
			return (FALSE);
		*res = *res * 10 + str[i] - 48;
		i++;
	}
	*res = s * *res % 256;
	return (TRUE);
}

int	ft_check_exit_char(char *str)
{
	int	i;
	int	flag;
	int	flag_space;

	i = 0;
	flag = 0;
	flag_space = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
	{
		flag_space++;
		i++;
	}
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-')
			flag++;
		if (((str[i] < '0' || str[i] > '9') && (str[i] != '+'
					&& str[i] != '-')) || ((flag_space > 0 || i >= 1)
				&& (str[i] == '+' || str[i] == '-')))
			return (0);
		i++;
	}
	if (flag > 1)
		return (0);
	return (1);
}

void	ft_exit_parsing(char **arg, long long int *exit_value, int *exit_flag)
{
	if (arg[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		*exit_flag = 0;
		*exit_value = 1;
		return ;
	}
	return ;
}

int	ft_exit(char **arg, int *exit_flag)
{
	long long int	exit_value;

	if (arg[1] == NULL)
	{
		*exit_flag = 1;
		return (0);
	}
	if (ft_atoi(arg[1], &exit_value) == FALSE)
	{
		return (ft_putstr_fd(": numeric arugment required\n", 2),
			ft_putstr_fd(arg[1], 2),
			ft_putstr_fd("minishell: exit: ", 2), 2);
	}
	else
		*exit_flag = 1;
	if (!ft_check_exit_char(arg[1]))
	{
		*exit_flag = 1;
		exit_value = 2;
		return (ft_putstr_fd("minishell: exit: ", 2),
			ft_putstr_fd(arg[1], 2),
			ft_putstr_fd(": numeric argumment required\n", 2), exit_value);
	}
	ft_exit_parsing(arg, &exit_value, exit_flag);
	return (exit_value);
}

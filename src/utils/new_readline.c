/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:02:47 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/23 10:03:51 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_new_readline(char **new, char **read_str, int *size)
{
	*new = malloc(sizeof(char));
	if (*new == NULL)
		return (ERROR);
	*new[0] = '\0';
	*read_str = malloc(2 * sizeof(char));
	if (*read_str == NULL)
		return (free(*new), ERROR);
	*read_str[0] = '\0';
	*size = read(0, *read_str, 1);
	return (SUCCESS);
}

char	*ft_handle_ctrl_c(char *new, char *read_str)
{
	printf("\n");
	return (free(new), free(read_str), NULL);
}

char	*ft_handle_ctrl_d(char *new, char *read_str, char *lim)
{
	printf("\n");
	ft_putstr_fd("minishell: warning: here-document wanted (`", 2);
	ft_putstr_fd(lim, 2);
	ft_putstr_fd("')\n", 2);
	return (free(new), free(read_str), NULL);
}

char	*ft_end_2(int size, char *new, char *read_str, char *lim)
{
	char	*res;

	if (size == -1)
		return (ft_handle_ctrl_c(new, read_str));
	if (size == 0)
		return (ft_handle_ctrl_d(new, read_str, lim));
	res = ft_strdup(new);
	if (res == NULL)
		return (free(new), free(read_str), NULL);
	return (free(new), free(read_str), res);
}

char	*new_readline(char *lim, int *exit_status)
{
	char	*new;
	char	*read_str;
	int		size;

	if (ft_set_new_readline(&new, &read_str, &size) != SUCCESS)
		return (NULL);
	while (size > 0)
	{
		read_str[1] = '\0';
		if (read_str[0] == '\n')
		{
			new = ft_join_char(new, read_str[0]);
			if (new == NULL)
				return (free(read_str), NULL);
			return (free(read_str), new);
		}
		else
		{
			new = ft_join_char(new, read_str[0]);
			if (new == NULL)
				return (free(read_str), NULL);
		}
		size = read(0, read_str, 1);
	}
	return (ft_end_1(size, exit_status), ft_end_2(size, new, read_str, lim));
}

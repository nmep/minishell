/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 03:45:01 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/05 13:08:48 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize(t_token *token)
{
	int	count;

	count = 0;
	while (token != NULL)
	{
		token = token->next;
		count++;
	}
	return (count);
}

int	ft_isalphanum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') \
			|| (c >= '0' && c <= '9') || c == '_')
	{
		return (1);
	}
	return (0);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	index;

	index = 0;
	while (str1[index] && str2[index] && (str1[index] == str2[index]))
		index++;
	return (str1[index] - str2[index]);
}

void	print_invalid_token(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
}

char	*ft_strdup(char *str)
{
	char	*new;
	int		index;

	new = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	index = -1;
	while (str[++index])
		new[index] = str[index];
	new[index] = '\0';
	return (new);
}

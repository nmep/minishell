/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 22:58:50 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/04 18:11:34 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_str(char *str)
{
	return (str);
}

int	ft_count_itoa(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*itoa;
	int		len;
	long	long_n;

	len = ft_count_itoa(n);
	long_n = n;
	itoa = (char *)malloc((len + 1) * sizeof(char));
	if (itoa == NULL)
		return (NULL);
	itoa[len] = '\0';
	if (long_n < 0)
		long_n *= -1;
	while (len > 0)
	{
		itoa[len - 1] = (long_n % 10) + '0';
		long_n /= 10;
		len--;
	}
	if (n < 0)
	itoa[0] = '-';
	return (itoa);
}

int	ft_is_ascii(char c)
{
	return (!(c >= '0' && c <= '9'));
}

char	*ft_strjoin_1_malloc(char *str1, char *str2)
{
	char	*join;
	int		i;
	int		j;

	if (str2 == NULL)
		return (str1);
	join = malloc ((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
	if (join == NULL)
		return (free(str1), NULL);
	i = -1;
	while (str1[++i])
		join[i] = str1[i];
	j = -1;
	while (str2[++j])
		join[i + j] = str2[j];
	join[i + j] = '\0';
	return (free(str1), join);
}

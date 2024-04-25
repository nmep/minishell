/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:37:17 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/16 19:43:50 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_word(int nb)
{	
	int	count;

	count = 1;
	while (nb >= 10)
	{
		nb /= 10;
		count++;
	}	
	return (count);
}

char	*ft_itoa_shlvl(int nb)
{
	char	*str;
	int		len;
	int		i;

	if (nb >= 999)
	{
		ft_putstr_fd("minishell: warning: shell level (1000)"
			" too high, resetting to 1\n", 2);
		nb = 1;
	}
	len = count_word(nb);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	str[len] = '\0';
	while (0 < len)
	{
		str[len - 1] = (nb % 10) + '0';
		nb /= 10;
		len--;
	}
	return (str);
}

int	ft_atoi_int_shlvl_main(char **envp, char *nb)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	(void)envp;
	if (nb == NULL)
		return (1);
	while (nb[i])
	{
		res = res * 10 + (nb[i] - 48);
		i++;
	}
	res++;
	return (res);
}

char	*ft_change_shlvl(char **envp, char *shlvl)
{
	char	*res_val;
	char	*res;

	res_val = ft_itoa_shlvl(ft_atoi_int_shlvl_main(envp, shlvl));
	if (!res_val)
		return (NULL);
	res = ft_strjoin_wihtout_free("SHLVL=", res_val);
	free(res_val);
	if (!res)
		return (NULL);
	return (res);
}

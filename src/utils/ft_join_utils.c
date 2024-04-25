/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:54:03 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/23 10:15:45 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_equal_val(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new_export;

	i = -1;
	new_export = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[++i])
		new_export[i] = s1[i];
	j = -1;
	while (s2[++j])
		new_export[i++] = s2[j];
	new_export[i] = '\0';
	free(s1);
	free(s2);
	return (new_export);
}

char	*ft_strjoin_path_without_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	str = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) + 2);
	while (s1[++i])
		str[i] = s1[i];
	str[i++] = '/';
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
}

char	*ft_strjoin_wihtout_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	str = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
}

char	*ft_strjoin_path(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	str = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) + 2);
	while (s1[++i])
		str[i] = s1[i];
	str[i++] = '/';
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free (s1);
	return (str);
}

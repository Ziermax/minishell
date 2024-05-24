/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:02:55 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/03/30 15:15:26 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/libft.h"

#include <stdio.h>

char	*ft_strjoin(char *str1, char *str2)
{
	char	*join;
	int		len1;
	int		len2;
	int		i;

	if (!str1 && !str2)
		return (NULL);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (!len1 && !len2)
		return (ft_calloc(sizeof(char), 1));
	join = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!join)
		return (NULL);
	i = -1;
	while (++i < len1)
		join[i] = str1[i];
	while (i < len1 + len2)
	{
		join[i] = str2[i - len1];
		i++;
	}
	join[i] = '\0';
	return (join);
}

char	*ft_threejoin(char *str1, char *str2, char *str3)
{
	char	*join;
	int		len1;
	int		len2;
	int		len3;
	int		i;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	len3 = ft_strlen(str3);
	if (!len1 && !len2 && !len3)
		return (NULL);
	join = malloc(sizeof(char) * (len1 + len2 + len3 + 1));
	if (!join)
		return (NULL);
	i = -1;
	while (++i < len1)
		join[i] = str1[i];
	i -= 1;
	while (++i < len1 + len2)
		join[i] = str2[i - len1];
	i -= 1;
	while (++i < len1 + len2 + len3)
		join[i] = str3[i - len1 - len2];
	join[i] = '\0';
	return (join);
}
/*
int	main(void)
{
	char	*str;

	str = ft_threejoin("/bin", "/", "ls");
	printf("path: \"%s\"\n", str);
	free(str);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:43:14 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/08 22:03:10 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/libft.h"

void	*ft_calloc(int count, int size)
{
	char	*rtrn;
	int		i;

	rtrn = malloc(sizeof(char) * count * size);
	if (!rtrn)
		return (NULL);
	i = 0;
	count = count * size;
	while (i < count)
		rtrn[i++] = 0;
	return (rtrn);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(char *str, int start, int bytes)
{
	char	*substr;
	int		len;
	int		i;

	if (!str || start < 0 || bytes < 0)
		return (NULL);
	len = ft_strlen(str);
	if (len - start <= 0)
		return (ft_strdup(""));
	if (len - start < bytes)
		len = len - start;
	else
		len = bytes;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
		substr[i++] = *(str++ + start);
	substr[i] = '\0';
	return (substr);
}

char	*ft_itoa(int num)
{
	char	*nbr;
	int		len;
	int		i;

	if (num == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_intlen(num) + (num < 0);
	nbr = malloc(sizeof(char) * (len + 1));
	if (!nbr)
		return (NULL);
	nbr[len] = '\0';
	i = 0;
	if (num < 0)
	{
		nbr[i++] = '-';
		num = -num;
	}
	while (i < len)
	{
		nbr[--len] = num % 10 + '0';
		num = num / 10;
	}
	return (nbr);
}

char	**ft_splitdup(char **split)
{
	char	**dup;
	int		i;
	int		size;

	size = ft_arraylen(split);
	dup = ft_calloc(size + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dup[i] = ft_strdup(split[i]);
		if (!dup[i])
		{
			free_split(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

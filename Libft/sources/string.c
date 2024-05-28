/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:07:32 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/05/28 19:25:38 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strlcat(char	*dst, char *src, int dstsize)
{
	int	i;

	if (!dst || !src || !dstsize)
		return (dstsize);
	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	if (dst[i] || i == dstsize)
		return (ft_strlen(src) + dstsize);
	while (*src && i < dstsize)
		dst[i++] = *(src++);
	dst[i] = '\0';
	return (ft_strlen(src) + i);
}
#include <stdio.h>

int	ft_strfcat(char	*dst, char *src, int dstsize, int from)
{
	if (from >= dstsize)
		return (dstsize);
	printf("from0: %d\n", from);
	while (*src && from < dstsize)
		dst[from++] = *(src++);
	dst[from] = '\0';
	printf("from: %d\n", from);
	return (ft_strlen(src) + from);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:07:32 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/09 11:05:36 by mvelazqu         ###   ########.fr       */
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

int	ft_strfcat(char	*dst, char *src, int dstsize, int from)
{
	if (!dst || !src || !dstsize)
		return (dstsize);
	if (from >= dstsize)
		return (dstsize);
	while (*src && from < dstsize)
		dst[from++] = *(src++);
	dst[from] = '\0';
	return (ft_strlen(src) + from);
}

void	ft_memset(void *dir, int c, size_t bytes)
{
	while (bytes--)
		*(char *)dir++ = c;
}

void	ft_bzero(void *dir, size_t bytes)
{
	ft_memset(dir, 0, bytes);
}

void	swap_strings(char **str_p, char *str)
{
	free(*str_p);
	*str_p = str;
}

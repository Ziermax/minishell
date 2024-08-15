/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:07:32 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/15 19:09:56 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(char *str1, char *str2, int bytes)
{
	if (!str1 || !str2 || bytes <= 0)
		return (0);
	while (*str1 && *str1 == *str2 && bytes-- > 1)
	{
		str2++;
		str1++;
	}
	return ((unsigned char)*str1 - (unsigned char)*str2);
}

int	ft_strfcat(char	*dst, char *src, int dstsize, int from)
{
	if (!dst || !src || !dstsize || from < 0)
		return (dstsize);
	if (from >= dstsize)
		return (dstsize);
	while (*src && from < dstsize)
		dst[from++] = *(src++);
	dst[from] = '\0';
	return (ft_strlen(src) + from);
}

//void	ft_memset(void *dir, int c, size_t bytes)
//{
//	while (bytes--)
//		*(char *)dir++ = c;
//}
//
//	ft_memset(dir, 0, bytes);
void	ft_bzero(void *dir, size_t bytes)
{
	while (bytes--)
		*(char *)dir++ = '\0';
}

char	*ft_strchr(char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str && (unsigned char)*str != (unsigned char)c)
		str++;
	if (*str == c)
		return (str);
	return (NULL);
}

char	*ft_strrchr(char *str, int c)
{
	char	*tmp;

	if (!str)
		return (NULL);
	tmp = NULL;
	while (*str)
	{
		if (*str == c)
			tmp = str;
		str++;
	}
	if (*str == c)
		return (str);
	return (tmp);
}

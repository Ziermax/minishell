/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:07:32 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/20 20:14:08 by mvelazqu         ###   ########.fr       */
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

char	*ft_substr(char *str, int start, int bytes)
{
	char	*substr;
	int		len;
	int		i;

	if (!str || start < 0 || bytes <= 0)
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

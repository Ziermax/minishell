/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:07:32 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/18 20:22:36 by mvelazqu         ###   ########.fr       */
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
	if (from >= dstsize)
		return (dstsize);
	while (*src && from < dstsize)
		dst[from++] = *(src++);
	dst[from] = '\0';
	return (ft_strlen(src) + from);
}

void	ft_print_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		fd_printf(1, "split[%d]: \"%s\"\n", split[i]);
		i++;
	}
}

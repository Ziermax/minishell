/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:58:10 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/02 13:47:03 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include <stdio.h>

static int	unspecialized_len(char *str, char *set)
{
	int	len;

	if (!str || !set)
		return (0);
	len = 0;
	while (*str)
	{
		if (ft_strchr(set, *str))
			len++;
		str++;
		len++;
	}
	return (len);
}

char	*unspecialize_set(char *str, char *set)
{
	char	*unspecialized;
	int		len;
	int		i;

	if (!str || !set)
		return (NULL);
	len = unspecialized_len(str, set);
	unspecialized = malloc(sizeof(char) * (len + 1));
	if (!unspecialized)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(set, *str))
			unspecialized[i++] = '\\';
		unspecialized[i] = *(str++);
		if (i < len)
			i++;
	}
	unspecialized[len] = '\0';
	return (unspecialized);
}

static int	normalize_len(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (*str)
	{
		if (*str == '\\'/* &&  *(str + 1) != '\\'*/)
			str++;
		if (!*str)
			continue ;
		len++;
		str++;
	}
	return (len);
}

char	*remove_unspecializer(char *str)
{
	char	*normalized;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	len = normalize_len(str);
	normalized = malloc(sizeof(char) * (len + 1));
	if (!normalized)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (*str == '\\')
			str++;
		if (!*str)
			break ;
		normalized[i] = *str;
		str++;
		i++;
	}
	normalized[i] = '\0';
	return (normalized);
}
/*
int	main(int argc, char **argv)
{
	int		len;
	char	*unspecialized;
	char	*normalized;

	if (argc != 3)
		return (0);
	printf("Managing this:\n%s\n%s\n", argv[1], argv[2]);
	len = unspecialized_len(argv[1], argv[2]);
	printf("Len del String: %d\n", len);
	unspecialized = unspecialize_set(argv[1], argv[2]);
	if (!unspecialized)
		return (1);
	printf("String es:\n%s\n", unspecialized);
	len = normalize_len(unspecialized);
	printf("Len del String: %d\n", len);
	normalized = remove_unspecializer(unspecialized);
	if (!normalized)
		return (free(unspecialized), 2);
	printf("String es:\n%s\n", normalized);
	free(normalized);
	free(unspecialized);
}*/

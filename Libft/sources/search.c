/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:55:30 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/23 02:22:14 by mvelazqu         ###   ########.fr       */
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

char	*search_word_in_str(char *word, char *str)
{
	int	i;

	if (!word || !str)
		return (NULL);
	while (*str)
	{
		i = 0;
		while (word[i] && str[i] == word[i])
			i++;
		if (word[i] == '\0')
			return (str);
		str++;
	}
	return (NULL);
}

char	*search_word_in_split(char *word, char **split, int bytes)
{
	int		i;

	if (!word || !split || bytes <= 0)
		return (NULL);
	i = 0;
	while (split[i])
	{
		if (ft_strncmp(word, split[i], bytes) == 0)
			return (split[i]);
		i++;
	}
	return (NULL);
}

char	*search_word_relative(char *word, char *str, int flag, int bytes)
{
	int	i;
	int	j;

	if (!word || !str || bytes <= 0)
		return (NULL);
	if (flag == STR_START)
		if (ft_strncmp(word, str, bytes) == 0)
			return (str);
	if (flag == STR_ANY)
		return (search_word_in_str(word, str));
	if (flag == STR_END)
	{
		i = ft_strlen(str);
		j = ft_strlen(word);
		while (--i >= 0 && --j >= 0 && bytes--)
			if (word[j] != str[i] || j == 0)
				break ;
		if (j == 0 && bytes == 0)
			return (&str[i]);
	}
	return (NULL);
}
	/*int	i;
	int	start;

	if (!word || !str)
		return (NULL);
	if (flag == STR_START && word[0] != str[0])
		return (NULL);
	start = 0;
	while (str[start])
	{
		i = 0;
		while (word[i] && str[start + i] == word[i])
			i++;
		if (flag == STR_START && word[i] == '\0' && start == 0)
			return (str);
		if (flag == STR_END && word[i] == '\0' && str[start + i] == '\0')
			return (&str[start]);
		if (flag == STR_ANY && word[i] == '\0'
			&& start != 0 && str[start + i] != '\0')
			return (&str[start]);
		start++;
	}
	return (NULL);*/
/*
#include <stdio.h>

int	main(void)
{
	char	*str = "/usr/bin/user";
	char	*word = "/bin/";
	char	*found;

	found = search_word_relative(word, str, STR_START);
	printf("found start: \"%s\"\n", found);
	found = search_word_relative(word, str, STR_ANY);
	printf("found _any_: \"%s\"\n", found);
	found = search_word_relative(word, str, STR_END);
	printf("found _end_: \"%s\"\n", found);
}*/

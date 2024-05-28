/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:55:30 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/05/28 16:04:38 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strcmp(char *str1, char *str2)
{
	while (*str1 && *str1 == *str2)
	{
		str2++;
		str1++;
	}
	return ((unsigned char)*str1 - (unsigned char)*str2);
}

char	*search_word_relative(char *word, char *str, int flag)
{
	int	i;
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

char	*search_word_in_split(char *word, char **split)
{
	char	*found;
	int		i;

	if (!word || !split)
		return (NULL);
	i = 0;
	while (split[i])
	{
		found = search_word_in_str(word, split[i]);
		if (found)
			return (found);
		i++;
	}
	return (NULL);
}
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

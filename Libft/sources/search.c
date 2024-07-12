/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:55:30 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/12 11:35:38 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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

static char	*search_word_in_middle(char *word, char *str, int bytes)
{
	int	len;
	int	i;

	if (!str || !str[0] || !str[1])
		return (NULL);
	i = 1;
	len = ft_strlen(str);
	while (i + bytes < len && str[i + 1])
	{
		if (ft_strncmp(word, &str[i], bytes) == 0)
			return (&str[i]);
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
	{
		if (ft_strncmp(word, str, bytes) == 0)
			return (str);
	}
	else if (flag == STR_MIDDLE)
		return (search_word_in_middle(word, str, bytes));
	else if (flag == STR_END)
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
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	char	*start;
	char	*middle;
	char	*end;
	
	if (argc != 3)
		return (0);
	start = search_word_relative(
		argv[1], argv[2], STR_START, ft_strlen(argv[1]));
	middle = search_word_relative(
		argv[1], argv[2], STR_MIDDLE, ft_strlen(argv[1]));
	end = search_word_relative(
		argv[1], argv[2], STR_END, ft_strlen(argv[1]));
	printf("Found Word start in %p: %s\n", start, start);
	printf("Found Word middl in %p: %s\n", middle, middle);
	printf("Found Word  end  in %p: %s\n", end, end);
}*/

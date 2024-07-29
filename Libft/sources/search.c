/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:55:30 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/18 18:42:56 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/libft.h"

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

char	*search_word_in_str(char *word, char *str, int bytes)
{
	int	len;
	int	i;

	if (!word || !str || bytes <= 0)
		return (NULL);
	i = 0;
	len = ft_strlen(str) + 1;
	while (str[i] && i + bytes < len)
	{
		if (ft_strncmp(word, &str[i], bytes) == 0)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

char	*search_word_in_start(char *word, char *str, int bytes)
{
	if (!word || !*word || !str || !*str || bytes <= 0)
		return (NULL);
	if (ft_strncmp(word, str, bytes) == 0)
		return (str);
	return (NULL);
}

char	*search_word_in_middle(char *word, char *str, int bytes)
{
	int	len;
	int	i;

	if (!word || !*word || !str || !str[0] || !str[1] || !str[2] || bytes <= 0)
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

char	*search_word_in_end(char *word, char *str)
{
	int	i;
	int	j;

	if (!word || !*word || !str || !*str)
		return (NULL);
	i = ft_strlen(word);
	j = ft_strlen(str);
	while (i >= 0 && j >= 0)
	{
		if (word[i] != str[j])
			break ;
		i--;
		j--;
	}
	if (i == -1)
		return (&str[++j]);
	return (NULL);
}
/*
int	main(int argc, char **argv)
{
	char	*start;
	char	*middle;
	char	*end;
	
	if (argc != 3)
		return (0);
	start = search_word_in_start(argv[1], argv[2], ft_strlen(argv[1]));
	middle = search_word_in_str(argv[1], argv[2], ft_strlen(argv[1]));
	end = search_word_in_end(argv[1], argv[2]);
	printf("Found Word start in %p: \"%s\"\n", start, start);
	printf("Found Word middl in %p: \"%s\"\n", middle, middle);
	printf("Found Word  end  in %p: \"%s\"\n", end, end);
	start = start;
	middle = middle;
	end = end;
}*/

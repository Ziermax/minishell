/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:56:58 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/03/28 17:07:20 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	count_words(char *str, char c)
{
	int	words;

	words = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
			words += 1;
		while (*str && *str != c)
			str++;
	}
	return (words);
}

static char	*get_word(char **position, char c)
{
	char	*str;
	char	*word;
	int		len;

	len = 0;
	str = *position;
	while (*str && *str == c)
		str++;
	while (str[len] && str[len] != c)
		len++;
	*position = &str[len];
	if (!len)
		return (NULL);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	word[len--] = '\0';
	while (len >= 0)
	{
		word[len] = str[len];
		len--;
	}
	return (word);
}

static void	free_split_char(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	**ft_split_char(char *str, char c)
{
	char	**split;
	int		words;
	int		i;

	if (!str)
		return (NULL);
	words = count_words(str, c);
	split = malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	i = 0;
	while (i < words)
	{
		split[i] = get_word(&str, c);
		if (!split[i++])
			return (free_split_char(split), NULL);
	}
	split[i] = NULL;
	return (split);
}

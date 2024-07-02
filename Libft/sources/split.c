/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:24:52 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/22 20:21:20 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static	char	*next_simple_word(char *str)
{
	if (!str)
		return (NULL);
	while (*str && !ft_isspace(*str))
		str++;
	return (str);
}

char	**ft_split(char *str)
{
	return (ultra_split(str, skip_spaces, next_simple_word));
}

static int	count_words_char(char *str, char *separator)
{
	int	words;

	words = 0;
	while (*str)
	{
		while (*str && ft_strchr(separator, *str))
			str++;
		if (!*str)
			return (words);
		words++;
		while (*str && !ft_strchr(separator, *str))
			str++;
	}
	return (words);
}

static char	*get_word_char(char **str, char *separator)
{
	char	*word;
	int		len;
	int		i;

	if (!str || !*str || !separator)
		return (NULL);
	while (**str && ft_strchr(separator, **str))
		*str += 1;
	len = 0;
	while ((*str)[len] && !ft_strchr(separator, (*str)[len]))
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = -1;
	while (++i < len)
		word[i] = (*str)[i];
	word[i] = '\0';
	*str = &(*str)[i];
	return (word);
}

char	**ft_split_char(char *str, char *separator)
{
	char	**split;
	int		words;
	int		i;

	if (!str)
		return (NULL);
	words = count_words_char(str, separator);
	split = malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	i = 0;
	while (i < words)
	{
		split[i] = get_word_char(&str, separator);
		if (!split[i++])
			return (free_split(split), NULL);
	}
	split[i] = NULL;
	return (split);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:07:00 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/03/31 14:37:50 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	count_word(char *str)
{
	int	words;

	words = 0;
	while (*str)
	{
		while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
			str++;
		if (*str)
			words += 1;
		while (*str && *str != ' ' && (*str < '\t' || *str > '\r'))
			str++;
	}
	return (words);
}

static char	*copy_word(char **position)
{
	char	*str;
	char	*word;
	int		len;

	len = 0;
	str = *position;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	while (str[len] && str[len] != ' ' && (str[len] < '\t' || str[len] > '\r'))
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

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	free_split_save(char **split, char *save)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		if (split[i] != save)
			free(split[i]);
		i++;
	}
	free(split);
}
// printf("SAVE FREE %p\n", split[i]);

char	**ft_split(char *str)
{
	char	**split;
	int		words;
	int		i;

	if (!str)
		return (NULL);
	words = count_word(str);
	split = malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	i = 0;
	while (i < words)
	{
		split[i] = copy_word(&str);
		if (!split[i++])
			return (free_split(split), NULL);
	}
	split[i] = NULL;
	return (split);
}

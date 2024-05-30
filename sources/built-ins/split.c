/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corte.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:33:23 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/30 19:50:36 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static int	ft_count_words(const char *str, char c)
{
	int	num_words;
	int	new_word;

	num_words = 0;
	new_word = 0;
	while (*str)
	{
		if (*str != c && new_word == 0)
		{
			new_word = 1;
			num_words++;
		}
		else if (*str == c)
			new_word = 0;
		str++;
	}
	return (num_words);
}

static char	*ft_make_str(const char *str, int first, int last)
{
	char	*r;
	int		i;

	i = 0;
	r = malloc((last - first + 1) * sizeof(char));
	if (!r)
		return (NULL);
	while (first < last)
	{
		r[i] = str[first];
		i++;
		first++;
	}
	r[i] = '\0';
	return (r);
}

static char	**ft_free(char **r)
{
	int	i;

	i = 0;
	while (r[i])
	{
		free(r[i]);
		i++;
	}
	free(r);
	return (NULL);
}

char	**split(char *s, char c)
{
	int		i;
	size_t	j;
	int		index_word;
	char	**r;

	r = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!r || !s)
		return (0);
	i = -1;
	j = 0;
	index_word = -1;
	while (++i <= (int)strlen(s))
	{
		if (s[i] != c && index_word < 0)
			index_word = i;
		else if ((s[i] == c || (size_t)i == strlen(s)) && index_word >= 0)
		{
			r[j++] = ft_make_str(s, index_word, i);
			if (!r[j - 1])
				return (ft_free(r));
			index_word = -1;
		}
	}
	r[j] = NULL;
	return (r);
}

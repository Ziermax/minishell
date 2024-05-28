/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:24:52 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/05/28 13:41:22 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*skip_spaces(char *str)
{
	if (!str)
		return (NULL);
	while (ft_isspace(*str))
		str++;
	return (str);
}

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

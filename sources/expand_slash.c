/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_slash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:42:58 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/15 20:09:48 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/expand.h"

static char	*remove_process(char *str, void *keep, char *normalize, int *i)
{
	if (*str == '\\' && !*(str + 1))
		str++;
	else if (*str == '\\' && ft_strchr(keep, *(str + 1)))
	{
		normalize[(*i)++] = *(str++);
		normalize[(*i)++] = *(str++);
	}
	else if (*str == '\\' && !ft_strchr(keep, *(str + 1)))
	{
		str++;
		normalize[(*i)++] = *(str++);
	}
	else
		normalize[(*i)++] = *(str++);
	return (str);
}

char	*remove_slash(char *str, void *keep)
{
	char	*normalize;
	char	*ret_normalize;
	int		i;

	if (!str || !keep)
		return (NULL);
	normalize = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!normalize)
		return (NULL);
	i = 0;
	while (*str)
		str = remove_process(str, keep, normalize, &i);
	normalize[i] = '\0';
	ret_normalize = ft_strdup(normalize);
	free(normalize);
	return (ret_normalize);
}

static char	*add_process(char *str, void *keep, char *slashed, int *i)
{
	if (*str == '\\' && !*(str + 1))
		str++;
	else if (*str == '\\' && ft_strchr(keep, *(str + 1)))
	{
		slashed[(*i)++] = *(str++);
		slashed[(*i)++] = *(str++);
	}
	else if (*str == '\\' && *(str + 1) == '\\')
	{
		slashed[(*i)++] = *(str++);
		slashed[(*i)++] = *(str++);
	}
	else if (ft_strchr(keep, *str))
	{
		slashed[(*i)++] = '\\';
		slashed[(*i)++] = *(str++);
	}
	else
		slashed[(*i)++] = *(str++);
	return (str);
}

char	*add_slash(char *str, void *keep)
{
	char	*slashed;
	char	*ret_slashed;
	int		i;

	if (!str || !keep)
		return (NULL);
	slashed = malloc((ft_strlen(str) * 2 + 1) * sizeof(char));
	if (!slashed)
		return (NULL);
	i = 0;
	while (*str)
		str = add_process(str, keep, slashed, &i);
	slashed[i] = '\0';
	ret_slashed = ft_strdup(slashed);
	free(slashed);
	return (ret_slashed);
}

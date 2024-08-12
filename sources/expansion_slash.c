/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_slash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:42:58 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/12 13:23:09 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/expand.h"
/*
static int	slash_remove_len(char *str, char *keep)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		if (!str[i])
			break ;
		if (ft_strchr(keep, str[i]))
			len++;
		len++;
		i++;
	}
	return (len);
}

static int	slash_add_len(char *str, char *keep)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' || ft_strchr(keep, str[i]))
		{
			i += 2;
			len += 2;
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	*remove_slash(char *str, char *keep)
{
	char	*normalize;
	int		i;
	int		len;

	if (!str || !keep)
		return (NULL);
	len = slash_remove_len(str, keep);
	normalize = malloc((len + 1) * sizeof(char *));
	if (!normalize)
		return (NULL);
	i = 0;
	while (*str && i < len)
	{
		if (*str == '\\')
			str++;
		if (!*str)
			break ;
		if (i < len)
			normalize[i++] = *(str++);
	}
	normalize[i] = '\0';
	return (normalize);
}*/

static char	*add_process(char *str, char *keep, char *slashed, int *i)
{
	if (*str == '\\' && !*(str + 1))
		str++;
	else if (*str == '\\' && ft_strchr(keep, *(str + 1)))
	{
		slashed[(*i)++] = *(str++);
		slashed[(*i)++] = *(str++);
	}
	else if (*str == '\\' && !ft_strchr(keep, *(str + 1)))
	{
		str++;
		slashed[(*i)++] = *(str++);
	}
	else if (*str == '\\' && *(str + 1) == '\\')
	{
		slashed[(*i)++] = '\\';
		str += 2;
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

char	*add_slash(char *str, char *keep)
{
	char	*slashed;
	char	*m_slashed;
	int		i;

	if (!str || !keep)
		return (NULL);
	slashed = malloc(ft_strlen(str) * 2 * sizeof(char));
	if (!slashed)
		return (NULL);
	i = 0;
	while (*str)
		str = add_process(str, keep, slashed, &i);
	slashed[i] = '\0';
	m_slashed = ft_strdup(slashed);
	free(slashed);
	return (m_slashed);
}

/*#include <stdio.h>

int	main(int ac, char **av)
{
	char *str1;

	if (ac != 3)
		return (1);
	printf("BFR: %s\n", av[1]);
	str1 = add_slash(av[1], av[2]);
	printf("ADD: %s\n", str1);
	free(str1);
	return (0);
}*/

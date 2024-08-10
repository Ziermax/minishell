/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_slash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:42:58 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/10 19:11:03 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/expand.h"

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
		if (ft_strchr(keep, *str))
			normalize[i++] = *(str++);
		if (*str == '\\')
			str++;
		if (!*str)
			break ;
		if (ft_strchr(keep, *str))
			normalize[i++] = '\\';
		if (i < len)
			normalize[i++] = *(str++);
	}
	normalize[i] = '\0';
	return (normalize);
}

char	*add_slash(char *str, char *keep)
{
	char	*slashed;
	int		i;

	if (!str || !keep)
		return (NULL);
	if (!keep[0] || !str[0])
		return (ft_strdup(str));
	slashed = malloc((slash_add_len(str, keep) + 1) * sizeof(char));
	i = 0;
	while (*str)
	{
		if (*str == '\\')
		{
			slashed[i++] = *(str++);
			slashed[i++] = *(str++);
		}
		else
		{
			if (ft_strchr(keep, *str))
				slashed[i++] = '\\';
			slashed[i++] = *(str++);
		}
	}
	slashed[i] = '\0';
	return (slashed);
}

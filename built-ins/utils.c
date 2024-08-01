/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:38:28 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/01 14:41:41 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_utils.h"
#include "../Libft/includes/libft.h"

char	*put_quots(char *s)
{
	char	*new;
	int		i;
	int		j;
	int		equal;

	if (!s)
		return (NULL);
	new = ft_calloc(ft_strlen(s) + 3, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	equal = 0;
	while (s[i])
	{
		new[j++] = s[i];
		if (s[i++] == '=' && !equal)
		{
			new[j++] = '\"';
			equal = 1;
		}
	}
	if (equal)
		new[j] = '\"';
	return (new);
}

char	*get_var(char *s)
{
	char	*var;
	int		i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (s[i] != '=')
		return (ft_strdup(s));
	var = ft_calloc(i + 1, sizeof(char));
	if (!var)
		return (NULL);
	i = 0;
	while (s[i] != '=' && s[i] != '+')
	{
		var[i] = s[i];
		i++;
	}
	return (var);
}

int	check_var(char **s, char *var)
{
	int	i;
	int	len;

	if (!var || !s || !*s)
		return (-1);
	len = ft_strlen(var);
	i = 0;
	while (s[i])
	{
		if (!ft_strncmp(s[i], var, len))
			return (i);
		i++;
	}
	return (-1);
}

int	get_index_var(char **var, char *to_find)
{
	int		i;
	char	*name;

	i = 0;
	while (var[i])
	{
		name = get_var();
		if (!name)
			return (-1);
		if (!ft_strncmp(name, to_find, ft_strlen(name)))
		{
			free(name);
			return (i);
		}
		free(name);
		i++;
	}
	return (-1);
}

char	*ft_itoa_brackets(int n)
{
	int		len;
	char	*num;

	len = ft_intlen(n);
	num = ft_calloc(len + 3, sizeof(char));
	if (!num)
		return (NULL);
	num[0] = '[';
	while (len > 0)
	{
		num[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	num[len + 2] = ']';
	return (num);
}

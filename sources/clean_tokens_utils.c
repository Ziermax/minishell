/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:35:37 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/18 16:31:25 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/token.h"

int	ft_isvarchar(int c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*next_var(char *str)
{
	if (*str == '$'
		&& ((ft_isvarchar(str[1]) && !ft_isdigit(str[1])) || str[1] == '?'))
	{
		str++;
		if (*str == '?')
			return (str + 1);
		while (ft_isvarchar(*str))
			str++;
		return (str);
	}
	while (*str)
	{
		if (*str == '$'
			&& ((ft_isvarchar(str[1]) && !ft_isdigit(str[1])) || str[1] == '?'))
			break ;
		str++;
	}
	return (str);
}
/*
	is_var = false;
	if (*str == '$' && ft_isvarchar(str[1]) && !ft_isdigit(str[1]))
		is_var = true;
	if (is_var && *(++str)== '?')
		return (str + 1);
	if (is_var && ft_isvarchar(*str))
	{
		while (ft_is
	}
}*/

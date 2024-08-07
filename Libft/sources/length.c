/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:09:23 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/31 18:13:57 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_splitlen(char **split)
{
	int	len;
	int	i;

	if (!split || !*split)
		return (0);
	len = 0;
	i = -1;
	while (split[++i])
		len += ft_strlen(split[i]);
	return (len);
}

int	ft_intlen(int nbr)
{
	int	len;

	if (!nbr)
		return (1);
	len = 0;
	while (nbr)
	{
		len++;
		nbr = nbr / 10;
	}
	return (len);
}

int	ft_arraylen(void *array)
{
	int		len;

	if (!array || !*(void **)array)
		return (0);
	len = 0;
	while (((void **)array)[len])
		len++;
	return (len);
}

int	get_length_array(char *var)
{
	int	i;
	int	length;

	i = 0;
	while (var[i] != '(')
		i++;
	i++;
	length = 0;
	while (var[i] != ')')
	{
		if (var[i] != ' ' && var[i] != '\t')
		{
			while (var[i] != ' ' && var[i] != '\r' && var[i] != ')')
				i++;
			length++;
		}
		while (var[i] == ' ' || var[i] == '\t')
			i++;
	}
	return (length);
}

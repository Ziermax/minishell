/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:51:40 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/02 18:56:08 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*xp_next_string(char *str)
{
	int		quote;
	char	*aux;

	if (!str)
		return (NULL);
	aux = str;
	quote = 0;
	if (*str == '\"' || *str == '\'')
		quote = *str++;
	if (quote == '\"')
		while (*str && !(*str == '\"' && aux != str && *(str - 1) != '\\'))
			str++;
	else if (quote == '\'')
		while (*str && !(*str == '\'' && aux != str && *(str - 1) != '\\'))
			str++;
	else
		while (*str && !((*str == '\'' || *str == '\"') 
				&& aux != str && *(str - 1) != '\\'))
			str++;
	if (quote && (*str == '\'' || *str == '\"'))
		str++;
	return (str);
}

char	**remove_quotes(char **split_str)
{
	char	*tmp;
	int		len;
	int		i;

	if (!split_str)
		return (NULL);
	i = -1;
	while (split_str[++i])
	{
		if (!split_str[i])
			break ;
		if (split_str[i][0] != '\'' && split_str[i][0] != '\"')
			continue ;
		len = ft_strlen(split_str[i]);
		if (split_str[i][len - 1] == '\'' || split_str[i][len - 1] == '\"')
			split_str[i][len - 1] = '\0';
		tmp = ft_substr(split_str[i], 1, len);
		if (!tmp)
			return (free_split(split_str), NULL);
		free(split_str[i]);
		split_str[i] = tmp;
	}
	return (split_str);
}
/*
int	main(int argc, char **argv)
{
	char	*str;

	if (argc != 2)
		return (0);
	str = argv[1];
	printf("str: %s\n\n", str);
	str = xp_next_string(str);
	printf("str: %s\n\n", str);
	str = xp_next_string(str);
	printf("str: %s\n\n", str);
	str = xp_next_string(str);
	printf("str: %s\n\n", str);
	str = xp_next_string(str);
	printf("str: %s\n\n", str);
	str = xp_next_string(str);
	printf("str: %s\n\n", str);
}*/

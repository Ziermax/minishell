/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:45:59 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/27 20:03:27 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

void	print_env(char *envp[])
{
	while (*envp)
	{
		write(1, *envp, strlen(*envp));
		write(1, "\n", 1);
		envp++;
	}
}

void	print_pwd(void)
{
	char	buf[1020];

	printf("%s\n", getcwd(buf, 1024));
}


void	print_echo(char **s)
{
	int	newline;
	int	i;

	newline = 1;
	while ((*s)[0] == '-')
	{
		i = 1;
		while ((*s)[i] == 'n')
			i++;
		if ((*s)[i])
			break ;
		newline = 0;
		s++;
	}
	while (*s)
	{
		printf("%s", *s);
		s++;
		if (*s)
			printf(" ");
	}
	if (newline)
		printf("\n");
}

void	ft_exit(void)
{
	exit(1);
}

int main(int argc, char *argv[], char *envp[])
{
	//print_pwd();
	//print_env(envp);
	//print_echo(argv + 2);
	//ft_cd();
	//ft_unset(envp);
	//ft_export(envp);
	ft_exit();
}

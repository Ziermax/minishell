/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:27:44 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/30 20:29:47 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void	handle_sigint(int sig)
{
	printf("\nSe recibió la señal SIGINT (Ctrl-C).\n");
	exit(0);
}

int	main(void)
{
	signal(SIGINT, handle_sigint);
	while (1)
	{
		printf("Programa en ejecución. Presiona Ctrl-C para salir.\n");
		sleep(1);
	}
	return (0);
}

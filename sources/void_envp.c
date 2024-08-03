/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   void_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:58:43 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/02 19:02:39 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**make_envp()
{


}

void	void_env(t_data *data)
{
	data->envp = make_envp();
	data->exp = make_exp();
}

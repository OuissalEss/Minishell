/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:42:00 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/05 09:24:57 by slaajour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// if there is a lot of pipes exit should return 

void	do_exit(void)
{
	t_cmd	*head;

	head = g_data->commands;
	if (!head->arguments[1])
	{
		printf("exit\n");
		exit(0);
	}
}

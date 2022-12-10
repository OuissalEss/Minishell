/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 12:44:57 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/10 12:45:00 by slaajour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	exit_status(void)
{
	if (g_data->exit_status == 2)
	{
		g_data->exit_status = 1;
		return (0);
	}
	return (1);
}

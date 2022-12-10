/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:21:32 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/10 06:06:35 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	do_env(t_cmd *cmd)
{
	t_env	*head;

	head = g_data->env;
	while (head)
	{
		if (head->var && head->value)
		{
			ft_putstr_fd(head->var, cmd->outfile);
			ft_putstr_fd("=", cmd->outfile);
			ft_putstr_fd(head->value, cmd->outfile);
			ft_putstr_fd("\n", cmd->outfile);
		}
		head = head->next_var;
	}
}

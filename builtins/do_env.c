/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:21:32 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/03 18:44:21 by slaajour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../execution.h"

void	do_env(void)
{
	t_env	*head;

	head = g_data->env;
	while (head)
	{
		if (head->var && head->value && ft_strcmp(head->value, ""))
		{
			ft_putstr(head->var);
			printf("=");
			ft_putstr(head->value);
			printf("\n");
		}
		head = head->next_var;
	}
}

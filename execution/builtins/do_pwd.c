/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:20:22 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/11 02:22:57 by slaajour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	do_pwd(t_cmd *cmd)
{
	t_env	*head;

	head = g_data->env;
	while (head)
	{
		if (ft_strcmp("PWD", head->var) == 1)
		{
			if (getcwd(NULL, 0) != NULL)
				head->value = getcwd(NULL, 0);
			ft_putstr_fd(head->value, cmd->outfile);
			ft_putstr_fd("\n", cmd->outfile);
		}
		head = head->next_var;
	}
}

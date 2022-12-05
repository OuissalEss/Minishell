/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:20:22 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/02 16:31:22 by slaajour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../execution.h"

void	do_pwd(void)
{
	t_env	*head;

	head = g_data->env;
	while (head)
	{
		if (ft_strcmp("PWD", head->var) == 1)
		{	
			head->value = getcwd(NULL, 0);
			printf("%s\n", head->value);
		}
		head = head->next_var;
	}
}

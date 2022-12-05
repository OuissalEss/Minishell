/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:19:15 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/05 09:17:27 by slaajour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../execution.h"

int	str_search(char *str)
{
	int	i;

	if (str[0] != '-' || (str[0] == '-' && str[1] == '\0'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (2);
		i++;
	}
	return (1);
}

void	do_echo(void)
{
	int		i;
	int		oneorzero;
	t_cmd	*head;

	oneorzero = 0;
	head = g_data->commands;
	if (head->arguments[1])
	{
		if (str_search(head->arguments[1]) == 1)
			oneorzero = 1;
		i = 1;
		while (head->arguments[i] && str_search(head->arguments[i]) == 1)
			i++;
		while (head->arguments[i])
		{
			ft_putstr(head->arguments[i]);
			if (head->arguments[i + 1])
				printf(" ");
			i++;
		}
	}
	if (oneorzero != 10)
		printf("\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:19:15 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/10 06:06:38 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	do_echo(t_cmd *cmd)
{
	int		i;
	int		oneorzero;

	oneorzero = 0;
	if (cmd->arguments[1])
	{
		if (str_search(cmd->arguments[1]) == 1)
			oneorzero = 1;
		i = 1;
		while (cmd->arguments[i] && str_search(cmd->arguments[i]) == 1)
			i++;
		while (cmd->arguments[i])
		{
			ft_putstr_fd(cmd->arguments[i], cmd->outfile);
			if (cmd->arguments[i + 1])
				ft_putstr_fd(" ", cmd->outfile);
			i++;
		}
	}
	if (oneorzero != 1)
		ft_putstr_fd("\n", cmd->outfile);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:42:00 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/11 02:24:57 by slaajour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	previous_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*cmnds;

	cmnds = g_data->commands;
	i = 0;
	while (cmnds)
	{
		if (cmnds == cmd && i == 0)
			return (0);
		cmnds = cmnds->next_cmd;
		i++;
	}
	return (1);
}

int	is_num(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	is_valid_arg(t_cmd *head, char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!is_num(arg[i]))
		{
			if (previous_cmd(head) == 0 && !(head->next_cmd))
				ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("Minishell: exit: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (255);
		}
		i++;
	}
	return (0);
}

int	exit_test(t_cmd *head)
{
	if (previous_cmd(head) == 0 && !(head->next_cmd))
		ft_putstr_fd("exit\n", 1);
	if ((long long)atoi(head->arguments[1]) > 9223372036854775807)
		return (255);
	else
		return (atoi(head->arguments[1]));
}

int	do_exit(t_cmd *head)
{
	int	i;

	i = 1;
	if (!head->arguments[1])
	{
		if (previous_cmd(head) == 0 && !(head->next_cmd))
			ft_putstr_fd("exit\n", 1);
		return (0);
	}
	while (head->arguments[i])
	{
		if (is_valid_arg(head, head->arguments[i]) != 0)
			return (255);
		i++;
	}
	if (i > 2)
	{
		if (previous_cmd(head) == 0 && !(head->next_cmd))
			ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		return (2);
	}
	else
		return (exit_test(head));
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:50:32 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/27 13:40:37 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parsing.h"

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*l;

	l = *lst;
	if (l)
	{
		while (l->next_var)
			l = l->next_var;
		l->next_var = new;
	}
	else
		*lst = new;
}

void	cmd_add_back(t_cmd *new)
{
	t_cmd	*l;

	l = g_data->commands;
	if (l)
	{
		while (l->next_cmd)
			l = l->next_cmd;
		l->next_cmd = new;
	}
	else
		g_data->commands = new;
}

t_cmd	*cmd_get_last(t_cmd *lst)
{
	if (lst)
	{
		while (lst->next_cmd)
			lst = lst->next_cmd;
	}
	return (lst);
}

void	red_add_back(t_red **r, t_red *new)
{
	t_red	*l;

	l = *r;
	if (l)
	{
		while (l->next)
			l = l->next;
		l->next = new;
	}
	else
		*r = new;
}

void	add_cmd(void)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	command->cmd_name = NULL;
	command->arguments = NULL;
	command->infile = 0;
	command->outfile = 1;
	command->red = NULL;
	command->next_cmd = NULL;
	cmd_add_back(command);
}

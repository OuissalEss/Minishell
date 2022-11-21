/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:50:32 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/21 10:50:33 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

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

t_cmd	*get_last(t_cmd *lst)
{
	if (lst)
	{
		while (lst->next_cmd)
			lst = lst->next_cmd;
	}
	return (lst);
}

void	hdoc_add_back(t_heredoc **lst, t_heredoc *new)
{
	t_heredoc	*l;

	l = *lst;
	if (l)
	{
		while (l->next)
			l = l->next;
		l->next = new;
	}
	else
		*lst = new;
}

int	add_heredoc(char *str, int i)
{
	t_cmd		*last;
	t_heredoc	*hd;

	last = get_last(g_data->commands);
	hd = malloc(sizeof(t_heredoc));
	hd->dlmt = get_name(str, &i);
	hd->dlmt = remove_quotes(hd->dlmt);
	hd->next = NULL;
	hdoc_add_back(&(last->hdoc), hd);
	return (i);
}

void	add_cmd(void)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	command->cmd_name = NULL;
	command->arguments = NULL;
	command->infile = 0;
	command->outfile = 1;
	command->hdoc = NULL;
	command->next_cmd = NULL;
	cmd_add_back(command);
}

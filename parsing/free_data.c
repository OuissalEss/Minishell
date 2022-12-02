/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:22:30 by oessamdi          #+#    #+#             */
/*   Updated: 2022/12/02 15:21:08 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parsing.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
}

void	free_red(t_red *red)
{
	t_red	*r;
	t_red	*tmp;

	r = red;
	while (r)
	{
		if (r->file_name)
			free(r->file_name);
		r->file_name = NULL;
		if (r->arr)
			free(r->arr);
		r->arr = NULL;
		tmp = r;
		r = r->next;
		free(tmp);
		tmp = NULL;
	}
}

void	free_data(void)
{
	t_cmd	*cmd;

	cmd = g_data->commands;
	while (cmd)
	{
		g_data->commands = g_data->commands->next_cmd;
		if (cmd->infile != 0)
			close(cmd->infile);
		if (cmd->outfile != 1)
			close(cmd->outfile);
		free(cmd->cmd_name);
		cmd->cmd_name = NULL;
		free_red(cmd->red);
		free_args(cmd->arguments);
		if (cmd->arguments != NULL)
			free(cmd->arguments);
		cmd->arguments = NULL;
		free(cmd);
		cmd = NULL;
		cmd = g_data->commands;
	}
	g_data->commands = NULL;
}

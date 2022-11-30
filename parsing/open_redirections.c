/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 07:28:15 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/29 08:24:29 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parsing.h"

int	open_files(t_red *r)
{
	int	fd;

	fd = -1;
	if (r->type == 4)
	{
		fd = open(r->file_name, O_RDONLY, 0644);
		if (fd > 0)
			r->fd[0] = fd;
	}
	else
	{
		if (r->type == 1)
			fd = open(r->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (r->type == 2)
			fd = open(r->file_name, O_WRONLY | O_CREAT, 0644);
		if (fd > 0)
			r->fd[1] = fd;
	}
	if (fd < 0)
	{
		printf("%s\n", strerror(errno));
		return (-1);
	}
	return (0);
}

void	write_in_file(char *str, t_red *r)
{
	int		*arr;
	char	*tmp;

	arr = malloc(sizeof(int) * strlen(str));
	set_arr(str, &arr);
	tmp = str;
	if (r->expand == 0)
		tmp = handle_expansion(&str, &arr);
	printf("%s\n", tmp);
	if (r->expand == 0)
		free(tmp);
	tmp = NULL;
}

int	open_hdoc(t_red *r)
{
	char	*str;

	if (pipe(r->fd) < 0)
	{
		printf("%s\n", strerror(errno));
		return (-1);
	}
	dup2(r->fd[1], 1);
	while (1)
	{
		str = readline(">");
		if (strcmp(str, r->file_name) == 0)
			break ;
		else
			write_in_file(str, r);
		if (str != NULL)
			free(str);
		str = NULL;
	}
	close(r->fd[1]);
	return (0);
}

void	set_red(t_cmd *cmd)
{
	t_red	*r;

	r = cmd->red;
	while (r)
	{
		if (r->type == 3 || r->type == 4)
		{
			if (cmd->infile != 0)
				close(cmd->infile);
			cmd->infile = r->fd[0];
		}
		else if (r->type == 1 || r->type == 2)
		{
			if (cmd->outfile != 1)
				close(cmd->outfile);
			cmd->outfile = r->fd[1];
		}
		r = r->next;
	}
}

int	open_all_files(t_red *r)
{
	while (r)
	{
		if (open_files(r) == -1)
			return (-1);
		r = r->next;
	}
	return (0);
}

int	open_red(void)
{
	t_cmd	*cmd;
	t_red	*r;

	cmd = g_data->commands;
	while (cmd)
	{
		r = cmd->red;
		while (r)
		{
			if (r->type == 3)
				if (open_hdoc(r) == -1)
					return (-1);
			r = r->next;
		}
		cmd = cmd->next_cmd;
	}
	cmd = g_data->commands;
	while (cmd)
	{
		if (open_all_files(cmd->red) == -1)
			return (-1);
		set_red(cmd);
		cmd = cmd->next_cmd;
	}
	return (0);
}

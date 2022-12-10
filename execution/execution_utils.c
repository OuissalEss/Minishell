/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 12:45:58 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/10 12:46:00 by slaajour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp("cd", cmd) || ft_strcmp("echo", cmd)
		|| ft_strcmp("env", cmd) || ft_strcmp("pwd", cmd)
		|| ft_strcmp("export", cmd) || ft_strcmp("unset", cmd)
		|| ft_strcmp("exit", cmd))
		return (1);
	return (0);
}

int	lst_size(t_env *env)
{
	int	c;

	c = 0;
	while (env)
	{
		c++;
		env = env->next_var;
	}
	return (c);
}

int	ft_pipe(t_cmd *cmd)
{
	int	fd[2];

	if (pipe(fd) < 0)
		return (1);
	if (cmd->outfile == 1)
		cmd->outfile = fd[1];
	else
		close(fd[1]);
	if (cmd->next_cmd->infile == 0)
		cmd->next_cmd->infile = fd[0];
	else
		close(fd[0]);
	return (0);
}

int	previous(t_cmd *cmd)
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

void	wait_for_proccess(void)
{
	int	statval;

	statval = 0;
	while (wait(&statval) > 0)
		if (WIFEXITED(statval))
			g_data->exit_status = WEXITSTATUS(statval);
}

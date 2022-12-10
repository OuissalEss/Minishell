/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_executing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 12:43:36 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/10 12:43:38 by slaajour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	builtins(t_cmd *cmd)
{
	char	*str;

	str = cmd->cmd_name;
	if (ft_strcmp("echo", str))
		do_echo(cmd);
	else if (ft_strcmp("env", str))
		do_env(cmd);
	else if (ft_strcmp("cd", str))
		return (do_cd(cmd));
	else if (ft_strcmp("pwd", str))
		do_pwd(cmd);
	else if (ft_strcmp("export", str))
		return (do_export(cmd));
	else if (ft_strcmp("unset", str))
		return (do_unset(cmd));
	else if (ft_strcmp("exit", str))
		return (do_exit(cmd));
	return (0);
}

char	**env_array(t_env *env)
{
	int		i;
	int		x;
	char	**envp;

	envp = malloc(sizeof(char *) * (lst_size(env) + 1));
	x = 0;
	while (x < (lst_size(env) + 1))
		envp[x++] = NULL;
	x = 0;
	while (env)
	{
		i = 0;
		while (env->var[i])
			envp[x] = ft_charjoin(envp[x], env->var[i++]);
		i = 0;
		if (env->value)
			envp[x] = ft_charjoin(envp[x], '=');
		while (env->value && env->value[i])
			envp[x] = ft_charjoin(envp[x], env->value[i++]);
		env = env->next_var;
		x++;
	}
	envp[x] = NULL;
	return (envp);
}

void	call_execve(t_cmd *cmd)
{
	char	*tmp;

	if (cmd->outfile != 1)
	{
		if (cmd->next_cmd)
			close(cmd->next_cmd->infile);
		dup2(cmd->outfile, 1);
	}
	if (cmd->infile != 0)
	{
		dup2(cmd->infile, 0);
	}
	tmp = cmd->cmd_name;
	cmd->cmd_name = check_path(cmd->cmd_name);
	if (tmp)
		free(tmp);
	tmp = NULL;
	if (execve(cmd->cmd_name, cmd->arguments, env_array(g_data->env)) < 0)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd->arguments[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
}

int	execute(t_cmd *cmd)
{
	g_data->child_process = fork();
	if (g_data->child_process == 0)
	{
		if (is_builtin(cmd->cmd_name) == 1)
			exit(builtins(cmd));
		else
			call_execve(cmd);
	}
	else
	{
		if (cmd->outfile != 1)
			close(cmd->outfile);
		if (cmd->infile != 0)
			close(cmd->infile);
	}
	return (0);
}

void	start_executing(void)
{
	t_cmd	*cmd;

	cmd = g_data->commands;
	while (cmd)
	{
		if (is_builtin(cmd->cmd_name) == 1 && !(cmd->next_cmd)
			&& previous(cmd) == 0)
		{
			g_data->exit_status = builtins(cmd);
			if (ft_strcmp(cmd->cmd_name, "exit") && exit_status() == 1)
				exit(g_data->exit_status);
		}
		else
		{
			if (cmd->next_cmd)
			{
				if (ft_pipe(cmd))
					return (ft_putstr_fd(strerror(errno), 2));
			}
			execute(cmd);
		}
		cmd = cmd->next_cmd;
	}
	wait_for_proccess();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:11:55 by slaajour          #+#    #+#             */
/*   Updated: 2022/12/05 08:42:43 by slaajour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../execution.h"

void	builtins(void)
{
	char	*str;

	str = g_data->commands->cmd_name;
	if (ft_strcmp("echo", str))
		do_echo();
	else if (ft_strcmp("env", str))
		do_env();
	else if (ft_strcmp("cd", str))
		do_cd();
	else if (ft_strcmp("pwd", str))
		do_pwd();
	else if (ft_strcmp("export", str))
		do_export();
	else if (ft_strcmp("unset", str))
		do_unset();
	else if (ft_strcmp("exit", str))
		do_exit();
}

void	start_executing(void)
{
	char	*str;
	int		i;

	i = 0;
	str = g_data->commands->cmd_name;
	if (ft_strcmp("cd", str) || ft_strcmp("echo", str)
		|| ft_strcmp("env", str) || ft_strcmp("pwd", str)
		|| ft_strcmp("export", str) || ft_strcmp("unset", str)
		|| ft_strcmp("exit", str))
		builtins();
	else
		printf("Minishell: %s: command not found\n", str);
}
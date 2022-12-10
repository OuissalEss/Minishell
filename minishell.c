/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:48:55 by oessamdi          #+#    #+#             */
/*   Updated: 2022/12/10 06:42:46 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/parsing.h"
#include "parsing/check_error/check_error.h"
#include <readline/history.h>
#include <readline/readline.h>

int	exist(char **s)
{
	int		i;
	int		r;
	char	*str;

	i = 0;
	str = expand_dollar(*s);
	if (str == NULL)
	{
		printf("exit\n");
		g_data->exit_status = 0;
		exit (0);
	}
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	r = 1;
	if (str[i] == '\0')
		r = -1;
	free(str);
	str = NULL;
	return (r);
}

void	env(void)
{
	t_env	*tmp;

	tmp = g_data->env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->var, tmp->value);
		tmp = tmp->next_var;
	}
}

void	handle_sigint(int sig)
{
	(void) sig;
	if (g_data->child_process != 0 && !kill(g_data->child_process, SIGKILL))
	{
		g_data->exit_status = 130;
		write(1, "\n", 1);
	}
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		//rl_replace_line("", STDIN_FILENO);
		rl_redisplay();
		g_data->exit_status = 1;
	}
	g_data->child_process = 0;
}

void	handle_sigquit(int sig)
{
	(void) sig;
	if (g_data->child_process != 0 && !kill(g_data->child_process, SIGKILL))
	{
		printf("Quit: 3\n");
		g_data->exit_status = 131;
	}
	g_data->child_process = 0;
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	char			*str;

	(void) argc;
	(void) argv;
	init_data(envp);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	while (1)
	{
		str = readline("my prompt > ");
		add_history(str);
		if (exist(&str) == 1 && check_error(str) == 1)
		{
			start_parsing(str);
			start_executing();
			free_data();
		}
		if (str)
			free(str);
		str = NULL;
	}
	return (0);
}

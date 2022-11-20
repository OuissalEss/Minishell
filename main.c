#include "minishell.h"
#include "parsing.h"

int	exist(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		g_data->exit_status = 0;
		exit (0);
	}
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (-1);
	return (1);
}

void	free_data(void)
{
	t_cmd	*cmd;

	cmd = g_data->commands;
	while (cmd)
	{
		g_data->commands = g_data->commands->next_cmd;
		free(cmd->cmd_name);
		free(cmd->arguments);
		cmd = g_data->commands;
	}
	g_data->commands = NULL;
}

void	print(void)
{
	int			i;
	t_cmd		*lst;
	t_heredoc	*hlst;

	lst = g_data->commands;
	while (lst)
	{
		printf("cmd = %s\n", lst->cmd_name);
		i = 0;
		while (lst->arguments[i])
		{
			printf("args[%d] = %s     ", i, lst->arguments[i]);
			i++;
		}
		printf("\ninfile = %d\n", lst->infile);
		printf("outfile = %d\n", lst->outfile);
		hlst = lst->hdoc;
		while (hlst)
		{
			printf("hdoc = %s      ", hlst->dlmt);
			hlst = hlst->next;
		}
		printf("\n ");
		lst = lst->next_cmd;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	(void) argc;
	(void) argv;
	init_data(envp);
	while (1)
	{
		str = readline("my prompt : ");
		if (exist(str) == 1 && check_error(str) == 1)
		{
			start_parsing(str);
			print();
			free_data();
		}
	}
	return (0);
}

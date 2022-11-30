/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:55:36 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/29 07:30:28 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parsing.h"

void	set_arr(char *str, int **array)
{
	int	*arr;
	int	i;

	arr = *array;
	arr[0] = 0;
	if (str[0] == '\'')
		arr[0] = 1;
	else if (str[0] == '\"')
		arr[0] = 2;
	i = 1;
	while (str[i])
	{
		arr[i] = arr[i - 1];
		if (str[i] == '\'' && arr[i - 1] == 0)
			arr[i] = 1;
		else if (str[i] == '\"' && arr[i - 1] == 0)
			arr[i] = 2;
		else if ((str[i] == '\'' && arr[i - 1] == 1)
			|| (str[i] == '\"' && arr[i - 1] == 2))
			arr[i] = 0;
		i++;
	}
}

char	**allocate_args(char *str, int *arr)
{
	int		i;
	int		c;
	char	**args;

	i = 0;
	c = 1;
	while (str[i])
	{
		if (((str[i] == ' ' || str[i] == '\t') && arr[i] == 0)
			&& (str[i + 1] != ' ' && str[i + 1] != '\t'))
			c++;
		i++;
	}
	args = malloc(sizeof(char *) * (c + 1));
	i = 0;
	while (i < c + 1)
		args[i++] = NULL;
	return (args);
}

void	set_commands(char *str, int *arr)
{
	int		i;
	int	a;
	t_cmd	*last;

	i = 0;
	a = 0;
	last = cmd_get_last(g_data->commands);
	last->arguments = allocate_args(str, arr);
	while (str[i] && ((str[i] == ' ' || str[i] == '\t') && arr[i] == 0))
		i++;
	while (str[i])
	{
		if (((str[i] == ' ' || str[i] == '\t') && arr[i] == 0)
			&& (str[i + 1] != ' ' && str[i + 1] != '\t'))
			a++;
		else
			last->arguments[a] = ft_charjoin(last->arguments[a], str[i]);
		i++;
	}
	if (last->arguments[0] != NULL)
		last->cmd_name = strdup(last->arguments[0]);
}

void	parse(char *cmds)
{
	int		*arr;
	char	*tmp;
	t_cmd	*last;

	arr = malloc(sizeof(int) * strlen(cmds));
	add_cmd();
	last = cmd_get_last(g_data->commands);
	set_arr(cmds, &arr);
	handle_quotes(&cmds, &arr);
	last->red = handle_redirection(&cmds, &arr, last->red);
	tmp = handle_expansion(&cmds, &arr);
	set_commands(tmp, arr);
	free(arr);
	arr = NULL;
	free(tmp);
	tmp = NULL;
}

void	start_parsing(char *str)
{
	int		*arr;
	int		i;
	char	**cmds;

	arr = malloc(sizeof(int) * strlen(str));
	set_arr(str, &arr);
	cmds = split_cmds(str, arr);
	free(arr);
	arr = NULL;
	i = 0;
	while (cmds[i])
		parse(cmds[i++]);
	expand_red();
	printf("aaaaaaaaaaaa\n");
	open_red();
}

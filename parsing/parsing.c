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

#include "parsing.h"
#include "minishell.h"

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

int	add_red(t_red **r, int t, char *str, int *arr)
{
	t_red	*rd;
	int		i;

	i = (t % 2) + 1;
	rd = malloc(sizeof(t_red));
	rd->file_name = NULL;
	rd->file_name = ft_charjoin(rd->file_name, '\0');
	rd->expand = 0;
	while (str[i] && (arr[i] == 0 && (str[i] == ' ' || str[i] == '\t')))
		i++;
	while (str[i] && (arr[i] != 0 || !(str[i] == ' '
				|| str[i] == '\t' || str[i] == '<' || str[i] == '>')))
	{
		if (t == 3 && arr[i] > 0)
			rd->expand = arr[i];
		rd->file_name = ft_charjoin(rd->file_name, str[i]);
		i++;
	}
	rd->fd[0] = -1;
	rd->fd[1] = -1;
	rd->type = t;
	rd->next = NULL;
	red_add_back(r, rd);
	return (i);
}

t_red	*handle_redirection(char **str, int **arr, t_red *red)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[0][i])
	{
		if ((str[0][i] == '<' && str[0][i + 1] == '<') && arr[0][i] == 0)
			i += add_red(&red, 3, &str[0][i], &arr[0][i]);
		else if ((str[0][i] == '>' && str[0][i + 1] == '>') && arr[0][i] == 0)
			i += add_red(&red, 1, &str[0][i], &arr[0][i]);
		else if (str[0][i] == '>' && arr[0][i] == 0)
			i += add_red(&red, 2, &str[0][i], &arr[0][i]);
		else if (str[0][i] == '<' && arr[0][i] == 0)
			i += add_red(&red, 4, &str[0][i], &arr[0][i]);
		else
		{
			str[0][j] = str[0][i];
			arr[0][j] = arr[0][i];
			j++;
		}
		i++;
	}
	str[0][j] = '\0';
	return (red);
}

void	init_var(int *j, char **str, int **arr)
{
	int	j1;

	j1 = *j;
	j1 = 0;
	if (arr[0][0] == 0)
	{
		str[0][0] = str[0][0];
		j1 = 1;
	}
}

void	handle_quotes(char **str, int **arr)
{
	int	i;
	int	j;
	int	*new;

	new = malloc(sizeof(int) * strlen(str[0]));
	init_var(&j, str, arr);
	if (arr[0][0] == 0)
		new[0] = arr[0][0];
	i = 1;
	while (str[0][i] && str[0][0])
	{
		if (!(arr[0][i] > 0 && arr[0][i - 1] == 0)
			&& !(arr[0][i] == 0 && arr[0][i - 1] > 0))
		{
			new[j] = arr[0][i];
			str[0][j++] = str[0][i];
		}
		i++;
	}
	str[0][j] = '\0';
	free(arr[0]);
	arr[0] = NULL;
	arr[0] = new;
}

void	set_commands(char *str, int *arr)
{
	int		i;
	int		j;
	int		a;
	t_cmd	*last;

	i = 0;
	last = get_last(g_data->commands);
	while (str[i] && ((str[i] == ' ' || str[i] == '\t') && arr[i] == 0))
		i++;
	while (str[i] && ((str[i] == ' ' || str[i] == '\t') && arr[i] == 0))
	{
		last->cmd_name = ft_charjoin(last->cmd_name, str[i++]);
	}
	i = j;
	a = 1;
	while (str[i])
	{
		if (((str[i] == ' ' || str[i] == '\t') && arr[i] == 0))
			a++;
		else
			last->arguments[a] = ft_charjoin(last->cmd_name, str[i++]);
		while (str[i] && ((str[i] == ' ' || str[i] == '\t') && arr[i] == 0))
			i++;
	}
}

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

void	parse(char *cmds)
{
	int		*arr;
	char	*tmp;
	t_cmd	*last;

	arr = NULL;
	add_cmd();
	last = get_last(g_data->commands);
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

	arr = NULL;
	set_arr(str, &arr);
	cmds = split_cmds(str, arr);
	free(arr);
	arr = NULL;
	i = 0;
	while (cmds[i])
		parse(cmds[i++]);
	open_red();
}

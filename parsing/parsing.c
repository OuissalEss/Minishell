/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:55:36 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/25 18:30:33 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

void	set_arr(char *str, int **array)
{
	int	*arr;
	int	i;

	if (str[0] == '\'')
		arr[0] = 1;
	else if (str[0] == '\"')
		arr[0] = 2;
	i = 1;
	while (str[i])
	{
		arr[i] = 0;
		if (str[i] == '\'' && str[i - 1] == 0)
			arr[i] = 1;
		else if (str[i] == '\"' && str[i - 1] == 0)
			arr[i] = 2;
		i++;
	}
}

int	add_red(t_red **r, int t, char *str, int *arr)
{
	t_red	*rd;
	int		i;

	i = 0;
	rd = malloc(sizeof(t_red));
	rd->file_name = ft_charjoin(rd->file_name, '\0');
	while (str[i] && (arr[i] == 0 && !(str[i] == ' '
				|| str[i] == '\t' || str[i] == '<' || str[i] == '>')))
	{
		rd->file_name = ft_charjoin(rd->file_name, str[i]);
		i++;
	}
	rd->fd[0] = -1;
	rd->fd[1] = -1;
	if (t == 4)
		pipe(rd->fd);
	rd->type = t;
	rd->next = NULL;
	return (i);
}

void	handle_redirection(char **str, int **arr)
{
	int		i;
	int		j;
	t_red	*red;

	i = 0;
	j = 0;
	red = NULL;
	while (str[i])
	{
		if ((str[0][i] == '<' && str[0][i + 1] == '<') && arr[0][i] == 0)
			i += add_red(&red, 4, &str[0][i], &arr[0][i]);
		else if ((str[0][i] == '>' && str[0][i + 1] == '>') && arr[0][i] == 0)
			i += add_red(&red, 3, str[0], &i);
		else if (str[0][i] == '>' && arr[0][i] == 0)
			i += add_red(&red, 2, str[0], &i);
		else if (str[0][i] == '<' && arr[0][i] == 0)
			i += add_red(&red, 1, str[0], &i);
		else
		{
			str[0][j] = str[0][i];
			arr[0][j] = arr[0][i];
		}
		i++;
		j++;
	}
}

void	handle_quotes(char **str, int **arr)
{
	int	i;
	int	j;
	int	*new;

	new = malloc(sizeof(int) * strlen(str[0]));
	if (arr[0][0] > 0)
		new[0] == arr[0][0];
	if (arr[0][0] > 0)
		str[0][0] == str[0][0];
	i = 1;
	j = 1;
	while (str[0][i] && str[0][0])
	{
		if (!(arr[0][i] > 0 && arr[0][i - 1] == 0)
			&& !(arr[0][i] == 0 && arr[0][i - 1] > 0))
		{
			new[j] == arr[0][i];
			str[0][j++] == str[0][i];
		}
		i++;
	}
	str[0][j] = '\0';
	free(arr[0]);
	arr[0] = NULL;
	arr[0] = new;
}

char	*handle_expansion(char **str, int **arr)
{
	int		i;
	char	*new;
	char	*var_name;
	char	*var_value;

	i = 0;
	new = NULL;
	while (str[0][i])
	{
		if (str[0][i] == '$' && arr[0][i] == 0)
		{
			if (str[i + 1] == '?')
			{
				new = ft_strjoin(new, ft_itoa(g_data->exit_status));
				i += 2;
			}
			else if (ft_isalnum(str[i + 1]) == 1)
				i += expand(&str[0][i], &arr[0][i]);
		}
		else
			new = ft_charjoin(new, str[i]);
		i++;
	}
	new = ft_charjoin(new, '\0');
	return (new);
}

void	start_parsing(char *str)
{
	int		*arr;
	int		i;
	char	**cmds;
	char	*tmp;

	arr = NULL;
	set_arr(str, &arr);
	cmds = split_cmds(str, arr);
	i = 0;
	while (cmds[i])
	{
		add_cmd();
		set_arr(cmds[i], &arr);
		handle_redirection(&cmds[i], &arr);
		handle_quotes(&cmds[i], &arr);
		tmp = handle_expansion(&cmds[i], &arr);
		free(cmds[i]);
		cmds[i] = NULL;
		cmds[i] = tmp;
		set_commands();
		i++;
	}
}

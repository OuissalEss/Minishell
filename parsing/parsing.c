/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:55:36 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/27 17:53:05 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

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
	while (str[i] && (arr[i] == 0 && (str[i] == ' ' || str[i] == '\t')))
		i++;
	while (str[i] && (arr[i] != 0 || !(str[i] == ' '
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
	red_add_back(r, rd);
	return (i);
}

void	handle_redirection(char **str, int **arr, t_red	*red)
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

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*x;

	x = b;
	i = 0;
	while (i < len)
	{
		x[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	*ft_calloc(size_t size)
{
	void	*x;

	x = malloc(size);
	if (!x)
		return (NULL);
	ft_memset(x, 0, size);
	return (x);
}

int	get_count(char *str, int **arr )
{
	int		i;
	int		c;

	i = 0;
	c = 1;
	while (str[i])
	{
		if (str[i] == '|' && arr[0][i] == 0)
			c++;
		i++;
	}
	return (c);
}

char	**split_cmds(char *str, int **arr)
{
	int		i;
	int		c;
	char	**cmds;

	c = get_count(str, arr);
	cmds = ft_calloc(sizeof(char *) * (c + 1));
	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '|' && arr[0][i] == 0)
			c++;
		else
		{
			cmds[c] = ft_charjoin(cmds[c], str[i]);
			i++;
		}
	}
	cmds[c + 1] = NULL;
	return (cmds);
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
		handle_redirection(&cmds[i], &arr, get_last(g_data->commands)->red);
		handle_quotes(&cmds[i], &arr);
		tmp = handle_expansion(&cmds[i], &arr);
		free(cmds[i]);
		cmds[i] = NULL;
		cmds[i] = tmp;
		set_commands();
		i++;
	}
	open_red();
}

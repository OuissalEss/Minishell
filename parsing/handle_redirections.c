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

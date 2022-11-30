/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:48:38 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/29 09:00:44 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../parsing.h"
#include "check_error.h"

int	check_file_name(char *str, int i, char *redirect)
{
	int	j;

	j = 0;
	while (redirect[j])
	{
		if ((redirect[j] == ' ' || redirect[i] == '\t') && quotes(str, i) == 0)
			return (-1);
	}
	return (1);
}

int	check_red(t_errflags *f, char *str, int i)
{
	char	*redirect;

	if ((f->in == 1 || f->out == 1 || f->app == 1)
		&& (str[i + 1] != '>' && str[i + 1] != '<'))
	{
		i++;
		redirect = get_name(str, &i);
		redirect = expand_dollar(redirect);
		if (redirect[0] == '\0' || check_file_name(str, i, redirect) != 1)
		{
			printf("ambiguous redirect\n");
			return (-3);
		}
	}
	return (0);
}

int	error(t_errflags *f, char *str, int i)
{
	if (f->pipe == 2 || (f->in == 1 && f->out == 1)
		|| (f->pipe == 1 && f->hdoc == 1)
		|| (f->in == 1 && f->app == 1) || (f->in == 1 && f->hdoc == 1)
		|| (f->out == 1 && f->app == 1) || (f->out == 1 && f->hdoc == 1)
		|| (f->app == 1 && str[i] == '>' && str[i - 1] != '>')
		|| (f->hdoc == 1 && str[i] == '<' && str[i - 1] != '<'))
		return (-1);
	if (check_red(f, str, i) == -1)
		return (-1);
	return (1);
}

int	max_heredoc(t_errflags *f)
{
	printf("maximum here-document count exceeded\n");
	return (free_flags(f, -2));
}

int	check_error(char *str)
{
	int			i;
	t_errflags	*f;

	init_flags(&f);
	i = skip_white_spaces(str, 0, f);
	if (str[i] == '|')
		return (free_flags(f, -1));
	while (str[i])
	{
		i = skip_white_spaces(str, i, f);
		if (quotes(str, i) == 0)
			set_flags(f, str, i);
		if (error(f, str, i) < 0)
			return (free_flags(f, error(f, str, i)));
		if (f->c == 1)
			set_flags2(f, str, i);
		if (f->hdoc_count > 16)
			return (max_heredoc(f));
		i++;
	}
	if (quotes(str, i) != 0 || f->pipe == 1 || f->in == 1
		|| f->out == 1 || f->app == 1 || f->hdoc == 1)
		return (free_flags(f, -1));
	return (free_flags(f, 1));
}

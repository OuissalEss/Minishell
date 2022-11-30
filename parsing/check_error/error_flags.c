/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:48:58 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/29 10:20:07 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "check_error.h"

void	add_hdoc_err(t_errflags *f, char *s, int i)
{
	t_heredoc	*new;
	t_heredoc	*l;

	new = malloc(sizeof(t_heredoc));
	new->dlmt = remove_quotes(get_name(s, &i));
	new->next = NULL;
	l = f->hdocs;
	if (l)
	{
		while (l->next)
			l = l->next;
		l->next = new;
	}
	else
		f->hdocs = new;
}

void	set_flags(t_errflags *flags, char *s, int i)
{
	if (s[i] == '|' && flags->pipe == 0)
	{
		flags->pipe = 1;
		flags->id_command++;
	}
	else if (s[i] == '|' && flags->pipe == 1)
		flags->pipe = 2;
	else if (s[i] == '>' && flags->out == 0)
		flags->out = 1;
	else if (s[i] == '>' && flags->out == 1)
	{
		flags->out = 0;
		flags->app = 1;
	}
	else if (s[i] == '<' && flags->in == 0)
		flags->in = 1;
	else if (s[i] == '<' && flags->in == 1)
	{
		flags->in = 0;
		flags->hdoc = 1;
	}
	else if (s[i] != ' ')
			flags->c = 1;
}

void	set_flags2(t_errflags *flags, char *s, int i)
{
	if (flags->hdoc == 1)
	{
		flags->dlmt = 1;
		flags->hdoc = 0;
		flags->hdoc_count++;
		add_hdoc_err(flags, s, i + 1);
	}
	flags->c = 0;
	flags->pipe = 0;
	flags->in = 0;
	flags->out = 0;
	flags->app = 0;
	flags->hdoc = 0;
}

void	open_hdocs(t_errflags *f)
{
	char		*str;
	t_heredoc	*h;

	h = f->hdocs;
	while (h)
	{
		while (1)
		{
			str = readline(">");
			if (str == NULL || strcmp(str, h->dlmt) == 0)
				break ;
			free(str);
			str = NULL;
		}
		h = h->next;
	}
}

int	free_flags(t_errflags *f, int r)
{
	t_heredoc	*hd;

	hd = f->hdocs;
	if (r == -1)
		printf("Error\n");
	if (f->hdocs)
	{
		if (r != -2)
			open_hdocs(f);
		while (hd)
		{
			f->hdocs = f->hdocs->next;
			free(hd->dlmt);
			hd->dlmt = NULL;
			free(hd);
			hd = NULL;
			hd = f->hdocs;
		}
	}
	free(f);
	f = NULL;
	if (r == -2)
		return (-1);
	return (r);
}

void	init_flags(t_errflags **f)
{
	t_errflags	*flags;

	flags = malloc(sizeof(t_errflags));
	flags->c = 0;
	flags->pipe = 0;
	flags->in = 0;
	flags->out = 0;
	flags->app = 0;
	flags->hdoc = 0;
	flags->dlmt = 0;
	flags->hdoc_count = 0;
	flags->id_command = 0;
	flags->hdocs = NULL;
	*f = flags;
}

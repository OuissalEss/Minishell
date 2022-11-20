#include "minishell.h"
#include "parsing.h"

int	skip_white_spaces(char *str, int i, t_errflags *flags)
{
	if (flags->dlmt == 1 && str[i] == ' ')
		flags->dlmt = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0' && i > 0)
		i--;
	return (i);
}

int	error(t_errflags *f, char *str, int i)
{
	if (f->pipe == 2 || (f->in == 1 && f->out == 1)
		|| (f->in == 1 && f->app == 1) || (f->in == 1 && f->hdoc == 1)
		|| (f->out == 1 && f->app == 1) || (f->out == 1 && f->hdoc == 1)
		|| (f->app == 1 && str[i] == '>' && str[i - 1] != '>')
		|| (f->hdoc == 1 && str[i] == '<' && str[i - 1] != '<')
		|| (f->dlmt == 1 && f->in == 1) || (f->dlmt == 1 && f->out == 1))
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
		if (error(f, str, i) == -1)
			return (free_flags(f, -1));
		if (f->c == 1)
			set_flags2(f);
		if (f->hdoc_count > 16)
			return (max_heredoc(f));
		i++;
	}
	if (quotes(str, i) != 0 || f->pipe == 1 || f->in == 1
		|| f->out == 1 || f->app == 1 || f->hdoc == 1)
		return (free_flags(f, -1));
	return (free_flags(f, 1));
}

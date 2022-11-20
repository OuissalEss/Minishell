#include "minishell.h"
#include "parsing.h"

void	add_hdoc_err(t_errflags f, char *s, int i)
{
	t_heredoc	*new;

	new = malloc(sizeof(t_heredoc));
	new->dlmt = get_name(s, &i);
	new->next = NULL;

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
		add_hdoc_err(flags, s, i + 1);
	}
	else if (s[i] != ' ')
			flags->c = 1;
}

void	set_flags2(t_errflags *flags)
{
	if (flags->hdoc == 1)
	{
		flags->dlmt = 1;
		flags->hdoc = 0;
		flags->hdoc_count++;
	}
	flags->c = 0;
	flags->pipe = 0;
	flags->in = 0;
	flags->out = 0;
	flags->app = 0;
	flags->hdoc = 0;
}

int	free_flags(t_errflags *f, int r)
{
	free(f);
	f = NULL;
	if (r == -2)
		return (-1);
	if (r == -1)
		printf("Error\n");
	if (f->id_command > 0)
		open_hdocs(f);
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
	flags->hdoc = NULL;
	*f = flags;
}

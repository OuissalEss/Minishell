#include "parsing/minishell.h"

static int	ft_intlen(long nb)
{
	int	i;

	i = 1;
	if (nb < 0)
	{
		nb = -nb;
		i++;
	}
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			i;
	long		nb;
	char		*str;

	nb = n;
	i = ft_intlen(nb);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = '\0';
	if (n < 0)
	{
		nb = -nb;
	}
	while (i > 0)
	{
		str[--i] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

char	*join_two_str(char *s1, char const *s2, int l1)
{
	int		i;
	char	*p;

	p = malloc(sizeof(char *) * (l1 + strlen(s2)));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != EOL)
	{
		p[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != EOL)
	{
		p[i + l1] = s2[i];
		i++;
	}
	p[i + l1] = EOL;
	return (p);
}

char	*ft_charjoin(char *str, char x)
{
	int		i;
	int		len;
	char	*new;

	len = 0;
	i = 0;
	if (str != NULL)
		len = strlen(str);
	new = malloc(sizeof(char) * (len + 2));
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = x;
	new[i + 1] = '\0';
	if (str != NULL)
		free(str);
	str = NULL;
	return (new);
}

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		l1;
	char	*p;

	if (!s1)
		s1 = ft_charjoin(s1, '\0');
	if (!s2)
		s2 = ft_charjoin(s2, '\0');
	l1 = strlen(s1);
	p = join_two_str(s1, s2, l1);
	if (p == NULL)
		return (NULL);
	free(s1);
	s1 = NULL;
	free(s2);
	s2 = NULL;
	return (p);
}

char	*get_varname(char *str, int i)
{
	int		i1;
	int		j;
	char	*var_name;

	i1 = i;
	while (str[i] && ft_isalnum(str[i]) != 0)
		i++;
	var_name = malloc(sizeof(char) * (i - i1 + 1));
	j = 0;
	while (str[i1] && ft_isalnum(str[i1]) != 0)
		var_name[j++] = str[i1++];
	var_name[j] = '\0';
	return (var_name);
}

char	*get_varvalue(char *var_name)
{
	int		j;
	char	*value;
	t_env	*envp;

	j = 0;
	value = NULL;
	envp = g_data->env;
	if (!envp || var_name[0] == '\0')
		return (ft_charjoin(value, '\0'));
	while (envp)
	{
		if (strcmp(envp->var, var_name) == 0)
		{
			value = envp->value;
			break ;
		}
		envp = envp->next_var;
	}
	if (value == NULL)
		return (ft_charjoin(value, '\0'));
	return (value);
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

	j1 = 0;
	if (arr[0][0] == 0)
	{
		str[0][0] = str[0][0];
		j1 = 1;
	}
	*j = j1;
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

int	expand(char *str, int *arr, char **new)
{
	int		i;
	char	*n;
	char	*var_name;
	char	*var_value;

	var_name = get_varname(str, 1);
	var_value = get_varvalue(var_name);
	n = *new;
	i = 0;
	while (var_value[i])
	{
		n = ft_charjoin(n, var_value[i]);
		i++;
	}
	*new = n;
	i = strlen(var_name);
	free(var_name);
	var_name = NULL;
	return (i);
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

void	*ft_calloc(size_t size, size_t count)
{
	void	*x;

	x = malloc(size * count);
	if (!x)
		return (NULL);
	ft_memset(x, 0, size * count);
	return (x);
}

int	get_count(char *str, int **arr)
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
	cmds = malloc(sizeof(char *)*(c + 1));
	i = 0;
	while (i < c + 1)
		cmds[i++] = NULL;
	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '|' && arr[0][i] == 0)
			c++;
		else
			cmds[c] = ft_charjoin(cmds[c], str[i]);
			i++;
	}
	cmds[c + 1] = NULL;
	return (cmds);
}






void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*l;

	l = *lst;
	if (l)
	{
		while (l->next_var)
			l = l->next_var;
		l->next_var = new;
	}
	else
		*lst = new;
}

char	*get_var(char *str)
{
	int		i;
	char	*var;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var = malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

char	*get_value(char *str)
{
	int		start;
	int		i;
	char	*value;

	start = 0;
	while (str[start] && str[start] != '=')
		start++;
	start++;
	value = malloc(sizeof(char) * strlen(&str[start]) + 1);
	i = 0;
	while (str[start])
		value[i++] = str[start++];
	value[i] = '\0';
	return (value);
}

void	set_env(char **envp)
{
	int		i;
	t_env	*node;

	i = 0;
	g_data->env = NULL;
	if (!envp)
		return ;
	while (envp[i])
	{
		node = malloc(sizeof(t_env));
		node->var = get_var(envp[i]);
		node->value = get_value(envp[i]);
		node->next_var = NULL;
		ft_lstadd_back(&g_data->env, node);
		i++;
	}
}

void	init_data(char **envp)
{
	g_data = malloc(sizeof(t_data));
	g_data->commands = NULL;
	set_env(envp);
	g_data->exit_status = 0;
	g_data->child_process = 0;
}

t_cmd	*get_last(t_cmd *lst)
{
	if (lst)
	{
		while (lst->next_cmd)
			lst = lst->next_cmd;
	}
	return (lst);
}

void	cmd_add_back(t_cmd *new)
{
	t_cmd	*l;

	l = g_data->commands;
	if (l)
	{
		while (l->next_cmd)
			l = l->next_cmd;
		l->next_cmd = new;
	}
	else
		g_data->commands = new;
}

void	add_cmd(void)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	command->cmd_name = NULL;
	command->arguments = NULL;
	command->infile = 0;
	command->outfile = 1;
	command->hdoc = NULL;
	command->red = NULL;
	command->next_cmd = NULL;
	cmd_add_back(command);
}

void	print(void)
{
	int			i;
	t_cmd		*lst;
	t_heredoc	*hlst;

	printf("HELLOLLLL\n");
	lst = g_data->commands;
	while (lst)
	{
		printf("cmd = %s\n", lst->cmd_name);
		i = 0;
		while (lst->arguments && lst->arguments[i])
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
		t_red *r = lst->red;
		while (r)
		{
			printf("red = %s,%d      ", r->file_name, r->type);
			r = r->next;
		}
		printf("\n");
		lst = lst->next_cmd;
	}
}

int	main(int argc, char **argv, char **envp)
{
    int *arr;
    char *str;
    int  i;
	int k;
	char **cmds;
	t_red	*r = NULL;

	(void) argc;
	(void) argv;
	init_data(envp);
	t_env *e = g_data->env;
	// while (e)
	// {
	// 	printf("var = %s\n", e->var);
	// 	e = e->next_var;
	// }
	while (1)
	{
		i = 0;
		str = readline(">");
		arr = (int *)malloc(sizeof(int) *1024);
		set_arr(str, &arr);
		cmds = split_cmds(str, &arr);
		free(arr);
		arr =NULL;
		i = 0;
		while (cmds[i]) {
			// printf("%s\n", cmds[i++]);
			add_cmd();
			arr = (int *)malloc(sizeof(int) * 1024);
			set_arr(cmds[i], &arr);
			t_cmd *last =  get_last(g_data->commands);
			last->red = handle_redirection(&cmds[i], &arr, last->red);
			handle_quotes(&cmds[i], &arr);
			cmds[i] = handle_expansion(&cmds[i], &arr);
			printf("%s\n", cmds[i]);
			free(arr);
			arr =NULL;
			i++;
		}
		printf("i = %d\n\n", i);
		print();










		// printf("%s\n", str);
		// while (str[i]) {
		// 	printf("%d ", arr[i]);
		// 	i++;
		// }
		// printf("\n");
		
		// printf("%s\n", str);
		// i = 0;
		// while (str[i]) {
		// 	printf("%d ", arr[i]);
		// 	i++;
		// }
		// printf("\n");

		// printf("%s\n", str);
		// i = 0;
		// while (str[i]) {
		// 	printf("%d ", arr[i]);
		// 	i++;
		// }
		// printf("\n");
	}
    return (0);
}
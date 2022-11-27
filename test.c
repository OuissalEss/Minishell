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

int	expand(char *str, int *arr, char **new)
{
	int		i;
	char	*var_name;
	char	*var_value;

	var_name = get_varname(str, 1);
	var_name = get_varvalue(var_name);
	i = 0;
	while (str[i])
	{
		new[0] = ft_charjoin(new[0], str[i]);
		i++;
	}
	free(var_name);
	var_name = NULL;
	return (i);
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
			if (str[0][i + 1] == '?')
			{
				new = ft_strjoin(new, ft_itoa(g_data->exit_status));
				i += 2;
			}
			else if (ft_isalnum(str[0][i + 1]) == 1)
				i += expand(&str[0][i], &arr[0][i], &new);
		}
		else
			new = ft_charjoin(new, str[0][i]);
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


int     main(void) {
    int *arr;
    char *str;
    int  i;
	char **cmds;
	t_red	*r = NULL;

	while (1)
	{
		i = 0;
		str = readline(">");
		arr = (int *)malloc(sizeof(int) *1024);
		set_arr(str, &arr);
		cmds = split_cmds(str, &arr);
		i = 0;
		while (cmds[i]) {
			// printf("%s\n", cmds[i++]);
			set_arr(str, &arr);
			handle_redirection(&cmds[i], &arr, r);
			handle_quotes(&cmds[i], &arr);
			handle_expansion(&cmds[i], &arr);
			printf("%s\n", cmds[i]);
		}
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
#include "minishell.h"
#include "parsing.h"

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

char	*ft_strjoin(char *s1, char const *s2)
{
	int		l1;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	l1 = strlen(s1);
	p = join_two_str(s1, s2, l1);
	if (p == NULL)
		return (NULL);
	free(s1);
	s1 = NULL;
	return (p);
}

int	skip_whitespace(char *str, int i)
{
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		i--;
	return (i);
}

char	*get_name(char *str, int *j)
{
	int		i;
	char	*name;

	i = *j;
	name = NULL;
	i = skip_whitespace(str, i);
	while (str[i] && ((str[i] != ' ' && str[i] != '|' && str[i] != '<'
				&& str[i] != '>' ) || quotes(str, i) != 0))
	{
		name = ft_charjoin(name, str[i]);
		i++;
	}
	name = ft_charjoin(name, '\0');
	*j = i;
	return (name);
}

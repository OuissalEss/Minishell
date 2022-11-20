#include "minishell.h"
#include "parsing.h"

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
	if (!envp)
		return (ft_charjoin(value, '\0'));
	while (envp)
	{
		if (envp->var == var_name)
		{
			value = envp->value;
			break;
		}
		envp = envp->next_var;
	}
	if (!value)
		return (ft_charjoin(value, '\0'));
	return (occurence);
}

char	*expand_dollar(char *str)
{
	int		i;
	char	*new;
	char	*var_name;
	char	*var;

	i = 0;
	new = NULL;
	new = ft_charjoin(new, '\0');
	while (str[i])
	{
		if (str[i] == '$' && quotes(str, i) != 1)
		{
			var_name = get_varname(str, i + 1);
			var = get_varvalue(var_name);
			new = ft_strjoin(new, var);
			i += strlen(var_name);
			free(var_name);
			var_name = NULL;
		}
		else
			new = ft_charjoin(new, str[i]);
		i++;
	}
}

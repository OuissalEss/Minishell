/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 07:37:39 by oessamdi          #+#    #+#             */
/*   Updated: 2022/12/02 14:14:56 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
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
	char	*value;
	t_env	*envp;

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

int	expand(char *str, char **new)
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

int	expand_exit(char *str, char **new)
{
	int		i;
	char	*nb;
	char	*n;

	nb = ft_itoa(g_data->exit_status);
	i = 0;
	n = *new;
	while (str[i])
	{
		n = ft_charjoin(n, nb[i]);
		i++;
	}
	*new = n;
	free(nb);
	nb = NULL;
	return (2);
}

char	*handle_expansion(char **str, int **arr)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (str[0][i])
	{
		if (str[0][i] == '$' && arr[0][i] != 1)
		{
			if (str[0][i + 1] == '?')
				i += expand_exit(&str[0][i], &new);
			else if (ft_isalnum(str[0][i + 1]) == 1)
				i += expand(&str[0][i], &new);
			else
				new = ft_charjoin(new, str[0][i]);
		}
		else
			new = ft_charjoin(new, str[0][i]);
		i++;
	}
	new = ft_charjoin(new, '\0');
	return (new);
}

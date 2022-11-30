/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:48:41 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/25 17:46:38 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parsing.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
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

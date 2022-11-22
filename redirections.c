/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:48:50 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/22 15:03:24 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	open_hdocs(t_errflags *f)
{
	(void)f;
	printf("open here-doc\n");
}

int	add_infile(char *str, int i)
{
	t_cmd	*last;
	char	*file_name;
	int		fd;

	last = get_last(g_data->commands);
	file_name = get_name(str, &i);
	file_name = remove_quotes(file_name);
	if (last->infile != 0)
		close(last->infile);
	fd = open(file_name, O_CREAT | O_RDONLY, 0644);
	free(file_name);
	file_name = NULL;
	if (fd < 0)
		printf("%s\n", strerror(errno));
	else
		last->infile = fd;
	return (i);
}

int	add_outfile(char *str, int i)
{
	t_cmd	*last;
	char	*file_name;
	int		fd;

	last = get_last(g_data->commands);
	file_name = get_name(str, &i);
	file_name = remove_quotes(file_name);
	if (last->outfile != 1)
		close(last->outfile);
	fd = open(file_name, O_WRONLY | O_CREAT, 0644);
	free(file_name);
	file_name = NULL;
	if (fd < 0)
		printf("%s\n", strerror(errno));
	else
		last->outfile = fd;
	return (i);
}

int	add_append(char *str, int i)
{
	t_cmd	*last;
	char	*file_name;
	int		fd;

	last = get_last(g_data->commands);
	file_name = get_name(str, &i);
	file_name = remove_quotes(file_name);
	if (last->outfile != 1)
		close(last->outfile);
	fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	free(file_name);
	file_name = NULL;
	if (fd < 0)
		printf("%s\n", strerror(errno));
	else
		last->outfile = fd;
	return (i);
}

int	handle_redirections(char *str, int i)
{
	if (str[i] == '<' && str[i + 1] == '<')
		i = add_heredoc(str, i + 2);
	else if (str[i] == '<')
		i = add_infile(str, i + 1);
	else if (str[i] == '>' && str[i + 1] == '>')
		i = add_append(str, i + 2);
	else if (str[i] == '>')
		i = add_outfile(str, i + 1);
	i--;
	return (i);
}

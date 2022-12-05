/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:19:12 by oessamdi          #+#    #+#             */
/*   Updated: 2022/12/05 06:21:38 by slaajour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/parsing.h"
#include "parsing/check_error/check_error.h"

// void	print(void)
// {
// 	int			i;
// 	t_cmd		*lst;
// 	t_red		*r;

// 	lst = g_data->commands;
// 	while (lst)
// 	{
// 		// printf("cmd = %s\n", lst->cmd_name);
// 		i = 0;
// 		while (lst->arguments && lst->arguments[i])
// 		{
// 			// printf("args[%d] = %s     ", i, lst->arguments[i]);
// 			i++;
// 		}
// 		// printf("\ninfile = %d\n", lst->infile);
// 		// printf("outfile = %d\n", lst->outfile);
// 		r = lst->red;
// 		while (r)
// 		// {
// 		// 	printf("r = %s   type = %d   ", r->file_name, r->type);
// 		// 	printf("fd[0] = %d   fd[1] = %d\n", r->fd[0], r->fd[1]);
// 			r = r->next;
// 		}
// 		lst = lst->next_cmd;
// }

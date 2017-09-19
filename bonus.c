/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:03:52 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/18 16:18:23 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_select *get_dir_content(t_select *tmp)
{
	struct dirent infostruct;
	DIR           dirpath;
	t_select      *lst;
	t_select      *new;
	char           *path

	if (!(dirpath = opendir(tmp->name)))
		ft_error(1, "read");
	tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	while (infostruct = readdir(dirpath))
	{
		if (!(path = ft_strjoinmulti(lst->name, "/", infostruct->d_name))
				|| (new = ft_memalloc(sizeof(t_select))))
			ft_error(1, "lstat failed");
		else
			add_t_select_list(&lst, new);
		free(path);
	}
}

void display_directory(t_select *tmp)
{
	t_select lst;

	lst = get_dir_content;
}

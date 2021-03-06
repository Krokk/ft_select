/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 16:40:24 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/24 02:57:09 by tchapka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		print_selected(t_select **lst)
{
	t_select	*tmp;
	int			is_arg;

	tmp = *lst;
	is_arg = 0;
	set_termm_clear(1);
	while (tmp)
	{
		if (tmp->is_selected)
		{
			ft_putstr(tmp->name);
			if (tmp->next)
				ft_putstr(" ");
			is_arg++;
		}
		(tmp) = tmp->next;
	}
	if (is_arg)
		ft_putstr("\n");
}

static int		how_print(t_select **lst)
{
	if ((*lst)->is_cursor)
		ft_putstr_fd(tgetstr("us", NULL), 2);
	if ((*lst)->is_selected)
		ft_putstr_fd(tgetstr("mr", NULL), 2);
	ft_putstr_fd((*lst)->name, 0);
	ft_putstr_fd(tgetstr("me", NULL), 2);
	return (0);
}

int				ft_pointchar(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (0);
}

void			print_arg(t_select *lst)
{
	t_select	*tmp;
	int			pos;
	int			line;
	int			x;

	x = 0;
	pos = 0;
	line = -1;
	tmp = lst;
	tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	while (tmp)
	{
		while (++line < g_data->win_line && tmp)
		{
			tputs((tgoto(tgetstr("cm", NULL), x, line)), 1, ft_pointchar);
			tmp->line = pos;
			how_print(&tmp);
			pos++;
			tmp = tmp->next;
		}
		x += g_data->max_name_len + 4;
		line = -1;
	}
}

int				show_cursor(t_select **lst)
{
	int			buffer;
	t_select	*tmp;
	int			ret;

	tmp = *lst;
	ret = 0;
	g_select = tmp;
	tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	while (ret == 0)
	{
		ft_resize(1);
		buffer = 0;
		read(0, &buffer, 8);
		tmp = handle_key(buffer, tmp, &ret);
		tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	}
	if (ret == 1)
		print_selected(lst);
	if (ret == 2)
		set_termm_quit(1);
	free_t_select();
	return (0);
}

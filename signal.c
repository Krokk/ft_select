/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 07:58:46 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/21 17:34:46 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void			set_termm_cont(int i)
{
	(void)i;
	set_termm();
	tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	print_arg(g_select);
}

void				ft_signal(void)
{
	signal(SIGWINCH, ft_resize);
	signal(SIGINT, set_termm_back);
	signal(SIGSTOP, set_termm_back);
	signal(SIGCONT, set_termm_cont);
}

int					set_termm(void)
{
	char			*name_term;

	// free name term quand on quitte
	if ((name_term = getenv("TERM")) == NULL)
		ft_error(2, "<TERM> VARIABLE NOT FOUND");
	if (tgetent(NULL, name_term) == ERR)
		ft_error(2, "VARIABLE NOT VALID");
	if (tcgetattr(0, &g_data->save_term) == -1)
		ft_error(2, "tcgetattr");
	if (tcgetattr(0, &g_data->term) == -1)
		ft_error(2, "tcgetattr");
	g_data->term.c_lflag &= ~(ICANON);
	g_data->term.c_lflag &= ~(ECHO);
	g_data->term.c_cc[VMIN] = 1;
	g_data->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &g_data->term) == -1)
		return (-1);
	tputs(tgetstr("ti", NULL), 1, ft_pointchar);
	tputs(tgetstr("vi", NULL), 1, ft_pointchar);
	return (0);
}

void				ft_resize(int i)
{
	struct winsize	sz;
	int				col_nbr;

	(void)i;
	ioctl(STDERR_FILENO, TIOCGWINSZ, &sz);
	g_data->win_col = sz.ws_col;
	g_data->win_line = sz.ws_row;
	col_nbr = (sz.ws_col / (g_data->max_name_len + 4)) + 1;
	if ((g_data->args_count / sz.ws_row) + 1 >= col_nbr)
		ft_putstr_fd("PLEASE RESIZE THE TERMINAL", 0);
	else
		print_arg(g_select);
}

void				free_t_select(void)
{
	t_select		*save;

	while (g_select)
	{
		save = g_select->next;
		ft_strdel(&g_select->name);
		free(g_select);
		g_select = save;
	}
}

void				set_termm_back(int i)
{
	(void)i;
	tcsetattr(0, TCSANOW, &g_data->save_term);
	tputs(tgetstr("ve", NULL), 1, ft_pointchar);
	tputs(tgetstr("te", NULL), 1, ft_pointchar);
}

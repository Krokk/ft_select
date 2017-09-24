/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 07:58:46 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/24 01:26:47 by tchapka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void			set_termm_cont(int i)
{
	(void)i;
	ft_signal();
	set_termm();
	ft_resize(1);
}

void				ft_signal(void)
{
	signal(SIGWINCH, ft_resize);
	signal(SIGINT, set_termm_quit);
	signal(SIGQUIT, set_termm_quit);
	signal(SIGTSTP, set_termm_back);
	signal(SIGCONT, set_termm_cont);
}

int					set_termm(void)
{
	char			*name_term;

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
	col_nbr = (sz.ws_col / (g_data->max_name_len + 4));
	tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	if ((g_data->args_count % sz.ws_row) == 0)
		col_nbr++;
	if ((g_data->args_count / sz.ws_row) + 1 > col_nbr)
		ft_putstr_fd("PLEASE RESIZE THE TERMINAL", 0);
	else
		print_arg(g_select);

}

void				free_t_select(void)
{
	t_select		*save;
	t_select		*tmp;

	tmp = g_data->head;
	while (tmp)
	{
		save = tmp->next;
		ft_strdel(&tmp->name);
		free(tmp);
		tmp = save;
	}
}

void				set_termm_back(int i)
{
	(void)i;
	tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	tputs(tgetstr("ve", NULL), 1, ft_pointchar);
	tputs(tgetstr("te", NULL), 1, ft_pointchar);
	tcsetattr(0, TCSADRAIN, &g_data->save_term);
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, "\032");
}

void				set_termm_clear(int i)
{
	(void)i;
	tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	tputs(tgetstr("ve", NULL), 1, ft_pointchar);
	tputs(tgetstr("te", NULL), 1, ft_pointchar);
	tcsetattr(0, TCSANOW, &g_data->save_term);
}

void				set_termm_quit(int i)
{
	(void)i;
	tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	tputs(tgetstr("ve", NULL), 1, ft_pointchar);
	tputs(tgetstr("te", NULL), 1, ft_pointchar);
	tcsetattr(0, TCSANOW, &g_data->save_term);
	free_t_select();
	exit (0);
}

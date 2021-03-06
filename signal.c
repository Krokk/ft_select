/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 07:58:46 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/25 15:52:45 by rfabre           ###   ########.fr       */
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
	signal(SIGTERM, set_termm_quit);
	signal(SIGKILL, set_termm_quit);
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
	exit(0);
}

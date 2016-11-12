/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 17:05:11 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/12 21:57:51 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int		ft_is_printable(char *order)
{
	int	i;

	i = -1;
	while (order[++i] != '\0')
		if (ft_isprint(order[i]) == false)
			return (0);
	return (1);
}

int		key_selection_next(t_group *grp, char *order, int key)
{
	if (key == HOME)
		ft_go_home(grp);
	else if (key == END)
		ft_go_end(grp);
	else if (key == ALT_L)
		ft_prev_word(grp);
	else if (key == ALT_R)
		ft_next_word(grp);
	else if (key == ARROW_L || key == ARROW_R ||
		key == ARROW_U || key == ARROW_D)
		handling_arrow(grp, key);
	else if (ft_is_printable(order))
		print_cmd(grp, order);
	else
		return (0);
	return (1);
}

int		key_selection(t_group *grp, char *order)
{
	int	key;

	key = KEY(order[0], order[1], order[2], order[3]);
	if (key == ENTER)
		return (key);
	if (key == CTRL_D)
		handling_ctrl_d(grp);
	else if (key == DEL)
		remove_line(grp);
	else if (key == BACKSPACE || key == DEL)
		handling_backspace(grp);
	else if (key == CTRL_L)
		handling_clear_screen(grp);
	else if (key == PAGE_UP)
		ft_go_up(grp);
	else if (key == PAGE_DOWN)
		ft_go_down(grp);
	else
		return (key_selection_next(grp, order, key));
	return (1);
}

void read_fd_in(t_group *grp, char *order)
{
	int i;
	char str[2];

	i = -1;
	TERM(cmd_line) = NEW(0);
	while (order && order[++i] != '\0')
	{
		ft_bzero(str, 2);
		str[0] = order[i];
		if (order[i] != '\n')
			TERM(cmd_line) = JOINF(TERM(cmd_line), str, 1);
		else if (order[i + 1] != '\0')
			TERM(cmd_line) = JOINF(TERM(cmd_line), " ; ", 1);
	}
	grp->quit = true;
}

void	get_cmd(t_group *grp, int fd)
{
	int		ret;
	char	order[BUF_SIZE + 1];
	char	*tmp;

	ft_bzero(order, BUF_SIZE + 1);
	tmp = NULL;
	while ((ret = read(fd, order, BUF_SIZE)) > 0)
	{
		order[ret] = '\0';
		tmp = SDUP(order);
		if (key_selection(grp, order) == '\n' && ft_escape(grp) == 0)
			break ;
		ft_bzero(order, BUF_SIZE + 1);
	}
	if (TERM(cmd_quote) != NULL)
		fill_cmd_line(grp);
	ft_go_end(grp);
	ret == 0 ? read_fd_in(grp, tmp) : ft_putchar_fd('\n', 2);
	reset_edl(grp);
	ft_bzero(order, BUF_SIZE + 1);
}

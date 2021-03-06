/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:17:06 by jtranchi          #+#    #+#             */
/*   Updated: 2016/12/13 14:18:10 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void			init_term(t_group *grp)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	grp->term = (t_term *)malloc(sizeof(t_term));
	grp->term->curs_pos = 0;
	grp->term->line = 0;
	grp->term->cmd_size = 0;
	grp->term->other_read = false;
	grp->term->cmd_line = NULL;
	grp->term->cmd_quote = NULL;
	grp->term->search = NULL;
	grp->term->window = (t_window *)malloc(sizeof(t_window));
	grp->term->window->width = w.ws_col;
	grp->term->window->heigth = w.ws_row;
}

static	void	set_grpenv(t_group *grp)
{
	grp->env = (t_env *)malloc(sizeof(t_env));
	grp->env->lst = NULL;
	grp->env->lst_tmp = NULL;
	grp->env->opt_i = false;
	grp->env->start_varenv = 0;
	grp->env->end_varenv = 0;
	grp->env->cmd = NULL;
	grp->env->path_tmp = NULL;
	grp->env->pgid = NULL;
	grp->env->fg = false;
}

t_group			*set_grp(t_group *grp)
{
	grp = (t_group*)ft_memalloc(sizeof(t_group));
	set_grpenv(grp);
	grp->prompt_size = 6;
	grp->exit = 0;
	grp->err_parse = false;
	grp->hdcount = 0;
	grp->allcmd = NULL;
	grp->father = -1;
	grp->program_name = NULL;
	grp->program_pid = -1;
	grp->jobs = NULL;
	grp->pipefd_in = STDIN_FILENO;
	ft_get_history(grp);
	init_term(grp);
	grp->root = NULL;
	return (grp);
}

t_group			*get_grp(void)
{
	static t_group *grp = NULL;

	if (!grp)
		grp = set_grp(grp);
	return (grp);
}

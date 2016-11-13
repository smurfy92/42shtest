/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:30:12 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/13 22:50:01 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		check_lastcmd(t_group *grp)
{
	t_parse *tmp;

	tmp = grp->allcmd->andor->parselst;
	while (tmp->next)
		tmp = tmp->next;
	if (is_builtins(tmp->cmdsplit))
	{
		CMD(cmdsplit) = tmp->cmdsplit;
		builtins(grp);
	}
}

void		pipe_exec(t_group *grp)
{
	t_parse *tmp;
	int			ret;
	grp->father = fork();
	if (grp->father == 0)
	{
		while (grp->allcmd->andor->parselst)
		{
			tmp = grp->allcmd->andor->parselst;
			if (!tmp->fail)
			{
				if (tmp->next)
					ft_fork_pipe(grp);
				else
					exec_child(grp, tmp);
			}
			free_parselst(tmp);
			grp->allcmd->andor->parselst = tmp->next;
		}
		exit(EXIT_FAILURE);
	}
	waitpid(grp->father, &ret, 0);
	error_process_check(ret);
	check_lastcmd(grp);
	if (ret > 0)
		grp->exit = 1;
}

void		andor_exec(t_group *grp)
{
	t_andor *tmp;
	int 	ret;

	ret = 0;
	while (grp->allcmd->andor)
	{
		tmp = grp->allcmd->andor;
		REMOVE(&grp->allcmd->andor->cmd);
		reset_shell();
		pipe_exec(grp);
		init_shell();
		if ((tmp->type == 1 && grp->exit != 0) ||
			(tmp->type == 2 && grp->exit == 0))
		{
			free(tmp);
			grp->exit = 0;
			break ;
		}
		grp->allcmd->andor = tmp->next;
		if (tmp->next)
			grp->exit = 0;
		free_allparse(tmp);
		free(tmp);
	}
}

void		init_exec(t_group *grp)
{
	t_allcmd *tmp;

	if (!grp->fail)
	{
		while (grp->allcmd)
		{
			tmp = grp->allcmd;
			REMOVE(&tmp->cmd);
			andor_exec(grp);
			grp->allcmd = tmp->next;
			free(tmp);
			tmp = grp->allcmd;
		}
	}
	grp->fail = 0;
}

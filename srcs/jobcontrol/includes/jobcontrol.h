/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 23:25:11 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/03 04:10:23 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCONTROL_H
# define JOBCONTROL_H

typedef struct s_jobs
{
	pid_t			pid;
	int				idx;
	int				terminate;
	int				is_last;
	int				is_prelast;
	char			*cmd;
	char			*status;
	struct termios	tmodes;
	struct s_jobs	*next;
}				t_jobs;

/*
**	jobscreate.c
*/

t_jobs		*create_jobs(t_group *grp, char *cmd, int pid);
t_jobs		*get_jobs_idx(t_group *grp, int val);
t_jobs		*get_jobs_pid(t_group *grp, int pid);
t_jobs		*display_jobs(int idx, int pid, int n);

/*
**	jobsbuiltins.c
*/

int			builtin_jobs(t_group *grp);
int			builtin_fg(t_group *grp, int idx);
int			builtin_bg(t_group *grp, int idx);
void		put_in_fg(t_group *grp, t_jobs *curr);

/*
**	jobsstatus.c
*/

void		jobs_update(t_group *grp);
void		jobs_is_continued(t_group *grp);
void		change_state(t_jobs *jobs, int code);

#endif

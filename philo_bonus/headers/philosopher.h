/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:13:52 by gcrisp            #+#    #+#             */
/*   Updated: 2023/06/28 13:16:29 by gcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include "structs.h"
# include "enums.h"
# include "colours.h"
# include "errors.h"
# include "pthread.h"
# include <stdio.h>
# include <semaphore.h>
# include <unistd.h>
# include <sys/time.h>
# include <signal.h>

typedef struct s_phil
{
	t_phil_state	state;
	unsigned int	number;
	unsigned int	eat_times;
	t_args			*args;
	sem_t			*forks;
	sem_t			*fed;
	struct timeval	start_time;
	struct timeval	last_ate;
	pid_t			killswitch;
}	t_phil;

void	*philosopher(t_phil *data);
#endif

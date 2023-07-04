/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 08:58:09 by gcrisp            #+#    #+#             */
/*   Updated: 2023/06/29 11:09:47 by gcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void	do_nothing(void)
{
	while (1)
		usleep(10);
}

void	moniter(sem_t *fed, unsigned int num, pid_t *processes)
{
	while (num--)
		sem_wait(fed);
	kill(processes[0], SIGKILL);
	free(processes);
	do_nothing();
}

void	start_phils(t_args *args, pid_t *processes, sem_t *forks, sem_t *fed)
{
	t_phil			data;
	struct timeval	now;
	unsigned int	i;
	pid_t			ret;

	i = args->phil_num;
	gettimeofday(&now, 0);
	while (i--)
	{
		data = (t_phil){THINKING, i + 1, 0, args, forks, fed, now, now,
			processes[0]};
		if (i % 2)
			data.state = SLEEPING;
		ret = fork();
		if (ret)
			processes[i + 2] = ret;
		else
		{
			free(processes);
			philosopher(&data);
			do_nothing();
		}
	}
}

int	init(t_args *args, sem_t **forks, sem_t **fed, pid_t **processes)
{
	pid_t				ret;

	*forks = sem_open("forks", O_CREAT, 0660, args->phil_num);
	*fed = sem_open("fed", O_CREAT, 0660, 0);
	*processes = malloc(sizeof(pid_t) * (args->phil_num + 2));
	if (*forks == SEM_FAILED || *fed == SEM_FAILED || !*processes)
		return (1);
	ret = fork();
	if (ret)
		(*processes)[0] = ret;
	else
		do_nothing();
	ret = fork();
	if (ret)
		(*processes)[1] = ret;
	else
		moniter(*fed, args->phil_num, *processes);
	start_phils(args, *processes, *forks, *fed);
	return (0);
}

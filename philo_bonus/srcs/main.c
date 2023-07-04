/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 09:20:42 by gcrisp            #+#    #+#             */
/*   Updated: 2023/06/29 09:16:15 by gcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_input.h"
#include "structs.h"
#include "philosopher.h"
#include "init.h"
#include <signal.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <unistd.h>

void	cleanup(sem_t *forks, sem_t *fed, pid_t *processes, unsigned int n)
{
	if (forks)
		sem_close(forks);
	if (fed)
		sem_close(fed);
	if (!processes)
		return ;
	n += 2;
	while (n--)
		kill(processes[n], SIGKILL);
	free(processes);
}

int	main(int ac, char **av)
{
	t_args	args;
	sem_t	*forks;
	sem_t	*fed;
	pid_t	*processes;

	sem_unlink("forks");
	sem_unlink("fed");
	parse_input(ac, av, &args);
	if (init(&args, &forks, &fed, &processes))
	{
		cleanup(forks, fed, processes, args.phil_num);
		init_error();
	}
	waitpid(processes[0], 0, 0);
	cleanup(forks, fed, processes, args.phil_num);
}

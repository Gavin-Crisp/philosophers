/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 08:56:08 by gcrisp            #+#    #+#             */
/*   Updated: 2023/06/29 09:18:34 by gcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H
# include <semaphore.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <signal.h>
# include "structs.h"
# include "philosopher.h"

int	init(t_args *args, sem_t **forks, sem_t **fed, pid_t **processes);
#endif

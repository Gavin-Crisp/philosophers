/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 09:39:25 by gcrisp            #+#    #+#             */
/*   Updated: 2023/06/06 09:43:53 by gcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	init_error(void)
{
	printf(RED "Improper Initialization" RESET ": Program could not start du"
		"e to issue that occured setting up the simulation.\n");
	exit(2);
}

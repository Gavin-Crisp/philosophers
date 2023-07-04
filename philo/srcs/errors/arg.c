/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 09:33:16 by gcrisp            #+#    #+#             */
/*   Updated: 2023/06/06 09:34:47 by gcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	arg_error(void)
{
	printf(RED "Invalid Input" RESET ": Enter args in the order of -\n\t1)" CYAN
		" number_of_philosophers\n\t" RESET "2) " CYAN "time_to_die\n\t" RESET
		"3) " CYAN "time_to_eat\n\t" RESET "4) " CYAN "time_to_sleep\n\t" RESET
		"5) " CYAN "number_of_times_each_philosopher_must_eat" RESET " (optiona"
		"l)\nArgs must be positive integers.\nZero is " ITALICS "not" RESET " a"
		" positive integer.\n");
	exit(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:26:50 by gcrisp            #+#    #+#             */
/*   Updated: 2023/06/06 14:35:17 by gcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H
# include <sys/time.h>

int	get_mil_diff(struct timeval a, struct timeval b);
int	diff_from_now(struct timeval a);
#endif

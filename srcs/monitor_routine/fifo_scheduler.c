/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo_scheduler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 10:00:43 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/16 09:39:12 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <pthread.h>
#include "codexion.h"
#include "coder_routine.h"
#include "mutex_log_msg.h"

uint32_t	fifo_scheduler(uint32_t *available_dongles, uint32_t size, t_coder coders[size], uint32_t dongle_cooldown)
{
	uint32_t	min_compilations_done;
	uint64_t	i;
	(void)   dongle_cooldown;

	i = -1;
	min_compilations_done = coders[0].compilations_done;
	while (++i < size)
	{
		pthread_mutex_lock(&coders[i].local_mutex);
		if (coders[i].state & DONGLES_RELEASED)
			*available_dongles += TWO_DONGLES;
		coders[i].state &= ~(DONGLES_RELEASED);
		if (coders[i].state & WAITING_TO_COMPILE)
		{
			while (!(coders[i].state & TWO_DONGLES) && *available_dongles > 0)
			{
				(*available_dongles)--;
				coders[i].state += GIVE_ONE_DONGLE;
				mutex_log_msg(time_elapsed(0), coders[i].id, TAKEN_DONGLE_MSG, coders[i].global_mutex);
			}
		}
		if (coders[i].compilations_done < min_compilations_done)
			min_compilations_done = coders[i].compilations_done;
		pthread_mutex_unlock(&coders[i].local_mutex);
	}
	return (min_compilations_done);
}

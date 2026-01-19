/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schedule_fifo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 10:00:43 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/19 13:36:27 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <pthread.h>
#include "private_monitor_routine.h"

int	schedule_fifo(t_coder coders[], const t_monitor_config *config, uint32_t *available_dongles, t_coder **priority_coder)
{
	const uint32_t	ncoders = config->ncoders;
	const uint32_t	dongle_cooldown = config->dongle_cooldown;
	static uint64_t	priority_coder_idx = 0;
	uint64_t		i;

	i = -1;
	while (++i < ncoders)
	{
		pthread_mutex_lock(&coders[i].local_mutex);
		if (coders[i].execution_remaining == 0)
		{
			*priority_coder = &coders[i];
			return (STOP_SIMULATION);
		}
		if (required_compilations(##TODO##) == TRUE)
		{
			*priority_coder = NULL;
			return (STOP_SIMULATION);
		}
		*available_dongles += collect_released_dongles(&coders[i].compilations_history, dongle_cooldown);
		pthread_mutex_unlock(&coders[i].local_mutex);
	}
	priority_coder_idx %= ncoders;
	*priority_coder = &coders[priority_coder_idx++];
	return (CONTINUE_SIMULATION);
}

{
	uint32_t	min_compilations_done;
	uint64_t	i;
	(void)   dongle_cooldown;	// remove me

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

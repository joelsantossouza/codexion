/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:37:06 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/18 21:43:02 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include "private_monitor_routine.h"

void	*start_monitoring(t_coder coders[])
{
	const t_monitor_config	*config = monitor_config(NULL, NULL, NULL, NULL);
	const t_scheduler		scheduler = config->scheduler;
	uint32_t				available_dongles;
	t_coder					*priority_coder;

	available_dongles = config->ncoders;
	while (TRUE)
	{
		
		if (scheduler(coders, config, &available_dongles, &priority_coder) == STOP_SIMULATION)
		{
			// TODO: set all coder as dead, then print the priority_coder that die
		}
		pthread_mutex_lock(&priority_coder->local_mutex);
		if (priority_coder->state & WAITING_TO_COMPILE)
		{
			while (!(priority_coder->state & TWO_DONGLES) && available_dongles > 0)
			{
				available_dongles--;
				priority_coder->state += ONE_DONGLE;
				mutex_log_msg(time_elapsed(0), priority_coder->id, TAKEN_DONGLE_MSG, priority_coder->global_mutex);
			}
		}
		pthread_mutex_unlock(&priority_coder->local_mutex);
	}
}

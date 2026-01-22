/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:37:06 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/22 11:13:01 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include "private_monitor_routine.h"
#include "private_coder_routine.h"

void	*start_monitoring(t_coder coders[])
{
	const t_monitor_config	*config = monitor_config(NULL, NULL, NULL, NULL);
	const t_scheduler		scheduler = config->scheduler; // WARNING: MAYBE UNSED
	uint32_t				available_dongles;
	t_coder					*priority_coder;

	available_dongles = config->ncoders;
	while (TRUE)
	{
		/*I THINK THAT SCHEDULER SHOULD ONLY RETURN WHEN THE PRIORITY CODER 
		 *CAN ACTUALLY TAKE TWO AVAILABLE DONGLES BECAUSE IT WILL CONTINUE
		 RETURNING THE SAME CODER UNTIL IT ACTUALLY COMPILES

		 GET PRIORITY CODER, LOOP TO COLLECT DONGLES UNTIL HAVE TWO DONGLES
		 AVAILABLE TO PRIORITY, GIVE THEM TO PRIORITY

		 INSIDE THE SCHEDULE_EDF, HAS A QUEUE THAT HOLDS THE ORDER OF DEADLINES
		 OF CODERS, WHEN YOU CALL THE FUNCTION RETURN THE ONE THAT IS CLOSER TO
		 DIE*/
		if (scheduler(coders, config, &available_dongles, &priority_coder) == STOP_SIMULATION)
			return (stop_simulation(config->ncoders, coders, priority_coder));
		pthread_mutex_lock(&priority_coder->local_mutex);
		// if (priority_coder->state & WAITING_TO_COMPILE)
		// {
			while (!(priority_coder->state & TWO_DONGLES) && available_dongles > 0)
			{
				available_dongles--;
				priority_coder->state += ONE_DONGLE;
				log_coder_activity(priority_coder, TAKEN_DONGLE_MSG);
			}
		// }
		pthread_mutex_unlock(&priority_coder->local_mutex);
	}
}

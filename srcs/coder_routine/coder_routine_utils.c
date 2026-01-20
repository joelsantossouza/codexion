/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:40:53 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/20 10:15:09 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdint.h>
#include <unistd.h>
#include "private_coder_routine.h"

const t_coder_config	*coder_config(const uint32_t *compile, const uint32_t *debug, const uint32_t *refactor, const uint32_t *burnout)
{
	static t_coder_config	coder_config;

	if (compile)
		coder_config.tasks[COMPILE] = *compile;
	if (debug)
		coder_config.tasks[DEBUG] = *debug;
	if (refactor)
		coder_config.tasks[REFACTOR] = *refactor;
	if (burnout)
		coder_config.burnout = *burnout;
	return ((const  t_coder_config *)&coder_config);
}

int	wait_to_compile(t_coder	*coder)
{
	uint64_t	last_time;
	uint64_t	current_time;
	uint64_t	elapsed_time;

	last_time = millis();
	mutex_set_flag(&coder->state, WAITING_TO_COMPILE, &coder->local_mutex);
	while (TRUE)
	{
		current_time = millis();
		elapsed_time = current_time - last_time;
		last_time = current_time;
		pthread_mutex_lock(&coder->local_mutex);
		if (elapsed_time >= coder->execution_remaining)
		{
			coder->execution_remaining = 0;
			return (pthread_mutex_unlock(&coder->local_mutex), CODER_STOP);
		}
		coder->execution_remaining -= elapsed_time;
		if (coder->state & TWO_DONGLES)
		{
			coder->state &= ~(WAITING_TO_COMPILE | TWO_DONGLES);
			return (pthread_mutex_unlock(&coder->local_mutex), CODER_CONTINUE);
		}
		pthread_mutex_unlock(&coder->local_mutex);
	}
}

void	do_task(t_coder *coder)
{
	if (*time_left == 0)
		return ;
	if (time < *time_left)
	{
		*time_left -= time;
		usleep(time);
		return ;
	}
	usleep(*time_left);
	*time_left = 0;
}

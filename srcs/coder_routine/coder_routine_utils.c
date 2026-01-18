/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:40:53 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/18 14:21:10 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdint.h>
#include <unistd.h>
#include "codexion.h"
#include "coder_routine.h"
#include "mutex_set_flag.h"

const t_coder_config	*coder_config(uint32_t *compile, uint32_t *debug, uint32_t *refactor, uint32_t *burnout)
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

int	wait_to_compile(uint8_t *coder_state, pthread_mutex_t *mutex, uint32_t *time_left)
{
	uint64_t	last_time;
	uint64_t	current_time;
	uint64_t	elapsed_time;

	if (*time_left == 0)
		return (FALSE);
	last_time = millis();
	mutex_set_flag(coder_state, WAITING_TO_COMPILE, mutex);
	while (TRUE)
	{
		pthread_mutex_lock(mutex);
		if (*coder_state & TWO_DONGLES)
			break ;
		pthread_mutex_unlock(mutex);
		current_time = millis();
		elapsed_time = current_time - last_time;
		if (elapsed_time >= *time_left)
			return (*time_left = 0, FALSE);
		*time_left -= elapsed_time;
		last_time = current_time;
	}
	*coder_state &= ~(WAITING_TO_COMPILE | TWO_DONGLES);
	return (pthread_mutex_unlock(mutex), TRUE);
}

void	spend_time(uint32_t time, uint32_t *time_left)
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

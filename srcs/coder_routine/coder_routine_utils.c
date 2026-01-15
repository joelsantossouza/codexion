/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:40:53 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/15 11:13:29 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdint.h>
#include "codexion.h"
#include "mutex_set_flag.h"

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
		if (*coder_state & READY_TO_COMPILE)
			break ;
		pthread_mutex_unlock(mutex);
		current_time = millis();
		elapsed_time = current_time - last_time;
		if (elapsed_time >= *time_left)
			return (*time_left = 0, FALSE);
		*time_left -= elapsed_time;
		last_time = current_time;
	}
	*coder_state &= ~(WAITING_TO_COMPILE | READY_TO_COMPILE);
	return (pthread_mutex_unlock(mutex), TRUE);
}

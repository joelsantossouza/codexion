/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timed_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:27:17 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/09 15:45:03 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

int	timed_wait(uint8_t *is_ready_flag, pthread_mutex_t *mutex, uint32_t *time_left)
{
	uint64_t	last_time;
	uint64_t	current_time;
	uint64_t	elapsed_time;

	if (*time_left == 0)
		return (FALSE);
	last_time = millis();
	while (TRUE)
	{
		pthread_mutex_lock(mutex);
		if (*is_ready_flag == TRUE)
			return (pthread_mutex_unlock(mutex), TRUE);
		pthread_mutex_unlock(mutex);
		current_time = millis();
		elapsed_time = current_time - last_time;
		if (*time_left <= elapsed_time)
		{
			*time_left = 0;
			return (FALSE);
		}
		*time_left -= elapsed_time;
		last_time = current_time;
	}
}

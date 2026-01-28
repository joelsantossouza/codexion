/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_two_dongles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:56:47 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/28 12:13:42 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_control.h"

static inline
enum e_simulation_status	wait_dongle_cooldown(t_dongle *dongle)
{
	uint64_t	time_elapsed;

	pthread_mutex_lock();
	time_elapsed = millis() - dongle->last_release_ms;
	pthread_mutex_unlock();
	if (time_elapsed >= dongle_cooldown)
		return (SIMULATION_RUNNING);
	return (monitored_wait(dongle_cooldown - time_elapsed, &deadline));
}

enum e_simulation_status	request_two_dongles(t_coder *coder)
{
	if (coder->wait_my_turn(coder) == SIMULATION_STOPPED)
		return (SIMULATION_STOPPED);
	if (wait_dongle_cooldown(coder->right_dongle) == SIMULATION_STOPPED)
		return (SIMULATION_STOPPED);
	if (wait_dongle_cooldown(coder->left_dongle) == SIMULATION_STOPPED)
		return (SIMULATION_STOPPED);
	return (SIMULATION_RUNNING);
}

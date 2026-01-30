/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_two_dongles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:56:47 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/29 23:52:45 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "dongle_protocols.h"
#include "simulation_control.h"
#include "time_utils.h"

static
enum e_simulation_status	wait_dongle_cooldown(const t_coder *coder, t_dongle *dongle)
{
	uint64_t	dongle_cooldown_end_ms;

	pthread_mutex_lock(&dongle->mutex);
	dongle_cooldown_end_ms = dongle->cooldown_end_ms;
	pthread_mutex_unlock(&dongle->mutex);
	if (millis() >= dongle_cooldown_end_ms)
		return (SIMULATION_RUNNING);
	return (monitored_wait_until(dongle_cooldown_end_ms, coder->deadline_ms));
}

enum e_simulation_status	request_two_dongles(t_coder *coder)
{
	if (coder->wait_my_turn(coder) == SIMULATION_STOPPED)
		return (SIMULATION_STOPPED);
	if (wait_dongle_cooldown(coder, coder->right_dongle) == SIMULATION_STOPPED)
		return (SIMULATION_STOPPED);
	if (wait_dongle_cooldown(coder, coder->left_dongle) == SIMULATION_STOPPED)
		return (SIMULATION_STOPPED);
	return (SIMULATION_RUNNING);
}

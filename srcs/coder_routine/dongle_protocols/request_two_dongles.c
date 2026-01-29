/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_two_dongles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:56:47 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/29 20:22:59 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dongle_protocols.h"
#include "simulation_control.h"

static
enum e_simulation_status	wait_dongle_cooldown(const t_coder *coder, const t_dongle *dongle)
{
	uint64_t	dongle_cooldown_end_ms;

	pthread_mutex_lock();
	dongle_cooldown_end_ms = dongle->cooldown_end_ms;
	pthread_mutex_unlock();
	if (millis() >= dongle_cooldown_end_ms)
		return (SIMULATION_RUNNING);
	return (monitored_wait_until(dongle_cooldown_end_ms, &coder->deadline_ms));
}

enum e_simulation_status	request_two_dongles(const t_coder *coder)
{
	if (coder->wait_my_turn(coder) == SIMULATION_STOPPED)
		return (SIMULATION_STOPPED);
	if (wait_dongle_cooldown(coder, coder->right_dongle) == SIMULATION_STOPPED)
		return (SIMULATION_STOPPED);
	if (wait_dongle_cooldown(coder, coder->left_dongle) == SIMULATION_STOPPED)
		return (SIMULATION_STOPPED);
	return (SIMULATION_RUNNING);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitored_wait_until.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 23:45:22 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/10 09:48:41 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>
#include "simulation_control.h"
#include "time_utils.h"

#define MONITOR_INTERVAL_US	500

enum e_simulation_status	monitored_wait_until(uint64_t wait_until_ms,
												uint64_t limit_ms)
{
	if (wait_until_ms > limit_ms)
		wait_until_ms = limit_ms;
	while (millis() < wait_until_ms)
	{
		if (is_simulation_running() == false)
			return (SIMULATION_STOPPED);
		usleep(MONITOR_INTERVAL_US);
	}
	if (millis() >= limit_ms)
		return (SIMULATION_STOPPED);
	return (SIMULATION_RUNNING);
}

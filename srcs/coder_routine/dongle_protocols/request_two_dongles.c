/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_two_dongles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:56:47 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/27 18:49:44 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_control.h"

enum e_simulation_status request_two_dongles(t_coder *coder)
{
	if (coder->wait_my_turn(coder) == SIMULATION_STOPPED)
		return (SIMULATION_STOPPED);
	if (coder->wait_dongle_cooldown(coder->right_dongle) == SIMULATION_STOPPED)
		return (SIMUALTION_STOPPED);
	coder->take_dongle(coder->right_dongle);
	if (coder->wait_dongle_cooldown(coder->left_dongle) == SIMULATION_STOPPED)
		return (SIMUALTION_STOPPED);
	coder->take_dongle(coder->left_dongle);
	return (SIMULATION_RUNNING);
}

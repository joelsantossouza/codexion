/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_two_dongles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:57:46 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/29 20:28:17 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dongle_protocols.h"

static
void	release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock();
	dongle->cooldown_end_ms = millis() + dongle->cooldown;
	pthread_mutex_unlock();
	dequeue(&dongle->queue);
}

void	release_two_dongles(t_coder *coder)
{
	release_dongle(coder->left_dongle);
	release_dongle(coder->right_dongle);
	pthread_cond_broadcast();
	pthread_cond_broadcast();
}

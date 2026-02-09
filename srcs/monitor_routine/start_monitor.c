/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:11:46 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/09 16:36:55 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	start_monitor(pthread_t *monitor_thread, t_coder coders[])
{
	return (pthread_create(
		monitor_thread, NULL, (t_routine)monitor_routine, coders
	));
}

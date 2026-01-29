/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 11:35:37 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/29 11:38:52 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "time_utils.h"

uint64_t	timestamp_ms(uint64_t set_start)
{
	static uint64_t	start = 0;

	if (set_start > 0)
		start = set_start;
	return (millis() - start);
}

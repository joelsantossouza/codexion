/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:46:00 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/18 13:00:24 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_ROUTINE_H
# define MONITOR_ROUTINE_H

# include <stdint.h>
# include "codexion.h"

int	monitor_config(uint32_t *ncoders, uint32_t *cooldown, uint32_t *ncompiles_required, t_scheduler *scheduler_func);

#endif

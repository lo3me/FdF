/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:25:13 by mmomeni           #+#    #+#             */
/*   Updated: 2023/07/09 20:27:53 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

void	key_hook(mlx_key_data_t data, void *param);
void	scroll_hook(double xdelta, double ydelta, void *param);
void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
			void *param);
void	cursor_hook(double xpos, double ypos, void *param);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:06:28 by luigi             #+#    #+#             */
/*   Updated: 2024/10/03 14:10:55 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void range_z(t_point *point)
{
	if (point->z > point->z_max)
		point->z_max = point->z;
	if (point->z < point->z_min)
		point->z_min = point->z;
}
//no fundo quero percorrer o meu mapa e decidir o z_min e o z_max
//em seguida eu vou aplicar cor especifica para o minimo e o maximo
//e o que estiver entre esses numeros vai ser a variacao entre esses dois pontos

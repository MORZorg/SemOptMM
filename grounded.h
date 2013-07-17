/*
 * grounded.h
 *
 *  Created on: 15/lug/2013
 *      Author: ilariamartinelli
 */

#ifndef GROUNDED_H_
#define GROUNDED_H_
#include "SetArguments.h"

SetArguments get_not_attacked_nodes(SetArguments C, SetArguments I);
SetArguments get_attacked_from(SetArguments set, SetArguments N);
void grounded(AF gamma, SetArguments C, SetArguments *e, SetArguments *I);

#endif /* GROUNDED_H_ */

#ifndef INCFILE1_H_
#define INCFILE1_H_

#include <stdint.h>
#include "defines.h"

typedef void (*callBackFuncT)();

void initCoustomTimers();

void declareTimer(uint8_t i, uint8_t duration, callBackFuncT callback);

void startTimer(uint8_t i);

void deleteTimer(uint8_t i);

#endif /* INCFILE1_H_ */
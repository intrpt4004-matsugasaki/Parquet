#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
	void (* Panic)(const uint8_t *colour, const uint8_t *message);
} _Error;

extern _Error Error;

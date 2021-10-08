#include "Scraper/Error.h"

static void Panic(const uint8_t *colour, const uint8_t *message) {
	fprintf(stderr, u8"%s%s%s%s%s\n",
		u8"\e[31m",
		u8"[Error] ",
		colour,
		message,
		u8"\e[39m"
	);
}

_Error Error = {
	.Panic = Panic,
};

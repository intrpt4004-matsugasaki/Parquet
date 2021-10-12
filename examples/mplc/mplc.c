#include <Scraper.h>

#include "MPLParser.h"
#include "TokenCollector.h"

void main(const int32_t argc, uint8_t *argv[]) {
	TokenCollector_t *col = MPLParser.Invoke(String.FromFile(argv[1]));
	col->PrintTokens(col);
}

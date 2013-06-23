#include "stdint.h"


// css1.dat file information from
// http://www.strategyplanet.com/rctuk/tid/css1dat.html

struct css1_header {
	uint32_t NumberOfSounds;
	uint32_t *OffsetList;
	uint32_t DataSize;
};

int parse_header(FILE *fp, struct css1_header *header);
int parse_wav_header(FILE *fp);
int parse_wav_data(FILE *fp);

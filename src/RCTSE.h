#include "stdint.h"


// css1.dat file information from
// http://www.strategyplanet.com/rctuk/tid/css1dat.html

struct css1_header {
	uint32_t NumberOfSounds;
	uint32_t *OffsetList;
	uint32_t DataSize;
};

struct wav_header {
	uint16_t wFormatTag;
	uint16_t wChannels;
	uint32_t dwSamplesPerSec;
	uint32_t dwAvgBytesPerSec;
	uint16_t wBlockAlign;
	uint16_t wBitsPerSample;
};


int parse_header(FILE *fp, struct css1_header *header);
int parse_wav_header(FILE *fp, struct wav_header *header);
int parse_wav_data(FILE *fp, struct css1_header *header);

uint16_t get_WORD(FILE *fp);
uint32_t get_DWORD(FILE *fp);
void put_WORD(uint16_t WORD, FILE *fp);
void put_DWORD(uint32_t DWORD, FILE *fp);

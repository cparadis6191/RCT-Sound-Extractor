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

// Functions to deal with little endianess
uint16_t fgetWORD(FILE *fp);
uint32_t fgetDWORD(FILE *fp);
void fputWORD(uint16_t WORD, FILE *fp);
void fputDWORD(uint32_t DWORD, FILE *fp);

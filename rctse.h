#include <stdint.h>


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


struct css1_header* parse_header(FILE *fp);
struct wav_header* parse_wav_header(FILE *fp);
uint16_t* parse_wav_data(FILE *fp, size_t offset_start, size_t offset_end);

int put_wav_header(FILE *fp, struct wav_header *w_header, size_t data_size);
int put_wav_data(FILE *fp, uint16_t *data, size_t offset_start, size_t offset_end);

// Functions to deal with little endianess
uint16_t fgetWORD(FILE *fp);
uint32_t fgetDWORD(FILE *fp);
void fputWORD(uint16_t WORD, FILE *fp);
void fputDWORD(uint32_t DWORD, FILE *fp);

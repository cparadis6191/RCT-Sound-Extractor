#include <stdio.h>
#include <stdlib.h>

#include "RCTSE.h"


int main(void) {
	FILE *fp = fopen("../Css1.dat", "r");
	FILE *out = fopen("test.wav", "w");
	uint16_t *data;
	struct css1_header *c_header;
	struct wav_header *w_header;
	size_t data_size;

	if (fp == NULL) {
		fputs("File error", stderr);
		exit(1);
	}

	c_header = parse_header(fp);
	w_header = parse_wav_header(fp);

	data_size = c_header->OffsetList[1] - c_header->OffsetList[0];
	data = parse_wav_data(fp, c_header->OffsetList[0], c_header->OffsetList[1]);


	if (out == NULL) {
		fputs("File error", stderr);
		exit(1);
	}

	put_wav_header(out, w_header, data_size);
	put_wav_data(out, data, c_header->OffsetList[0], c_header->OffsetList[1]);

	free(c_header->OffsetList);
	free(data);
	fclose(out);
	fclose(fp);


	return 0;
}


struct css1_header* parse_header(FILE *fp) {
	struct css1_header* c_header = malloc(sizeof(struct css1_header));
	// Parse NumberOfSounds
	c_header->NumberOfSounds = fgetDWORD(fp);
	// TODO
	printf("NumberOfSounds: %i\n", c_header->NumberOfSounds);

	// Populate OffsetList
	c_header->OffsetList = calloc(c_header->NumberOfSounds, sizeof(uint32_t));

	for (unsigned int i = 0; i < c_header->NumberOfSounds; i++) {
		c_header->OffsetList[i] = fgetDWORD(fp);

		if (i == 0) {
			printf("Offset %i: %i\n", i, c_header->OffsetList[i] - c_header->OffsetList[i]);
		} else {
			printf("Offset %i: %i\n", i, c_header->OffsetList[i] - c_header->OffsetList[i - 1]);
		}
	}

	// Parse DataSize
	c_header->DataSize = fgetDWORD(fp);

	// TODO
	printf("DataSize: %i\n", c_header->DataSize);


	return c_header;
}

struct wav_header* parse_wav_header(FILE *fp) {
	struct wav_header* w_header = malloc(sizeof(struct wav_header));

	// Populate the wav_header struct
	w_header->wFormatTag = fgetWORD(fp);
	printf("%i\n", w_header->wFormatTag);
	w_header->wChannels = fgetWORD(fp);
	printf("%i\n", w_header->wChannels);
	w_header->dwSamplesPerSec = fgetDWORD(fp);
	printf("%i\n", w_header->dwSamplesPerSec);
	w_header->dwAvgBytesPerSec = fgetDWORD(fp);
	printf("%i\n", w_header->dwAvgBytesPerSec);
	w_header->wBlockAlign = fgetWORD(fp);
	printf("%i\n", w_header->wBlockAlign);
	w_header->wBitsPerSample = fgetWORD(fp);
	printf("%i\n", w_header->wBitsPerSample);


	return w_header;
}

// TODO get a single song first
uint16_t* parse_wav_data(FILE *fp, size_t offset_start, size_t offset_end) {
	// fp should be at the first bit of actual data
	// 16-bit samples

	// Move fp to first word of data
	fseek(fp, offset_start, SEEK_SET);
	uint16_t *buffer = malloc((offset_end - offset_start)*sizeof(uint16_t));
	fread(buffer, sizeof(uint16_t), (offset_end - offset_start), fp);


	return buffer;
}

int put_wav_header(FILE *fp, struct wav_header *w_header, size_t data_size) {
	// RIFF chunk descriptor
	fputs("RIFF", fp);
	fputDWORD(2*data_size + 31, fp);	// TODO Size 36 + SubChunk2Size
	fputs("WAVE", fp);	// format

	// fmt sub-chunk
	fputs("fmt", fp), fputc('\0', fp);			// Format chunk marker including null
	fputWORD(16, fp);							// Size of format data
	fputWORD(w_header->wFormatTag, fp);			// Type of format
	fputWORD(w_header->wChannels, fp);			// Mono/stereo
	fputDWORD(w_header->dwSamplesPerSec, fp);	// Sample rate
	fputDWORD(w_header->dwAvgBytesPerSec, fp);	// Byte rate
	fputWORD(w_header->wBlockAlign, fp);		// Block align
	fputWORD(w_header->wBitsPerSample, fp);		// Bits per sample

	// Data sub-chunk
	fputs("data", fp);			// Data description header
	fputDWORD(2*data_size, fp);	// Size of data bytes

	// Data


	return 0;
}

int put_wav_data(FILE *fp, uint16_t *data, size_t offset_start, size_t offset_end) {
	fwrite(data, sizeof(uint16_t), offset_end - offset_start, fp);


	return 0;
}


uint16_t fgetWORD(FILE *fp) {
	uint16_t WORD;

	WORD = fgetc(fp);
	WORD |= fgetc(fp) << 8;


	return WORD;
}

uint32_t fgetDWORD(FILE *fp) {
	uint32_t DWORD;

	DWORD = fgetc(fp);
	DWORD |= fgetc(fp) << 8;
	DWORD |= fgetc(fp) << 16;
	DWORD |= fgetc(fp) << 24;


	return DWORD;
}

void fputWORD(uint16_t WORD, FILE *fp) {
	fputc(WORD&0xff, fp);
	fputc(WORD >> 8, fp);


	return;
}

void fputDWORD(uint32_t DWORD, FILE *fp) {
	fputc((DWORD >> 0)&0xff, fp);
	fputc((DWORD >> 8)&0xff, fp);
	fputc((DWORD >> 16)&0xff, fp);
	fputc((DWORD >> 24)&0xff, fp);


	return;
}

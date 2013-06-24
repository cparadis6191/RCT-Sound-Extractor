#include <stdio.h>
#include <stdlib.h>

#include "RCTSE.h"


int main(void) {
	FILE *fp = fopen("../Css1.dat", "r");
	struct css1_header c_header;
	struct wav_header w_header;

	if (fp == NULL) {
		fputs("File error", stderr);
		exit(1);
	}

	parse_header(fp, &c_header);
	parse_wav_header(fp, &w_header);
	parse_wav_data(fp, &c_header);



	return 0;
}


int parse_header(FILE *fp, struct css1_header *header) {
	// Parse NumberOfSounds
	header->NumberOfSounds = fgetDWORD(fp);
	// TODO
	printf("NumberOfSounds: %i\n", header->NumberOfSounds);

	// Populate OffsetList
	header->OffsetList = calloc(header->NumberOfSounds, sizeof(uint32_t));

	for (int i = 0; i < header->NumberOfSounds; i++) {
		header->OffsetList[i] = fgetDWORD(fp);

		if (i == 0) {
			printf("Offset %i: %i\n", i, header->OffsetList[i] - header->OffsetList[i]);
		} else {
			printf("Offset %i: %i\n", i, header->OffsetList[i] - header->OffsetList[i - 1]);
		}
	}

	// Parse DataSize
	header->DataSize = fgetDWORD(fp);

	// TODO
	printf("DataSize: %i\n", header->DataSize);


	return 0;
}

int parse_wav_header(FILE *fp, struct wav_header *header) {
	// Populate the wav_header struct
	header->wFormatTag = fgetWORD(fp);
	printf("%i\n", header->wFormatTag);
	header->wChannels = fgetWORD(fp);
	printf("%i\n", header->wChannels);
	header->dwSamplesPerSec = fgetDWORD(fp);
	printf("%i\n", header->dwSamplesPerSec);
	header->dwAvgBytesPerSec = fgetDWORD(fp);
	printf("%i\n", header->dwAvgBytesPerSec);
	header->wBlockAlign = fgetWORD(fp);
	printf("%i\n", header->wBlockAlign);
	header->wBitsPerSample = fgetWORD(fp);
	printf("%i\n", header->wBitsPerSample);


	return 0;
}

// TODO get a single song first
int parse_wav_data(FILE *fp, struct css1_header *header) {
	// Start back at the beginning
	// fp should be at the first bit of actual data
	// 16-bit samples
	uint16_t *buffer = malloc((header->OffsetList[1] - header->OffsetList[0])*sizeof(uint16_t));

	FILE *out = fopen("test.wav", "w");

	// TODO
	// Write the incomplete wav header
	fputWORD(1, out);
	fputWORD(1, out);
	fputDWORD(22050, out);
	fputDWORD(44100, out);
	fputWORD(2, out);
	fputWORD(16, out);

	fwrite(buffer, sizeof(uint16_t), (header->OffsetList[1] - header->OffsetList[0]), out);

	fclose(out);




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

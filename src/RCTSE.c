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
	header->NumberOfSounds = get_DWORD(fp);
	// TODO
	printf("NumberOfSounds: %i\n", header->NumberOfSounds);

	// Populate OffsetList
	header->OffsetList = calloc(header->NumberOfSounds, sizeof(uint32_t));

	for (int i = 0; i < header->NumberOfSounds; i++) {
		header->OffsetList[i] = get_DWORD(fp);

		if (i == 0) {
			printf("Offset %i: %i\n", i, header->OffsetList[i] - header->OffsetList[i]);
		} else {
			printf("Offset %i: %i\n", i, header->OffsetList[i] - header->OffsetList[i - 1]);
		}
	}

	// Parse DataSize
	header->DataSize = get_DWORD(fp);

	// TODO
	printf("DataSize: %i\n", header->DataSize);


	return 0;
}

int parse_wav_header(FILE *fp, struct wav_header *header) {
	// Populate the wav_header struct
	header->wFormatTag = get_WORD(fp);
	printf("%i\n", header->wFormatTag);
	header->wChannels = get_WORD(fp);
	printf("%i\n", header->wChannels);
	header->dwSamplesPerSec = get_DWORD(fp);
	printf("%i\n", header->dwSamplesPerSec);
	header->dwAvgBytesPerSec = get_DWORD(fp);
	printf("%i\n", header->dwAvgBytesPerSec);
	header->wBlockAlign = get_WORD(fp);
	printf("%i\n", header->wBlockAlign);
	header->wBitsPerSample = get_WORD(fp);
	printf("%i\n", header->wBitsPerSample);


	return 0;
}

// TODO get a single song first
int parse_wav_data(FILE *fp, struct css1_header *header) {
	// Start back at the beginning
	// fp should be at the first bit of actual data
	// 16-bit samples
	uint16_t *buffer = malloc((header->OffsetList[1] - header->OffsetList[0])*sizeof(uint16_t));

	// Hopefully read in the right amount of data
	fread(buffer, sizeof(uint16_t), (header->OffsetList[1] - header->OffsetList[0]), fp);

	for (int i = 0; i < 99; i++) {
		printf("%x\n", buffer[i]);
	}

	fopen("test.wav", "w");




	return 0;
}

uint16_t get_WORD(FILE *fp) {
	uint16_t WORD;

	WORD = fgetc(fp);
	WORD |= fgetc(fp) << 8;


	return WORD;
}

uint32_t get_DWORD(FILE *fp) {
	uint32_t DWORD;

	DWORD = fgetc(fp);
	DWORD |= fgetc(fp) << 8;
	DWORD |= fgetc(fp) << 16;
	DWORD |= fgetc(fp) << 24;


	return DWORD;
}

void put_WORD(uint16_t WORD, FILE *fp) {


	return;
}

void put_DWORD(uint32_t DWORD, FILE *fp) {

	return;
}


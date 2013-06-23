#include <stdio.h>
#include <stdlib.h>

#include "RCTSE.h"


int main(void) {
	FILE *fp = fopen("../Css1.dat", "r");
	struct css1_header header;

	if (fp == NULL) {
		fputs("File error", stderr);
		exit(1);
	}

	parse_header(fp, &header);
	parse_wav_header(fp);
	parse_wav_data(fp);



	return 0;
}


int parse_header(FILE *fp, struct css1_header *header) {
	header->NumberOfSounds = 0;

	for (int i = 0; i <= 3; i++) {
		header->NumberOfSounds |= fgetc(fp) << i*8;
	}

	header->OffsetList = malloc(header->NumberOfSounds*sizeof(uint32_t));



	return 0;
}

int parse_wav_header(FILE *fp) {


	return 0;
}

int parse_wav_data(FILE *fp) {


	return 0;
}

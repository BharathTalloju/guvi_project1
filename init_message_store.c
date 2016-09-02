#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	FILE * fp = fopen("messagestore", "w");
	fputc(0, fp);
	fclose(fp);
	return 0;
}

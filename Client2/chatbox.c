#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define FILE_NAME "/home/BharathTalloju/Documents/MissionRnD/PostSummer/ChatBox/messagestore"

void *write_message(void *a);
void *display_messages();

int main(int argc, char const *argv[]) {

	char message_buffer[1024];
	pthread_t display_thread, t;

	pthread_create(&display_thread, NULL, &display_messages, NULL);

	while (1) {
		gets(message_buffer);
		pthread_create(&t , NULL, &write_message, (void *)&message_buffer);
	}

	pthread_exit(NULL);
}

void *write_message(void *a){
	char *user_tag = "client2: ";
	char *message = (char *)a;
	FILE *fp = fopen(FILE_NAME, "r+");

	fputc('1', fp);
	fseek(fp, 0, SEEK_END);
	fprintf(fp, "%s%s\n", user_tag, message);
	fseek(fp, 0 , SEEK_SET);
	fputc(0, fp);
	fclose(fp);
	pthread_exit(NULL);
}

void *display_messages(){
	FILE *fp = NULL;

	while(1){
		fp = fopen(FILE_NAME, "r");

		//wait till updated
		while(!fgetc(fp)){
			//wait
			fclose(fp);
			fp = fopen(FILE_NAME, "r");
		}
		fclose(fp);

		fp = fopen(FILE_NAME, "r");

		//wait while updating
		while(fgetc(fp)){

			fclose(fp);
			fp = fopen(FILE_NAME, "r");
		}

		//print messages
		system("clear");
		printf("Messages: \n");
		fseek(fp, 1, SEEK_SET);
		while (!feof(fp)) {
			putchar(fgetc(fp));
		}
		fclose(fp);

	}
	pthread_exit(NULL);
}

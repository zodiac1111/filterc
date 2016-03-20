#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include "def.h"
int main(int argc, char* argv[])
{
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read_size;
	char filename[MAX_FILE_PATH_LEN] = { 0 };
	sprintf(filename, "%s", argv[1]);
	fp = fopen(filename, "r");
	if (fp==NULL) {
		CLOG_ERR("open file fail");
		return -1;
	}
	while ((read_size = getline(&line, &len, fp))!=-1) {
		;
	}
	return 0;
}

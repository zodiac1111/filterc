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
	int ret;
	char filename[MAX_FILE_PATH_LEN] = { 0 };
	int taget_number = 0;
	int min = 0;
	int max = 0;
	if (argc!=3) {
		CLOG_ERR("./t <C tagfile> <line number>");
		return -1;
	}
	sprintf(filename, "%s", argv[1]);
	fp = fopen(filename, "r");
	if (fp==NULL) {
		CLOG_ERR("open file fail");
		return -1;
	}
	taget_number = atoi(argv[2]);
	while ((read_size = getline(&line, &len, fp))!=-1) {
		ret = sscanf(line, "%d,%d", &min, &max);
		if (ret!=2) {
			continue;
		}
		if (min==0&&max==0) {
			continue;
		}
		if ((min<taget_number)
			&&(max>taget_number)) {
			printf("%d\n", min);
			continue;
		}
		if (min>taget_number) {
			break;
		}
	}
	fclose(fp);
	return 0;
}

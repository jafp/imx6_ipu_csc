
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <linux/videodev2.h>
#include "ipu_csc.h"

int main() {
	
	ipu_csc_t csc;	
	ipu_csc_format_t input_format = { 1024, 768, 16, V4L2_PIX_FMT_YUYV };
	ipu_csc_format_t output_format = { 1024, 768, 24, V4L2_PIX_FMT_RGB24 };

	if (ipu_csc_init(&csc, &input_format, &output_format) < 0) {
		perror("ipu csc init failed");
		return -1;
	}

	// Load test image
	int file_fd;
	if ( (file_fd = open("freescale_1024x768_yuyv422.raw", O_RDWR, 0)) < 0) {
		printf("Could not open image file.\n");
		return -1;
	}
	int file_size = lseek(file_fd, 0, SEEK_END);
	void * raw_image = mmap(0, file_size, PROT_READ, MAP_SHARED, file_fd, 0);

	// Output buffer
	unsigned char output_image[ 1024 * 768 * 3 ];
	memset(output_image, 0, sizeof(output_image));

	if (ipu_csc_convert(&csc, raw_image, output_image) < 0) {
		perror("ipu_csc_convert");
	} else {
		printf("Conversion done.\n");
	}

	close(file_fd);
	ipu_csc_close(&csc);

	return 0;
}
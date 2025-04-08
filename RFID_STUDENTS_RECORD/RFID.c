#include "header.h"

#define SERIAL_PORT "/dev/ttyUSB0"
#define BUFFER_SIZE 256
#define EXPECTED_BYTES 12
#define SCREEN_WIDTH 80

/**
 * @brief Configures the serial port with necessary attributes.
 * @param fd File descriptor of the open serial port.
 * @return 0 on success, -1 on failure.
 */
static int configure_serial_port(int fd)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) != 0) {
        perror("Error getting serial port attributes");
        return -1;
    }

    tty.c_cflag &= ~PARENB;   // No parity bit
    tty.c_cflag &= ~CSTOPB;   // One stop bit
    tty.c_cflag &= ~CSIZE;    
    tty.c_cflag |= CS8;       // 8-bit characters
    tty.c_cflag &= ~CRTSCTS;  // Disable hardware flow control
    tty.c_cflag |= CREAD | CLOCAL; // Enable reading & ignore control lines

    tty.c_cc[VTIME] = 10;  // Timeout in deciseconds (1 second)
    tty.c_cc[VMIN] = 19;   // Minimum number of bytes to read

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("Error setting serial port attributes");
        return -1;
    }

    return 0;
}

/**
 * @brief Reads data from the serial port until an expected length is received.
 * @return A dynamically allocated string containing the scanned ID or NULL on failure.
 */
char *scanning(SDB *ptr,int flag)
{
    int serial_port = open(SERIAL_PORT, O_RDWR);
    if (serial_port < 0) {
        perror("Failed to open serial port");
        return NULL;
    }

    if (configure_serial_port(serial_port) != 0) {
        close(serial_port);
        return NULL;
    }

    char *rdbuf = (char *)malloc(BUFFER_SIZE);
    if (!rdbuf) {
        perror("Memory allocation failed");
        close(serial_port);
        return NULL;
    }

   printf("%*s Scanning...\n", (SCREEN_WIDTH - 10) / 2, "");

	while (1) {   
		int rfid=0; 
		memset(rdbuf, 0, BUFFER_SIZE);     
		int bytes_read = read(serial_port, rdbuf, BUFFER_SIZE - 1);   
		if(flag){
			while (ptr) {
				if (strncmp(ptr->RFID, rdbuf, 12) == 0) {
				    rfid=1; 
				    break;
				}
				ptr = ptr->next;
			} 
		}

		if(!rfid){
			if (bytes_read == EXPECTED_BYTES) {
				rdbuf[bytes_read] = '\0'; // Ensure null termination
				close(serial_port);
				return rdbuf;
			} else {
				printf("%*s Scan again\n", (SCREEN_WIDTH - 10) / 2, "");
				sleep(1);
			}
		}else {
			printf("%*s This card detail already exit,\n", (SCREEN_WIDTH - 10) / 2, "");
			printf("%*s Try another card...\n", (SCREEN_WIDTH - 10) / 2, "");
			sleep(1);
		}
	}

    free(rdbuf);
    close(serial_port);
    return NULL;
}

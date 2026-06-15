#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    // 1. Setup syslog logging using the LOG_USER facility
    openlog("writer", LOG_PID, LOG_USER);

    // 2. Check that exactly 2 arguments are given (plus the executable name itself)
    if (argc != 3) {
        syslog(LOG_ERR, "Error: Invalid number of arguments. Expected 2, got %d", argc - 1);
        fprintf(stderr, "Error: Two arguments required.\n");
        fprintf(stderr, "Usage: %s <writefile> <writestr>\n", argv[0]);
        closelog();
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    // 3. Log the attempt with LOG_DEBUG level
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    // 4. Open the file for writing using low-level I/O system calls
    // O_WRONLY: Write-only mode
    // O_CREAT: Create the file if it doesn't exist
    // O_TRUNC: Truncate (overwrite) the file if it already exists
    // 0644: Permissions (Read/Write for owner, Read for group/others)
    int fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        syslog(LOG_ERR, "Error: Failed to open/create file %s: %s", writefile, strerror(errno));
        perror("Error opening file");
        closelog();
        return 1;
    }

    // 5. Write the string to the file
    ssize_t bytes_written = write(fd, writestr, strlen(writestr));
    if (bytes_written == -1) {
        syslog(LOG_ERR, "Error: Failed to write to file %s: %s", writefile, strerror(errno));
        perror("Error writing to file");
        close(fd);
        closelog();
        return 1;
    }

    // 6. Clean up and close descriptors
    close(fd);
    closelog();

    return 0;
}

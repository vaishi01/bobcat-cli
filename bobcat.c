#include <err.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

bool process_input(const char *file_path);
bool write_all(int fd, const char *buffer, size_t count);

bool process_input(const char *file_path) {
  int fd;
  ssize_t bytes_read;
  struct stat statbuf;
  char buffer[BUFFER_SIZE] = {0};
  bool success = true;

  if (strcmp(file_path, "-") == 0) {
    fd = STDIN_FILENO;
  } else {
    if (stat(file_path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
      warnx("%s: Is a directory", file_path);
      return false;
    }
    fd = open(file_path, O_RDONLY);
    if (fd == -1) {
      warn("%s", file_path);
      return false;
    }
  }

  while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
    if (!write_all(STDOUT_FILENO, buffer, bytes_read)) {
      success = false;
      break;
    }
  }

  if (bytes_read == -1) {
    warn("%s", file_path);
    success = false;
  }

  if (fd != STDIN_FILENO) {
    close(fd);
  }
  return success;
}

bool write_all(int fd, const char *buffer, size_t count) {
  ssize_t bytes_written;
  size_t total_written = 0;

  while (total_written < count) {
    bytes_written = write(fd, buffer + total_written, count - total_written);
    if (bytes_written == -1) {
      warn("write error");
      return false;
    }
    total_written += bytes_written;
  }

  return true;
}

int main(int argc, char *argv[]) {
  bool success = true;

  if (argc == 1) {
    success &= process_input("-");
  } else {
    for (int i = 1; i < argc; i++) {
      success &= process_input(argv[i]);
    }
  }

  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}

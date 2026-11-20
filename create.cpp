#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include <cerrno>

void check(int result, const char* operation) {
    if (result == -1) { perror(operation); exit(1); }
}
void write_all(int fd, const char* data, size_t size) {
    while (size) {
        ssize_t n = write(fd, data, size);
        if (n < 0 && errno == EINTR) continue;
        if (n <= 0) { perror("write"); exit(1); }
        data += n; size -= static_cast<size_t>(n);
    }
}
int make_file(const char* path) {
    int fd = open(path, O_WRONLY | O_CREAT | O_EXCL, S_IRWXU);
    check(fd, path); return fd;
}
int main() {
    check(mkdir("StudyLab", S_IRWXU), "StudyLab");
    check(mkdir("StudyLab/notes", S_IRWXU), "notes");
    check(mkdir("StudyLab/data", S_IRWXU), "data");
    check(mkdir("StudyLab/archive", S_IRWXU), "archive");
    int fd = make_file("StudyLab/notes/topic.txt");
    const char text[] = "System programming\n";
    write_all(fd, text, sizeof(text) - 1); check(close(fd), "close");
    fd = make_file("StudyLab/notes/empty.txt"); check(close(fd), "close");
    fd = make_file("StudyLab/data/zeros.bin");
    check(ftruncate(fd, 64), "ftruncate"); check(close(fd), "close");
    int random = open("/dev/urandom", O_RDONLY); check(random, "urandom");
    fd = make_file("StudyLab/data/random.bin");
    char buffer[128]; size_t remaining = sizeof(buffer);
    while (remaining) {
        ssize_t n = read(random, buffer, remaining);
        if (n < 0 && errno == EINTR) continue;
        if (n <= 0) { perror("read"); return 1; }
        write_all(fd, buffer, static_cast<size_t>(n)); remaining -= static_cast<size_t>(n);
    }
    check(close(random), "close"); check(close(fd), "close");
    check(link("StudyLab/notes/topic.txt", "StudyLab/archive/topic_copy.txt"), "link");
    check(symlink("notes", "StudyLab/notes_link"), "symlink");
    return 0;
}

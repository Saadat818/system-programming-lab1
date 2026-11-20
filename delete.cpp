#include <unistd.h>
#include <cstdio>
#include <cstdlib>

void check(int result, const char* path) {
    if (result == -1) { perror(path); exit(1); }
}
int main() {
    check(unlink("StudyLab/notes_link"), "notes_link");
    check(unlink("StudyLab/archive/topic_copy.txt"), "topic_copy.txt");
    check(unlink("StudyLab/notes/topic.txt"), "topic.txt");
    check(unlink("StudyLab/notes/empty.txt"), "empty.txt");
    check(unlink("StudyLab/data/random.bin"), "random.bin");
    check(unlink("StudyLab/data/zeros.bin"), "zeros.bin");
    check(rmdir("StudyLab/archive"), "archive");
    check(rmdir("StudyLab/notes"), "notes");
    check(rmdir("StudyLab/data"), "data");
    check(rmdir("StudyLab"), "StudyLab");
}

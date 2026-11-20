#!/bin/sh
set -eu
mkdir StudyLab
mkdir StudyLab/notes StudyLab/data StudyLab/archive
printf 'System programming\n' > StudyLab/notes/topic.txt
touch StudyLab/notes/empty.txt
head -c 128 /dev/urandom > StudyLab/data/random.bin
dd if=/dev/zero of=StudyLab/data/zeros.bin bs=64 count=1 2>/dev/null
ln StudyLab/notes/topic.txt StudyLab/archive/topic_copy.txt
ln -s notes StudyLab/notes_link

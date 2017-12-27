#!/bin/bash
gcc applicant.c  -o applicant

gcc hr.c queue.c -pthread -o hr

gcc trial.c queue.c -pthread -o trial

chmod +x applicant

chmod +x hr

chmod +x trial

./applicant $2 & ./hr $1 & ./trial $1

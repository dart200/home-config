// Copyright (c) 2014 Datera, Inc.  All rights reserved.
// Datera, Inc. Confidential and Proprietary.

#include <sstream>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const static int BUF_SIZE = 1024;

int main (int argc, char* argv[])
{
    char* pid = argv[1];
    char* name = argv[2];
    //char* signal = argv[3];
    //char* time = argv[4];

    std::stringstream info_fname;
    info_fname << "/var/log/datera/core_info.PID" << pid << "." << name;
    FILE* core_info = fopen(info_fname.str().c_str(), "w+");

    std::stringstream cf_name;
    cf_name << "/var/log/datera/core.PID" << pid << "." << name;
    FILE* core_file = fopen(cf_name.str().c_str(), "w+");

    char buf[BUF_SIZE];

    int nr_read = 0;
    long total = 0;
    while ( (nr_read = fread(buf, 1, BUF_SIZE, stdin)) > 0) {
	total += nr_read;
	fwrite(buf, 1, nr_read, core_file);
    }

    fprintf(core_info, "Total size of core dump: %ldK\n", total/1024);

    if (feof(stdin))
	fprintf(core_info, "EOF reached, full core dumped\n");
    else
	fprintf(core_info, "Errored before EOF reached\n");

    fclose(core_info);
    fclose(core_file);
}

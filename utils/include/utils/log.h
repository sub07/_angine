#pragma once

#include <stdio.h>
#include <stdlib.h>

#ifndef NDEBUG
#define log_debug(format, ...) printf("[DEBUG LOG] "format"\n", ##__VA_ARGS__)
#define log_error(format, ...) fprintf(stderr, "[ERROR LOG] "format"\n", ##__VA_ARGS__)
#define abort_log(format, ...) log_error("[ABORTING] "format, ##__VA_ARGS__); exit(EXIT_FAILURE)
#define abort exit(EXIT_FAILURE)
#else
#define log_debug(format, ...)
#define log_error(format, ...)
#define abort_log(format, ...)
#define abort
#endif

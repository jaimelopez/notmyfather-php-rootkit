#ifndef ROOTKIT_CONFIG_H
#define ROOTKIT_CONFIG_H

#include "php.h"

#include "stdbool.h"
#define BOOL bool

// Rootkit configuration
#define ROOTKIT_NAME "rootkit"
#define ROOTKIT_VERSION "0.0.1"
#define ROOTKIT_AUTHOR "Jaime Lopez"
#define ROOTKIT_DEBUG 1

#if ROOTKIT_DEBUG == 1
#define ROOTKIT_PRINTF(...) { fprintf(stdout, __VA_ARGS__); fflush(stdout); }
#else
#define ROOTKIT_PRINTF(...) ((void)0)
#endif

extern zend_module_entry rootkit_module_entry;

#define phpext_rootkit_ptr &rootkit_module_entry

#endif
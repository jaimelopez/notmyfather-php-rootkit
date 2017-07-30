#ifndef ROOTKIT_HOOK_H
#define ROOTKIT_HOOK_H

#include "rootkit_config.h"

typedef struct
{
    bool execute_original;
    void (*original)(INTERNAL_FUNCTION_PARAMETERS);
    void (*hook)(INTERNAL_FUNCTION_PARAMETERS);
    const char *name;
} Hook;

bool rootkit_hook_function(
    const char *name,
    void (*hook),
    bool execute_original);

PHP_FUNCTION(hook_main_entry);

#endif
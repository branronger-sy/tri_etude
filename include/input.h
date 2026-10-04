#ifndef INPUT_H
#define INPUT_H

typedef enum {
    INPUT_RANDOM = 0,
    INPUT_SORTED,
    INPUT_REVERSE_SORTED,
    INPUT_NEARLY_SORTED,
    INPUT_MANY_DUPLICATES,
    INPUT_TYPE_COUNT
} InputType;

/**
 * Generate an array of size n with the given pattern.
 */
void generate_array(int *t, int n, InputType type);

/**
 * Save array to a binary file.
 * Returns 1 on success, 0 on failure.
 */
int save_array(const char *filename, const int *t, int n);

/**
 * Load array from a binary file.
 * Returns 1 on success, 0 on failure.
 */
int load_array(const char *filename, int *t, int n);

/**
 * Get human-readable name of the input type.
 */
const char *input_type_name(InputType type);

#endif /* INPUT_H */

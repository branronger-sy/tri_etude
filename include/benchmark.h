#ifndef BENCHMARK_H
#define BENCHMARK_H
typedef enum {
  INPUT_RANDOM = 0,
  INPUT_SORTED,
  INPUT_REVERSE_SORTED,
  INPUT_NEARLY_SORTED,
  INPUT_MANY_DUPLICATES,
  INPUT_TYPE_COUNT
} InputType;
void generate_array(int *t, int n, InputType type);
const char *input_type_name(InputType type);
const char *input_type_filename(InputType type);
int parse_input_type(const char *str);
void benchmark_run_demo(const char *type_str, const char *filter);
void benchmark_run_full(const char *type_str, const char *filter);
void benchmark_run_tests(const char *filter);
#endif

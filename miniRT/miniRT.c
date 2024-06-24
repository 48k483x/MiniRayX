#include "srcs/include/miniRT.h"

int main(int ac, char *av[])
{
	t_scene scene = {0};
	char	**sc;

	sc = NULL;
	if (ac != 2 || !_check_extension(av[1]))
		return error("Usage:./miniRT [scene_file]");
	sc = get_scene(av[1]);
	if (sc == NULL)
		return error_main("Can't read scene file", sc);
	if (!alc_num(sc))
		return error_main("Scene must contain one A, one C and one L", sc);
	if (!selecte(&scene, sc))
		return (error_main("Error in scene file", sc));
	print_scene(&scene);
	free_all_l(&scene);
	free_tab(sc);
}

// int main() {
//     char *tests[] = {
//         "123.45",    // Valid float
//         "12a3.45",   // Invalid character 'a'
//         "123.",      // Dot at the end
//         ".45",       // Dot at the beginning
//         "123",       // Valid integer
//         "-123.45",   // Valid negative float
//         "-.45",      // Invalid, dot directly after minus
//         "",          // Empty string
//         "-",         // Minus sign only
//         "123.45.67", // Multiple dots
//         "123..45",   // Consecutive dots
//         " 123.45",   // Leading space
//         "123.45 ",   // Trailing space
//         "123. 45",   // Space in the middle
//         "0.45",      // Valid float starting with zero
//         "-0.45",     // Valid negative float starting with zero
//         "00.45",     // Valid float with leading zero
//         "12345678901234567890.1234567890", // Very large number
//         "12345678901234567890.", // Very large number with dot at the end
//         "1234567890.", // Large number with dot at the end
//         "1234567890", // Large number without dot
//         ".1234567890", // Dot at the beginning with large number
//         "-.1234567890", // Negative dot at the beginning with large number
//         "12345.67890", // Valid large float
//         "1e10", // Scientific notation, should be invalid
//         "1.23e10", // Scientific notation, should be invalid
//         "-1.23e-10", // Scientific notation with negative exponent, should be invalid
//         "NaN", // Not a Number, should be invalid
//         "inf", // Infinity, should be invalid
//         "-inf" // Negative Infinity, should be invalid
//     };

//     int num_tests = sizeof(tests) / sizeof(tests[0]);
//     for (int i = 0; i < num_tests; i++) {
//         printf("Test %d: %s -> %d\n", i + 1, tests[i], is_digitf(tests[i]));
//     }

//     return 0;
// }
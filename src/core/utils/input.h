#ifndef INPUT_H
#define INPUT_H

static int parse_two_digits(char a, char b)
{
	int result = 0;
	if (a >= '0' && a <= '9') result = (a - '0');
	if (b >= '0' && b <= '9') result = result * 10 + (b - '0');
	return result;
}

#endif // INPUT_H

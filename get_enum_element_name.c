#define VALUE_TABLE \
	X(KZero, "Zero") \
	X(KOne, "One") \
	X(KTwo, "Two")

#define X(a, b) a,
enum EValue { VALUE_TABLE };
#undef X

const char* ToString(EValue value)
{
#define X(a, b) b,
	static char *table[] = { VALUE_TABLE };
#undef X
	return table[value];
}

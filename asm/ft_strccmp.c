#include "../includes/asm.h"

int		ft_strccmp(const char *s1, const char *s2, const char limit)
{
	while (*s1 && *s2 && *s1 == *s2 && *s2 != limit)
	{
		s1++;
		s2++;
	}
	if (*s1 == '\0' && *s2 == ' ')
		return ((unsigned char)*s1 + 32 - (unsigned char)*s2);
	if (*s2 == '\0' && *s1 == ' ')
		return ((unsigned char)*s1 - (unsigned char)*s2 + 32);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

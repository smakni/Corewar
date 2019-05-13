#include "../../includes/asm.h"

int		ft_strccmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2 && *s2 != ' ' && *s2 != '\t')
	{
		if (*s1 != *s2)
			return (-1);
		s1++;
		s2++;
	}
	return (0);
}

/*
int		ft_strccmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2 && *s2 != ' ' && *s2 != '\t')
	{
		s1++;
		s2++;
	}
	if (*s1 == '\0' && (*s2 == ' ' || *s2 == '\t'))
		return ((unsigned char)*s1 + 32 - (unsigned char)*s2);
	if (*s2 == '\0' && (*s1 == ' ' || *s1 == '\t'))
		return ((unsigned char)*s1 - (unsigned char)*s2 + 32);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}*/

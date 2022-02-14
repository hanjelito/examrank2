#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

int ft_putstr(char *str, int n)
{
	int i = 0;
	if (!str)
		n = write(1, "(null)", 6);
	else
	{
		while (str[i])
		{
			n += write(1, &str[i], 1);
			i++;
		}
	}
	return (n);
}

int ft_putint(int num, int n)
{
	char *dec = "0123456789";

	if (num == -2147483648)
	{
		n = write(1, "-2147483648", 11);
		return (n);
	}
	if (num < 0)
	{
		n += write(1, "-", 1);
		num *= -1;
	}
	if (num > 9)
		n = ft_putint(num/10, n);
	n++;
	write(1, &dec[num%10], 1);
	return (n);
}

int ft_puthex(unsigned int num, int n)
{
    char *hex = "0123456789abcdef";
    if (num > 15)
        n = ft_puthex(num/16, n);
    n++;
    write(1, &hex[num%16], 1);
    return (n);
}

int ft_cases(char s, va_list ptr)
{
	int n = 0;

	if (s == 's')
		n = ft_putstr(va_arg(ptr, char *), n);
	if (s == 'd')
		n = ft_putint(va_arg(ptr, int), n);
	if (s == 'x')
		n = ft_puthex(va_arg(ptr, unsigned int), n);
	return (n);
}

int ft_printf(const char *format, ...)
{
	va_list ptr;
	int i = 0;
	int j = 0;

	va_start(ptr, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			j += ft_cases(format[i], ptr);
		}
		else
			j += write(1, &format[i], 1);
		i++;
	}
	va_end(ptr);
	return (j);
}

int main ()
{
    printf("----> Mio\n");
    printf("\n%d\n", ft_printf("holala %d %s %x", -12, "42\0", 2147483647));
    printf("\n----> Original\n");
    printf("\n%d\n", printf("holala %d %s %x", -12, "42\0", 2147483647));
    return(0);
}
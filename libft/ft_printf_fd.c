/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:34:45 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/08 17:15:14 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	print_unsigned(unsigned int nb, int fd)
{
	size_t	len;

	len = 0;
	if (nb > 9)
	{
		len += print_unsigned((nb / 10), fd);
		len += print_unsigned((nb % 10), fd);
	}
	else
	{
		ft_putchar_fd(nb + 48, fd);
		len++;
	}
	return (len);
}

static size_t	print_hex(unsigned long long n, char *base, int fd)
{
	size_t	len;

	len = 0;
	if (n > 15)
	{
		len += print_hex(n / 16, base, fd);
		len += print_hex(n % 16, base, fd);
	}
	else
	{
		ft_putchar_fd(base[n], fd);
		len++;
	}
	return (len);
}

static size_t	print_pointer(unsigned long long p, int fd)
{
	size_t	len;

	len = 0;
	if (!p)
		return (write(fd, "(nil)", 5), 5);
	write(fd, "0x", 2);
	len += print_hex(p, "0123456789abcdef", fd);
	return (len + 2);
}

static size_t	print_arg(va_list args, char c, int fd)
{
	if (!c)
		return (0);
	if (c == '%')
		return (ft_putchar_fd('%', fd), 1);
	else if (c == 'c')
		return (ft_putchar_fd(va_arg(args, int), fd), 1);
	else if (c == 's')
		return (ft_putstr_fd(va_arg(args, char *), fd));
	else if (c == 'i')
		return (ft_putnbr_fd(va_arg(args, int), fd));
	else if (c == 'd')
		return (ft_putnbr_fd(va_arg(args, int), fd));
	else if (c == 'u')
		return (print_unsigned(va_arg(args, unsigned int), fd));
	else if (c == 'p')
		return (print_pointer(va_arg(args, unsigned long long), fd));
	else if (c == 'x')
		return (print_hex(va_arg(args, unsigned int), "0123456789abcdef", fd));
	else if (c == 'X')
		return (print_hex(va_arg(args, unsigned int), "0123456789ABCDEF", fd));
	return (0);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	size_t	len;

	len = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			len += print_arg(args, *(format + 1), fd);
			format++;
		}
		else
		{
			ft_putchar_fd(*format, fd);
			len++;
		}
		format++;
	}
	va_end(args);
	return (len);
}

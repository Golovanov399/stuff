#!/usr/bin/python2

def gcd(x, y):
	while y != 0:
		x, y = y, x % y
	return x

class Ratio(object):
	def __init__(self, a=0, b=1):
		g = gcd(a, b)
		self.a = a // g
		self.b = b // g
		if self.b < 0:
			self.a *= -1
			self.b *= -1

	def __add__(self, other_):
		if not isinstance(other_, Ratio):
			other = Ratio(other_)
		else:
			other = other_
		return Ratio(self.a * other.b + self.b * other.a, self.b * other.b)

	def __sub__(self, other_):
		if not isinstance(other_, Ratio):
			other = Ratio(other_)
		else:
			other = other_
		return Ratio(self.a * other.b - self.b * other.a, self.b * other.b)

	def __mul__(self, other_):
		if not isinstance(other_, Ratio):
			other = Ratio(other_)
		else:
			other = other_
		return Ratio(self.a * other.a, self.b * other.b)

	def __div__(self, other_):
		if not isinstance(other_, Ratio):
			other = Ratio(other_)
		else:
			other = other_
		return Ratio(self.a * other.b, self.b * other.a)

	def __eq__(self, other_):
		if not isinstance(other_, Ratio):
			other = Ratio(other_)
		else:
			other = other_
		return self.a * other.b == self.b * other.a

	def __ne__(self, other_):
		if not isinstance(other_, Ratio):
			other = Ratio(other_)
		else:
			other = other_
		return self.a * other.b != self.b * other.a

	def __gt__(self, other_):
		if not isinstance(other_, Ratio):
			other = Ratio(other_)
		else:
			other = other_
		return self.a * other.b > self.b * other.a

	def __neg__(self):
		return Ratio(-self.a, self.b)

	def __str__(self):
		if self.b == 0:
			return "nan"
		elif self.b == 1:
			return str(self.a)
		else:
			return str(self.a) + '/' + str(self.b)

	def __repr__(self):
		if self.b == 0:
			return "nan"
		elif self.b == 1:
			return str(self.a)
		else:
			return str(self.a) + '/' + str(self.b)

def str_to_ratio(s):
	if s.find('/') > -1:
		pos = s.find('/')
		return Ratio(int(s[:pos]), int(s[pos+1:]))
	else:
		return Ratio(int(s))

def lin_eq_solve(a, b):
	"""
	Be careful: a and b may change
	I don't know, actually
	"""
	n = len(a)
	m = len(a[0])
	column = 0
	for i in xrange(n):
		if column >= m:
			break
		j = i
		while j < n and a[j][column] == 0:
			j += 1
		if j == n:
			column += 1
			continue
		if j > i:
			a[i], a[j] = a[j], a[i]
			b[i], b[j] = b[j], b[i]
		for j in xrange(i + 1, n):
			k = a[j][column] / a[i][column]
			for ij in xrange(column, m):
				a[j][ij] = a[j][ij] - a[i][ij] * k
			b[j] = b[j] - b[i] * k
		column += 1
	values = [0 for j in xrange(m)]
	for i in xrange(n - 1, -1, -1):
		col = 0
		while col < m and a[i][col] == 0:
			col += 1
		if col == m:
			continue
		val = b[i]
		for j in xrange(col + 1, m):
			val -= a[i][j] * values[j]
		values[col] = val / a[i][col]
	return values

# n, m = map(int, raw_input().split())
# a = [[0 for j in xrange(m)] for i in xrange(n)]
# b = [0 for i in xrange(n)]

# for i in xrange(n):
# 	data = list(map(int, raw_input().split()))
# 	a[i] = list(map(Ratio, data[:-1]))
# 	b[i] = Ratio(data[-1])

def taylor(arg, order):
	"""
	Represent f(x + arg) as Taylor series at x
	"""
	result = []
	current = Ratio(1)
	curfact = 1
	for i in xrange(order):
		result.append(current / curfact)
		current = current * arg
		curfact *= (i + 1)
	return result

def show_signed(x):
	if x == 0:
		return "0"
	elif x > 0:
		return "+" + str(x)
	else:
		return str(x)

def show_signed_with_h(x):
	if x == 0:
		return ""
	elif x == 1:
		return "+h"
	elif x == -1:
		return "-h"
	else:
		return show_signed(x) + "h"

def derivs(n):
	if n == 0:
		return ""
	elif n < 3:
		return "'" * n
	else:
		return "^{(%d)}" % (n)

def print_taylor_expansion(arg, order):
	result = "f(n" + show_signed_with_h(arg) + ") ="
	was_printed = False
	tlr = taylor(arg, order)
	for i in xrange(order):
		if tlr[i] == 0:
			continue

		qw = ""
		if i == 1:
			qw = "h"
		elif i > 1:
			qw = "h^" + str(i)
		if was_printed:
			if tlr[i] == 1:
				result += " + %sf%s(n)" % (qw, derivs(i))
			elif tlr[i] == -1:
				result += " - %sf%s(n)" % (qw, derivs(i))
			elif tlr[i] > 0:
				result += " + %s%sf%s(n)" % (tlr[i], qw, derivs(i))
			else:
				result += " - %s%sf%s(n)" % (-tlr[i], qw, derivs(i))
		else:
			if tlr[i] == 1:
				result += " %sf%s(n)" % (qw, derivs(i))
			elif tlr[i] == -1:
				result += " -%sf%s(n)" % (qw, derivs(i))
			elif tlr[i] > 0:
				result += " %s%sf%s(n)" % (tlr[i], qw, derivs(i))
			else:
				result += " -%s%sf%s(n)" % (-tlr[i], qw, derivs(i))			
		was_printed = True
	result += " + o\\left(h^{%d}\\right)" % (order-1)
	return result

variants = ["find_coeffs"]

while True:
	print "Tasks: " + " ".join(variants)
	var = raw_input("Select your task: ")
	if var in variants:
		break

if var == "find_coeffs":
	print "Print all arguments with only spaces between them. Replace h's by 1. For example:"
	print "n-1  n n+2"
	s = raw_input("Here you go: > ")
	a = s.split()
	n = len(a)
	A = []
	for i in xrange(n):
		if a[i] == 'n':
			a[i] = Ratio(0)
		else:
			a[i] = str_to_ratio(a[i].replace('n', ''))
		A.append(taylor(a[i], n))
	for i in xrange(n):
		for j in xrange(i):
			A[i][j], A[j][i] = A[j][i], A[i][j]
	b = [0] * n
	b[1] = 1
	b = list(map(Ratio, b))
	res = lin_eq_solve(A, b)
	equation = " + ".join("\\frac{%d}{%dh}f(n%s)" % (res[i].a, res[i].b, show_signed_with_h(a[i])) for i in xrange(n))
	for i in xrange(n):
		print print_taylor_expansion(a[i], n) + " \\\\"
	print equation + " = f'(n) + o\\left(h^%d\\right)" % (n-1)
	print "You can use the link below to paste this formula:"
	print "http://www.codecogs.com/latex/eqneditor.php"
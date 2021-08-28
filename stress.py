#!/usr/bin/env python3

import argparse
import subprocess as sp
import os
import sys

parser = argparse.ArgumentParser(description="Stress your solution against a naive one.")
parser.add_argument("-re", "--runtime", action="store_true", help="Test on runtime error")
parser.add_argument("main_file", metavar="<solution exec>", help="Executable file of the solution to test")
parser.add_argument("stupid_file", metavar="<naive soln exec>", help="Executable file of the solution to test against. If --runtime flag is not set, can be anything, say, -.", default="-")
parser.add_argument("gen_file", metavar="<generator exec>", help="Executable which prints a (random) test to stdout.")

args = parser.parse_args()


def test_format(s):
	return ("\n" if s.strip().count('\n') > 0 else " ") + s.strip()


def clear_last_row():
	print(f"\r{' ' * 100}\r", end="")


idx = 0
while True:
	idx += 1
	clear_last_row()
	print(f"Test #{idx}: generating...", end="")
	sys.stdout.flush()
	inp = sp.run(os.path.join(".", args.gen_file), capture_output=True).stdout
	clear_last_row()
	print(f"Test #{idx}: running our solution...", end="")
	sys.stdout.flush()
	our = sp.run(os.path.join(".", args.main_file), input=inp, capture_output=True)
	if our.returncode != 0:
		print(f"\nRuntime error on test #{idx}:")
		print(inp.decode().strip())
		print(f"Error message:\n{our.stderr.decode()}")
		break
	our = our.stdout.decode()
	if not args.runtime:
		clear_last_row()
		print(f"Test #{idx}: running naive solution...", end="")
		sys.stdout.flush()
		correct = sp.run(os.path.join(".", args.stupid_file), input=inp, capture_output=True).stdout.decode()
		if our.strip() != correct.strip():
			print(f"\nFailed test #{idx}:")
			print(inp.decode().strip())
			print(f"    our output: {test_format(our)}")
			print(f"correct output: {test_format(correct)}")
			break

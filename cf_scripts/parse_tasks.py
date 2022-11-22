#!/usr/bin/python3

import re
import requests
import sys
import os
import stat
from bs4 import BeautifulSoup
from shutil import copyfile

if len(sys.argv) < 2:
	print("Need contest number")
	sys.exit(0)

number = sys.argv[1]


def sample_text(sample):
	divs = sample.findAll("div", {"class": "test-example-line"})
	if divs:
		return "\n".join([test.text.strip() for test in divs if test.text.strip()])
	else:
		return sample.text.strip()


r = requests.get("http://codeforces.com/contest/" + number + "/problems", allow_redirects=True)
s = r.text
soup = BeautifulSoup(s, "html.parser")

if soup.text == "Redirecting... Please, wait.":
	print("Bypassing anti-scrap protection...")
	scr = soup.findAll("script")[-1].string
	scr = scr[scr.index("var a=toNumbers"):].split(';')
	line = scr[0]
	abc = []
	while "toNumbers" in line:
		i = line.index("toNumbers")
		line = line[i+11:]
		abc.append(line[:line.index('"')])
	from Crypto.Cipher import AES
	def to_numbers(x):
		return bytes(int(x[i:i+2], 16) for i in range(0, len(x), 2))
	key, iv, cipher = map(to_numbers, abc)
	aes = AES.new(key, AES.MODE_CBC, iv)
	rcpc = aes.decrypt(cipher).hex()
	print(f"RCPC = {rcpc}")
	url = scr[-2]
	url = url[url.index('"')+1:-1]
	r = requests.get(url, cookies={"RCPC": rcpc})
	s = r.text
	soup = BeautifulSoup(s, "html.parser")

probs = soup.findAll("div", {"class": "problemindexholder"})
for prob in probs:
	index = prob["problemindex"]
	if not os.path.exists(index):
		os.makedirs(index)
	samples = prob.find("div", {"class": "sample-test"})
	io = zip(samples.findAll("div", {"class": "input"}),
			 samples.findAll("div", {"class": "output"}))
	io = list(io)
	for i in range(len(io)):
		inp, out = io[i]
		with open("%s/in%d.in" % (index, i), "w") as f:
			print(sample_text(inp.find("pre")), file=f)
		with open("%s/out%d.out" % (index, i), "w") as f:
			print(sample_text(out.find("pre")), file=f)
	for file in ["qwe.cpp", "check.sh"]:
		newfile = index + "/" + file
		copyfile(file, newfile)
		os.chmod(newfile, os.stat(newfile).st_mode | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)

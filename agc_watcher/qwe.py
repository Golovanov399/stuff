#!/usr/bin/python2

import requests
import BeautifulSoup
import json

import argparse
import subprocess
import sys

import time

def extract_list(s):
	i = s.find('[')
	if i == -1:
		return ""
	t = s[i]
	bal = 1
	i += 1
	while i < len(s) and bal > 0:
		t += s[i]
		if s[i] == '[':
			bal += 1
		elif s[i] == ']':
			bal -= 1
		i += 1
	return t


def get_table(contest):
	try:
		r = requests.get("http://%s.contest.atcoder.jp/standings" % contest)
		soup = BeautifulSoup.BeautifulSoup(r.content)
		for x in soup.findAll('script'):
			if x.text.find('ATCODER') > -1:
				return json.loads(extract_list(str(x.text)))
	except Exception as e:
		print e


def handle_event(name, task_id, min_id, rank):
	# print "%s solved task with id = %d (probably task %c) and now on the place #%d" % (name, task_id, chr(ord('A') + task_id - min_id), rank)
	subprocess.Popen(['notify-send', "%s solved task with id = %d (probably task %c) and is now on the place #%d" % (name, task_id, chr(ord('A') + task_id - min_id), rank)])


if __name__ == "__main__":
	parser = argparse.ArgumentParser(description='Notifies about new solutions to the problems.')
	parser.add_argument('contest', type=str, help='contest id, eg agc019')
	parser.add_argument('--max-count', dest='count', type=int, default=5, help='number of first people to solve the problems in order to be notified about (default 5)')

	args = parser.parse_args()
	solved = dict()
	max_people_solved = args.count
	contest = args.contest

	while True:
		table = get_table(contest)
		if table is None:
			secs = 5
			print "Unable to obtain the table, trying to reconnect in %s seconds..." % secs
			time.sleep(secs)
			continue
		for row in table:
			name = row['user_screen_name']
			for task in row['tasks']:
				task_id = task['task_id']
				if 'score' in task and task['score'] > 0:
					if task_id not in solved:
						solved[task_id] = set()
					if len(solved[task_id]) < max_people_solved and name not in solved[task_id]:
						solved[task_id].add(name)
						handle_event(name, task_id, min(solved), row['rank'])

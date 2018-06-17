#!/usr/bin/python3

import vk

# https://oauth.vk.com/authorize?client_id=<client_id>&redirect_uri=oauth.vk.com/blank.html&response_type=token&scope=4103

session = vk.Session(access_token="poshel_nahui")
api = vk.API(session)

import urllib
import os

def get_max_photo_url(photo):
	return max(photo["sizes"], key=lambda x: x["width"])["url"]

def download_file(url, path=""):
	pic_name = url.split('/')[-1]
	if pic_name in os.listdir(path):
		return
	try:
		urllib.request.urlretrieve(url, os.path.join(path, pic_name))
	except Exception as e:
		print("Unable to download file by url {}: error is\n  {}".format(url, e))

def mkdir(dirname):
	try:
		os.mkdir(dirname)
	except FileExistsError as e:
		pass
	except Exception as e:
		print(e)

owner_id = -141886212 # `-` stands for a community, not user
album_id = 241817266

group_info = api.groups.getById(group_id=abs(owner_id), v="5.78")[0]
name = group_info["screen_name"] or group_info["name"]
mkdir(name)

# TODO: replace by `execute` api method?

offset = 0
urls = []
while True:
	while True:
		try:
			photos = api.photos.get(owner_id=owner_id, album_id=album_id, offset=offset, count=1000, v="5.78")["items"]
			break
		except vk.exceptions.VkAPIError as e:
			if not e.startswith("6."): # if "Too many requests per second" in e:
				print(e)
				import sys
				sys.exit(0)
	if len(photos) == 0:
		break
	offset += len(photos)
	urls.extend(map(get_max_photo_url, photos))

for i in range(len(urls)):
	print("Downloading " + str(i+1).rjust(len(str(len(urls))))+"/"+str(len(urls)), end="\r")
	download_file(urls[i], name)
print()

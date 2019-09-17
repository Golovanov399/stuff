#!/bin/bash
if [ -z "$1" ]
then
	name="$(date +%Y-%m-%d)"
else
	name="$(date +%Y-%m-%d)_$1"
fi
rm -rf $name
mkdir $name
cd $name
cp ../template.cpp qwe.cpp
cp ../parse_tasks.py .
cp ../check.sh .

echo $name

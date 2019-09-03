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
cp ../compile.sh .
cp ../run.sh .
# cp ../make_new_folders.sh .
cp ../parse_tasks.py .
cp ../check.sh .

# for i in {A..E}
# do
# 	mkdir $i;
# 	cp qwe.cpp $i;
# 	cp compile.sh $i;
# 	cp run.sh $i;
# 	cp check.sh $i;
# done;

# rm qwe.cpp compile.sh run.sh

echo $name

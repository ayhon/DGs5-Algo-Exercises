#!/usr/bin/env sh
fifo="/tmp/run_tests_fifo`date +%s`"
cmd="$1"
testfile="$2"
mkfifo "$fifo"
cat "$testfile" > "$fifo" &

testcase(){
	echo -e "Test case \e[3"$((("$1" % 2) + 1))"m$1\e[m"
	"$cmd" < "$fifo"
}

count=0
while true; do
	count=$(($count + 1))
	testcase $count || echo "Done" && exit 0
	echo ''
done
cat "$fifo"
rm "$fifo"

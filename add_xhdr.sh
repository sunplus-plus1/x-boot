#!/bin/bash

# $1: val
# $2: 1=no reverse
# $3: 1=have secure boot signature

function gen_bin_tmp
{
	#echo $1
	if [ "$2" = "1" ];then
		printf "0: %.8x" $1 | xxd -r -g0 >tmp
	else
		printf "0: %.8x" $1 | sed -E 's/0: (..)(..)(..)(..)/0: \4\3\2\1/' | xxd -r -g0 >tmp
	fi
	#hexdump -C tmp
}

if [ $# != 3 ];then
	echo "Error: $0 missed arguments"
	exit 1
fi

input=$1
output=$2
img_flag=$3

sz=`stat -c%s $1`
finalsz=$((64 + sz))

#chksum=`md5sum $input |cut -c 1-8`
chksum=`./tools/tcpsum $input |cut -c 1-4`
chksum="0000$chksum"
echo "chksum=$chksum"

# header size is 32 (0x20)
dd if=/dev/zero of=$output bs=1 count=32 2>/dev/null


##############
# 4-byte magic
val=$((0x54554258)) # XBUT (X=58h)
gen_bin_tmp $val
dd if=tmp of=$output conv=notrunc bs=1 count=4 seek=0 2>/dev/null

##############
# 4-byte version=0

##############
# 4-byte length of bin (exhclude header)
val=$sz
gen_bin_tmp $val
dd if=tmp of=$output conv=notrunc bs=1 count=4 seek=8 2>/dev/null

##############
# 4-byte checksum
val=$((0x$chksum))
gen_bin_tmp $val 0
dd if=tmp of=$output conv=notrunc bs=1 count=4 seek=12 2>/dev/null

##############
# 4-byte img_flag
val=$img_flag
gen_bin_tmp $val 0
dd if=tmp of=$output conv=notrunc bs=1 count=4 seek=16 2>/dev/null

##############
# 12-byte reserved

##############
# bin content
dd if=$input of=$2 conv=notrunc bs=1 seek=32 2>/dev/null

rm tmp

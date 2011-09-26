if [[ -z "$1" ]]
then 
	echo "Usage: 1.sh filenameFirst filenameSecond"
else
	declare -A array
	while read b c; do
		while read a && [[ -n $a ]]; do
			array[$a]="$b $c";
		done 
	done <$1
fi


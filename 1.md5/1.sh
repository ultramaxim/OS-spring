declare -a array
while read b c; do
	while read a && [[ -n $a ]]; do
		array[$a]="$b $c";
	done 
done <$1

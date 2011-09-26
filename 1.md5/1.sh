while read a b; do
	while read c && [[ -n $c ]]; do
		echo "$c  $a $b";
	done 
done <$1

while read a b; do
	while read c; do
		echo "$c  $a $b";
	done 
done <$1

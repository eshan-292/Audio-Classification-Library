for file in ./mfcc_features/*
do 
	echo "$file"
	./yourcode.out $file test.txt	
done

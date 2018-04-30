echo "Removing binarys."
rm -f server client

echo "Compiling"
gcc -o server main1.c
gcc -o client main2.c

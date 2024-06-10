echo "START"
mkdir $1
cd ./$1 
touch $user.txt
head -n 2 man wc > $user.txt
tail -n 2 man wc > $user.txt
chmod -w $user.txt
echo "END"

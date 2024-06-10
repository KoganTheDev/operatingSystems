echo "START"
mkdir $1
cd ./$1 
touch $USER.txt
man wc | head -n 2 >> $USER.txt
man wc | tail -n 2  >> $USER.txt
chmod -w $USER.txt
echo "END"

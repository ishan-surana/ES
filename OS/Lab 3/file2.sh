# result=`file *`
# num=`file * | wc-l`
# for ((i=0;i<num;i++));do
# echo $result[$i]
# done

echo -n "Enter string:- "
read substr
result=`ls | grep $substr`
echo $result

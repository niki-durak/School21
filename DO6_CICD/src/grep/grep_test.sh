COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE1="../grep/test1.txt"
TEST_FILE2="../grep/test2.txt"
PATTERN_FILE="../grep/reg_exmpl.txt"
GREP_FILE="../grep/s21_grep"
arguments=(i v c l n o)



echo "TEST 1:"

for var in ${arguments[@]}
do
  for var2 in ${arguments[@]}
  do
        if [ $var != $var2 ]
        then
          TEST1="-$var$var2 grep $TEST_FILE1"
          $GREP_FILE $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
            echo "$TEST1 - SUCCESS"
              (( COUNTER_SUCCESS++ ))
            else
            echo "$TEST1 - FAIL"
              (( COUNTER_FAIL++ ))
          fi
        fi
  done
done

echo "TEST 2:"
for var in ${arguments[@]}
do
  for var2 in ${arguments[@]}
  do
        if [ $var != $var2 ]
        then
          TEST2="-$var$var2 grep $TEST_FILE1 $TEST_FILE2"
          $GREP_FILE $TEST2 > s21_grep.txt
          grep $TEST2 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
            echo "$TEST2 - SUCCESS"
              (( COUNTER_SUCCESS++ ))
            else
            echo "$TEST2 - FAIL"
              (( COUNTER_FAIL++ ))
          fi
        fi
  done
done

rm s21_grep.txt grep.txt
echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"


N_LIST="10 32 50 64 100 128 200 256 300 400 512 1000"
PROGRAM=./matrixInv
INPUT_FILE=input.in
LIKWID_OUTPUT=likwid_out.csv
AUX_FILE=auxx.tmp

for N in $N_LIST;
do
    python3 gera_entrada.py $N $N > $INPUT_FILE

    likwid-perfctr -C 3 -g L3 -o $LIKWID_OUTPUT -m $PROGRAM < $INPUT_FILE > /dev/null

    RESULT=$(cat $LIKWID_OUTPUT | grep "RDTSC Runtime" | cut -d',' -f2)
    for r in $RESULT;
    do
        echo "$N,$r" >> $AUX_FILE
    done
done
cat $AUX_FILE
rm $AUX_FILE
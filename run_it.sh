N_LIST="10 32 50 64 100 128 200 256 300 400 512 1000"
PROGRAM=./matrixInv
INPUT_FILE=input.in
LIKWID_OUTPUT=likwid_out.csv
AUX_FILE=auxx.tmp


echo "N:Memory bandwidth [MBytes/s]:Time elapsed [s]:Cache miss:DP MFLOP/s:AVX DP MFLOP/s" >> $AUX_FILE

for N in $N_LIST;
do
    python3 gera_entrada.py $N $N > $INPUT_FILE

    likwid-perfctr -C 3 -g L3 -o $LIKWID_OUTPUT -m $PROGRAM < $INPUT_FILE > /dev/null

    RESULT=$(cat $LIKWID_OUTPUT | grep "L3 bandwidth"  | cut -d',' -f2)
    for r in $RESULT;
    do
        echo -n "$N,$r" >> $AUX_FILE
    done

    RESULT=$(cat $LIKWID_OUTPUT | grep "RDTSC Runtime" | cut -d',' -f2)
    for r in $RESULT;
    do
        echo -n ",$r" >> $AUX_FILE
    done

    likwid-perfctr -C 3 -g L2CACHE -o $LIKWID_OUTPUT -m $PROGRAM < $INPUT_FILE > /dev/null

    RESULT=$(cat $LIKWID_OUTPUT | grep "L2 miss ratio" | cut -d',' -f2)
    for r in $RESULT;
    do
        echo -n ",$r" >> $AUX_FILE
    done

    likwid-perfctr -C 3 -g FLOPS_DP -o $LIKWID_OUTPUT -m $PROGRAM < $INPUT_FILE > /dev/null
    
    RESULT_FLT=$(cat $LIKWID_OUTPUT | grep -v "AVX" | grep "DP MFLOP/s" | cut -d',' -f2)
    for r in $RESULT;
    do
        echo -n ",$r" >> $AUX_FILE
    done

    RESULT_AVX=$(cat $LIKWID_OUTPUT | grep "AVX" | cut -d',' -f2)
    for r in $RESULT;
    do
        echo ",$r" >> $AUX_FILE
    done
done
cat $AUX_FILE
rm $AUX_FILE
#!/bin/zsh

# 5th order
# original and all zero, fix random seed to 666
# for obv in  "r42" "k41"; do
#     for err in "tot" "stat"; do
#         ./runOri $obv $err 5 Original 666
#         ./runZero $obv $err 5 All-Zero 666
#     done
# done

# # pseudo simulation, seed starts from 1000
# for rsd in {1..24}; do 
#     for obv in  "r42" "k41"; do
#         for err in "tot" "stat"; do
#             ./run $obv $err 5 Pseudo-$rsd $(($rsd + 1000))
#             # echo "./run $obv $err 5 Pseudo-$rsd $(($rsd + 1000))"
#         done
#     done
# done

# 3rd order
# original and all zero, fix random seed to 666
for obv in  "r42" "k41"; do
        ./runOri $obv tot 3 Original 666
        ./runZero $obv tot 3 All-Zero 666
done

# pseudo simulation, seed starts from 1000
for rsd in {1..24}; do 
    for obv in  "r42" "k41"; do
        ./run $obv tot 3 Pseudo-$rsd $(($rsd + 1000))
    done
done

# 5th order
# original and all zero, fix random seed to 666
for obv in  "r42" "k41"; do
        ./runOri $obv tot 5 Original 666
        ./runZero $obv tot 5 All-Zero 666
done

# pseudo simulation, seed starts from 1000
for rsd in {1..24}; do 
    for obv in  "r42" "k41"; do
        ./run $obv tot 5 Pseudo-$rsd $(($rsd + 1000))
    done
done
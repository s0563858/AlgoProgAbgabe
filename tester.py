import os

summ = 0.0
times = 50
# for g in [1,2,4,6,8,10,12,14,16,18,20,24,28,32]:
for i in range(0,times):
    stream = os.popen('./yourFileProgram -p images/animal/1.kitten_small.jpg -b 20 -pn -c')
    output = float(stream.read())
    summ = summ + output

avg=summ/times
summ=0
print(avg)


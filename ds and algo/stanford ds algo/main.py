from collections import defaultdict
import threading

def hash_fn(n):
    M=1999993
    return n%M

def two_sum_present(target):
    global ans
    bool=True
    for x in nums:
        y = target-x
        if y in my_hash_table[hash_fn(y)] and y!=x:
            bool=False
            ans+=1
            return 1
    if bool == True:
        return 0
f = open('algo1_programming_prob_2sum.txt')
nums=[]
my_hash_table = defaultdict(list)    
for line in f.readlines():
    num = int(line.split('\n')[0])
    nums.append(num)
    my_hash_table[hash_fn(num)].append(num)

ans=0
for nr in range(-10000, 10001):
    thr = threading.Thread(target = two_sum_present, args=(nr,))
    thr.start()

print(ans)

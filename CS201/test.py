from os import path
import random,sys
sys.stdout=open("input.txt","w")
print("Y")
for i in range(5000000):
    print(1)
    print(random.randint(0,10000))
for i in range(5000):
    print(2)
    print(random.randint(0,100000))
print(5)
print(-1)
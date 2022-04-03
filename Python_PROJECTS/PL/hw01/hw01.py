import time
from tracemalloc import start

def get_user_input() :
    global n
    n = int(input(">> input the number of numbers to process : "))
    if(n<=1 or n>=31) : return False

    nums_string = input(">> Input the numbers to be process : ").split()
    global nums
    nums = list(map(int,nums_string))

    if(len(nums)!=n) : return False

    for num in nums :
        if(num<=0 or num>=100001):
            return False

    return True

def sort_nums(arr):
    arr_len = len(arr)

    for i in range(arr_len):
        for j in range(0, arr_len - i - 1):
            if arr[j] > arr[j + 1]: 
                arr[j], arr[j + 1] = arr[j + 1], arr[j]

def set_isPrime() :
    global isPrime
    isPrime = [True for i in range(100002)]

    for i in range(2,50001) :
        if(isPrime[i]) :
            for j in range(i*2,100001,i) :
                isPrime[j] = False

def get_GCD() :
    global gcd
    nums_copy = nums.copy()
    gcd = 1
    div_check = True
    for i in range(2,n+1) :
        if(isPrime[i]) :
            div_check = True
            while div_check :
                for j in range(0,n) :
                    if(nums_copy[j] % i != 0) :
                        div_check = False
                        break
                    nums_copy[j] /= i
                if div_check : gcd *= i

#main
input_check = False
while(input_check == False) :
    input_check = get_user_input()
    if(input_check == False) :
        print(">> wrong input. Try again.")

startTime = time.time()

sort_nums(nums)
set_isPrime()
get_GCD()
print("GCD of input numbers is ",gcd)

for i in range(0,n-1) :
    if nums[i] == nums[i+1] : continue
    print("Number of prime numbers between",int(nums[i]),",",int(nums[i+1]),": ", end="")
    prime_cnt =0
    for j in range(int(nums[i]), int(nums[i+1])+1):
        if(isPrime[j]) : prime_cnt += 1
    print(prime_cnt)

endTime = time.time()
totalTime = endTime - startTime
print("Total execution time usin Python is",totalTime*1000,"(millisec)")



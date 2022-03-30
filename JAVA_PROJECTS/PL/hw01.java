package PL;

import java.util.Scanner;

public class hw01 {
    public static int n=-1;
    public static int[] nums, nums_copy;
    public static boolean isPrime[];
    public static int max_n=-1;
    public static int GCD=1;
    public static Scanner scanner;

    public static void main(String[] args) {
        boolean inputCheck = false;
        scanner = new Scanner(System.in);
        while(!inputCheck){
            inputCheck = getUserInput();
            if(!inputCheck){
                System.out.println(">> wrong input. Try again.");
            }
        }
        scanner.close();
        long startTimeNano = System.nanoTime();

        sortNum();
        isPrime = new boolean[100001];
        setIsPrime();
        boolean div_check;
        for(int i=2; i<=max_n ; i++){               // 2~max_n
            if(isPrime[i]){                         // i가 소수면
                div_check = true;
                while(div_check){                   
                    for(int j=0; j<n; j++){         // 입력받은 모든 정수들에 대해
                        if(nums_copy[j] % i != 0){       // 소수 i로 나누어 떨어지지 않으면
                            div_check = false;      // 다음 소수로
                            break;
                        }
                        nums_copy[j] /= i;               // 나누어 떨어지면 나눔
                    }
                    if(div_check) GCD *= i;         // 모든 정수를 나눌 수 있으면 최대공약수에 해당 소수 곱
                }
            }
        }
        System.out.println("GCD of input numbers is "+GCD);

        for(int i=0; i<n-1; i++){
            if(nums[i] == nums[i+1]) continue;                  // 중복되는 수는 건너뜀
            System.out.print("Number of prime numbers between "+nums[i]+", "+nums[i+1]+": ");
            int prime_cnt=0;
            for(int j=nums[i]; j<=nums[i+1]; j++){              // 두 정수 사이의 범위에서
                if(isPrime[j]) prime_cnt++;                     // 소수면 cnt+1
            }
            System.out.println(prime_cnt);
        }

        long endTimeNano = System.nanoTime();

        long totalTimeNano = endTimeNano - startTimeNano;
        System.out.println("Total execution time using JAVA is "+totalTimeNano/1000000.0+"(millisec)");
    }

    static void setIsPrime(){
        for(int i=1; i<=100000; i++){
            isPrime[i] = true;
        }
        for(int i=2; i<=50000; i++){
            if(isPrime[i]){
                for(int j=2*i; j<=100000; j+=i){
                    isPrime[j] = false;
                }
            }
        }
    }

    static void sortNum(){
        int temp;
        for(int i=n-1; i>0; i--){
            for(int j=0; j<i; j++){
                if(nums[j] > nums[j+1]){
                    temp = nums[j];
                    nums[j] = nums[j+1];
                    nums[j+1] = temp;
                }
            }
        }
    }

    static boolean getUserInput(){
        boolean check = true;
        nums = new int[30];
        nums_copy = new int[30];

        System.out.print(">> Input the number of numbers to process : ");
            n = Integer.parseInt(scanner.nextLine());
        if(n<=1 || n>=31){
            return false;
        }

        max_n = -1;
        
        System.out.print(">> Input the numbers to be process : ");
        String num_String = " ";
        num_String = scanner.nextLine();
        String[] temp = num_String.split(" ");
        if(temp.length != n) {
            return false;
        }
        for(int i=0; i<n; i++){
            nums[i] = Integer.parseInt(temp[i]);
            if(nums[i]<=0 || nums[i]>=100001) {
                return false;
            }
        }
        nums_copy = nums;
        
        return check;
    }
}

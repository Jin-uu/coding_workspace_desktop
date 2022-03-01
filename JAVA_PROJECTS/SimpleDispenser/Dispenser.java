package SimpleDispenser;

import java.util.Scanner;

public class Dispenser {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        // 최소단위 100, 최대단위 10000
        int price = 0;
        while (true) {
            System.out.print("총 금액 입력 : ");
            price = sc.nextInt();
            if (price > 1000000) {
                System.out.println("1,000,000원보다 적은 금액을 입력하세요");
            } else if (price < 100) {
                System.out.println("100원보다 큰 금액을 입력하세요");
            } else break;
        }

        System.out.println("잔돈 : " + price + "원");
        int[] arr = { 10000, 5000, 1000, 500, 100 };
        for (int i = 0; i < arr.length; i++) {
            // 금액을 대입해서 자동계산
            if (price / arr[i] > 0) {
                System.out.println(arr[i] + "원 : " + price / arr[i] + " 개 ");
                price %= arr[i];
            }
        }
    }
}


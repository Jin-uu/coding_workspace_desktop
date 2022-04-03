package SimpleDispenser;

import java.util.Scanner;

public class Dispenser {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        // �ּҴ��� 100, �ִ���� 10000
        int price = 0;
        while (true) {
            System.out.print("�� �ݾ� �Է� : ");
            price = sc.nextInt();
            if (price > 1000000) {
                System.out.println("1,000,000������ ���� �ݾ��� �Է��ϼ���");
            } else if (price < 100) {
                System.out.println("100������ ū �ݾ��� �Է��ϼ���");
            } else break;
        }

        System.out.println("�ܵ� : " + price + "��");
        int[] arr = { 10000, 5000, 1000, 500, 100 };
        for (int i = 0; i < arr.length; i++) {
            // �ݾ��� �����ؼ� �ڵ����
            if (price / arr[i] > 0) {
                System.out.println(arr[i] + "�� : " + price / arr[i] + " �� ");
                price %= arr[i];
            }
        }
    }
}


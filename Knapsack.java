import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

// Time Complexity: O(N * W). where ‘N’ is the number of elements and ‘W’ is capacity. 
// Auxiliary Space: O(N * W). The use of a 2-D array of size ‘N*W’.

public class Knapsack {
    public static int getMax(List<Integer> Weight,List<Integer> Value,int MaxCapacity,int N){
        int res = 0; // our result variable

        int[][] knap = new int[N + 1][MaxCapacity + 1]; // declearing a knapsack

        for(int i=0;i<=N;i++){
            for(int w=0;w<=MaxCapacity;w++){
                if(i == 0 || w == 0){
                    // initialization is done by 0
                    knap[i][w] = 0;
                }
                else if(Weight.get(i - 1)<=w){ 
                    // To know why this condition see the max function properly as we do not want the Weight.get(i - 1) & w difference negative
                    knap[i][w] = Math.max(knap[i - 1][w],Value.get(i - 1) + knap[i - 1][w - Weight.get(i - 1)]);
                }
                else{
                    // if nothing satisfies the condition then we fallback to what was in previous iteration for knap variable
                    knap[i][w] = knap[i - 1][w];
                }
            } 
        }

        res = knap[N][MaxCapacity]; // last value in knapsack is the max profit

        int i = N, j = MaxCapacity;
        int[] selected = new int[N];

        // finding the selected elements into our knapsack
        while(i > 0 && j > 0){
            // check whether the element is in previous row if not the mark it as selected
            if(knap[i][j] == knap[i - 1][j]){
                selected[i - 1] = 0;
                i--;
            }
            else{
                selected[i - 1] = 1;
                i--;
                j = j - Weight.get(i);
            }
        }
        
        // print that selected array
        for(i = 0; i < selected.length; i++){
            System.out.print(selected[i]+" ");
        }
        System.out.println();

        return res;
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        // This is for test case
        int T = sc.nextInt();
        
        while((--T)>=0){
            // getting the user input

            List<Integer> weight = new ArrayList<Integer>();
            List<Integer> value = new ArrayList<Integer>();

            int N = sc.nextInt();
            int W = sc.nextInt();

            for(int i=0; i<N; i++){
                weight.add(sc.nextInt());
            }

            for(int i=0; i<N; i++){
                value.add(sc.nextInt());
            }

            System.out.println(getMax(weight, value, W, N));

        }
        
        sc.close();
    }
}

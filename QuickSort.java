import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class QuickSort{
    public static int partition(List<Integer> arr,int low,int high){
        int pivot = arr.get(low);
        int j = high;
        int i = low + 1;

        do{
            // i finding elements greater than pivot
            while(arr.get(i) <= pivot){
                i++;
            }
            
            // i finding elements less than pivot
            while(arr.get(j) > pivot){
                j--;
            }

            // if i did not crossed j then swap arr[i] & arr[j]
            if(i < j){
                int temp = arr.get(i);
                arr.set(i,arr.get(j));
                arr.set(j,temp);
            }
        }while(i < j);

        // swap arr[j] & pivot
        int temp = arr.get(low);
        arr.set(low,arr.get(j));
        arr.set(j,temp);

        return j;
    }

    public static void quicksort(List<Integer> arr,int low,int high){
        if(low < high){
            int partitionIDX = partition(arr,low,high);
            quicksort(arr, low, partitionIDX - 1); // left array
            quicksort(arr, partitionIDX + 1, high); // right array 
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        int T = sc.nextInt();
        List<Integer> Elements = new ArrayList<Integer>();

        while((--T)>=0){
            int N = sc.nextInt();

            for(int i = 0; i < N; i++){
                Elements.add(sc.nextInt());
            }

            quicksort(Elements, 0, N - 1);

            for(int i: Elements){
                System.out.print(i+" ");
            }
            System.out.println();

            Elements.clear();
        }

        sc.close();
    }
}
/**
 * Created by Bianca on 5/5/2019.
 */
public class VariantaSeriala {
    public static void main (String [] args){

        int s = 0;
        int a = 0;
        long b = 35000000;
        int copie;
        long startTime = System.nanoTime();
        for(int i = a ; i<b; i++){
            if(isPrime1(i)){
                for(int j = 1; j<= lengthNum(i); j++)
                    for(int k = 0; k < 10; k++){
                        copie = replaceDigitFromPosition(i, j, k);
                        if(isPrime1(copie) == false){
                            s += 1;
                        }
                    }
                if(s == 9* lengthNum(i)){
                    System.out.println(i);
                }
                s = 0;
            }
        }
        long endTime = System.nanoTime();
        long timeElapsed = endTime - startTime;

        System.out.println("Execution time in nanoseconds  : " + timeElapsed);

        double elapsedTimeInSecond = (double) timeElapsed / 1_000_000_000;
        System.out.println("Execution time in seconds:" + String.format("%.4f", elapsedTimeInSecond));

    }

    private static boolean isPrime1(int num){
        if ( num > 2 && num%2 == 0 ) {
            return false;
        }
        int top = (int)Math.sqrt(num) + 1;
        for(int i = 3; i < top; i+=2){
            if(num % i == 0){

                return false;
            }
        }
        return true;
    }
    private static int lengthNum(int n){
        int len = 0;
        if ( n > 0 ){
            len = (int)(Math.log10(n)+1);
        }
        return len;
    }
    static int replaceDigitFromPosition(int x, int pos, int digit)
    {
        int copie = 0;

        if(pos == 1){
            copie += (int)(x / Math.pow(10, pos)) * 10 + digit;
        }else if(pos > 1 && pos < lengthNum(x)){
            copie += (int)(x / Math.pow(10.0, pos)) * Math.pow(10.0, pos) + digit * Math.pow(10.0, pos-1) + x % Math.pow(10.0, pos-1);
        }else
        {
            copie += digit * Math.pow(10.0, pos-1) + x % Math.pow(10.0, pos-1);
        }
        return copie;
    }
}

public class Xbonacci {
  public double[] tribonacci(double[] s, int n) {
      
      double[] tribonacci;
      
      tribonacci = new double[n];
      
      if( !(n==0) && n > 3){
        // Assign initial values
        for(int i=0;i<3;i++)
          tribonacci[i]=s[i];
          /* 
          Complete the sequence, untill the defined limit
          calculated by n - 3 to avoid inexistenting indexes
          */
          for(int i=0;i<(n-3);i++){
            tribonacci[i+3] =  tribonacci[i]
                              +tribonacci[i+1]
                              +tribonacci[i+2];
          }
       }else if(!(n==0)){
        
        for(int i=0;i<n;i++)
         tribonacci[i]=s[i];
       
       
       }
      
      return tribonacci;
      
  }
}
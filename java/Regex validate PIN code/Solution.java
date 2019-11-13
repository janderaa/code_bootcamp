
public class Solution{

  public static boolean validatePin(String pin) {
    
    if(pin.isEmpty())
     return false;
    
    if(pin.length()==4 || pin.length()==6){
    
     for(int i = 0;i<pin.length();i++){
       if( Character.getType( pin.charAt(i) )!= 9 )
         return false;
     }
     
      return true;  
    }
    
    return false;
  }

}

/*
import java.util.regex.*;

public class Solution {

  public static boolean validatePin(String pin) {
    return pin.matches("\\d{4}|\\d{6}");
  }

}

https://docs.oracle.com/javase/8/docs/api/java/util/regex/Pattern.html
*/
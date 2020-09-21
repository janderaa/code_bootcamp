public class DescendingOrder {
  public static int sortDesc(final int num) {
    
    if(num >= 0){
    
      String num_string = Integer.toString(num);
      
      char[] num_charArray=num_string.toCharArray();
      
      char aux = 'a';
      
      for(int i=0;i<num_charArray.length;i++){  
        for(int j = (i+1 < num_charArray.length) ?  i+1: num_charArray.length ;j<num_charArray.length ;j++){
          if(Character.getNumericValue(num_charArray[j])>Character.getNumericValue(num_charArray[i])){
            aux = num_charArray[i];
            num_charArray[i] = num_charArray[j];
            num_charArray[j] = aux;
          }
        }
      } 
      
      String ordedered_num_string = new String(num_charArray);
      
      return Integer.parseInt(ordedered_num_string);
    }
    
    return num;
  }
}
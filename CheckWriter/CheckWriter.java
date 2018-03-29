//CheckWriter:
//writes an input number as a string as would be seen on a check


import java.io.*;
import java.util.*;
import java.lang.Math;

public class CheckWriter{
	public static void main(String[] args) throws IOException{
		//check number of command line arguments
		if(args.length != 2){
			System.out.println("Usage: CheckWriter in out");
			System.exit(1);
		}
		//initialize suffixes
		String[] suffixes = new String[]{"","thousand ","million ","billion "};
		String[] tens = new String[]{"zero ","ten ","twenty ","thirty ","forty ","fifty ","sixty ","seventy " ,"eighty ","ninety "};
		String[] tweens = new String[]{"ten ","eleven ","twelve ","thirteen ","fourteen ","fifteen ","sixteen ","seventeen ","eighteen ","nineteen "};
		String[] ones = new String[]{"zero ","one ","two ","three ","four ","five ","six ","seven ","eight ","nine "};
		//open files and read number into an array
		Scanner in = new Scanner(new File(args[0]));
		PrintWriter out = new PrintWriter(new FileWriter(args[1]));
		//split number into pre and post decimal numbers
		String number = in.nextLine();
		
		
		
		char[] cDigit = number.toCharArray();
		int[] digit = new int[cDigit.length];
		
		for(int i = 0; i < cDigit.length; i++){
			digit[i] = Character.digit(cDigit[i], 10);
			}
		int j;
		for ( j =0; j < cDigit.length;j++){
			if(digit[j] == -1){
				break;
			}
		}
		int[] numArray = new int[j];
		for (int k =0; k < j; k++){
			numArray[k] = digit[k];
			}
		j++;
		int[] decArray = new int[cDigit.length - j];
		for(int l=0; j<cDigit.length; l++){
			decArray[l] = digit[j];
			
			j++;
		}
		

	
		int integerLength = numArray.length;
		int decimalLength = decArray.length;
		
	

		String strOut = new String("");
		
		
			int counter = 0;
			int denomination;
			if(integerLength%3==0){
				denomination = integerLength/3;
			}
			else{
				denomination = integerLength/3;
				denomination+=1;
			}
			while(counter < integerLength){
				if((numArray.length - counter)%3 ==0){
					strOut += ones[numArray[counter]] + "hundred ";
					}
				else if((numArray.length - counter)%3 == 2){
					if(numArray[counter] == 1){
						strOut += tweens[numArray[++counter]] + suffixes[denomination-1];
						denomination -=1;
					}
					else{
						strOut += tens[numArray[counter]];
					}
				}
				else if((numArray.length - counter)%3 == 1){
					strOut += ones[numArray[counter]] +suffixes[denomination-1];
					denomination-=1;
				}
				counter++;
			}
		
			strOut += "dollars and ";
			
			if(decimalLength ==2 && decArray[0] == 1){
				strOut += tweens[decArray[1]];
					
			}
			else if(decArray[0]==1){
				strOut += "ten";
				
			}
			else{
				strOut += tens[decArray[0]];
				if(decimalLength==2){
					strOut += ones[decArray[1]];
				}
				
			}
			strOut += "cents";	
			
		
		
		out.println(strOut);
		in.close();       
		out.close();    
	}

}

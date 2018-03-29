//FindPrime:
//finds if the input number is prime, or the next lowest and next highest prime numbers otherwise

import java.io.*;
import java.util.*;
import java.lang.Math;



public class FindPrime{
	public static void main(String[] args) throws IOException{
		
		//check number of command line arguments
		if(args.length < 2){
			System.out.println("Usage: FileCopy <input file> <output file>");
			System.exit(1);
		}
		// open files       
		Scanner in = new Scanner(new File(args[0]));       
		PrintWriter out = new PrintWriter(new FileWriter(args[1])); 
		List<Integer> testList = new ArrayList<>();
		int testNum;
		int lower;
		int upper;
		while(in.hasNext()) {
			if(in.hasNextInt()){
				testList.add(in.nextInt());
			} else{
				in.next();
			}
		}
		for(int i = 0; i<testList.size(); i++){
			testNum = testList.get(i);
			if(isPrime(testNum) == true){
			out.println(testNum + " is prime.");

			}
			else{
				
				for(lower = testNum-1; lower>1; lower--){
					if(isPrime(lower) == true){
						break;
					}
				}
			
				for(upper = testNum+1; upper<testNum*2; upper++){
					if(isPrime(upper) == true){
						break;
					}
				}
				out.println(lower + " < " + testNum + " < " + upper);
			}
		}
		in.close();       
		out.close();  
	}


//isPrime. Tests if the input number is prime and returns a boolean value
//we only need to test for numbers lower thann the square root because
//the complimentary factor would have to be greater than the square root.
public static boolean isPrime(double argument){
		double boundary = Math.sqrt((double) argument+1);
		for (int i=2; i<=boundary; i++){
			if(argument%i == 0){
				return false;
			}
		}
		return true; //the number has been determined prime
}
}
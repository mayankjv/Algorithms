import java.util.*;
import java.io.*;
import java.nio.file.attribute.BasicFileAttributes;
import java.nio.file.FileSystems;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardWatchEventKinds;
import java.nio.file.WatchEvent;
import java.nio.file.WatchKey;
import java.nio.file.WatchService;




class WatchThread extends Thread{


	//Declaring an object of WatchService
	WatchService watchService;
	String path = "";

	public void set_path(String path_string){
		path= path_string;
	}

	//Run method of the thread that will be executed in parallel
	public void run(){
		//System.out.println("Thread Running");
		//WatchService.take() method might throw InterruptedExecution exception and IOException is likely to be thrown inside this try
		try{
				watchService = FileSystems.getDefault().newWatchService();
				//System.out.println("Path: "+path);
        		File directory = new File(path);
//        		File[] fList = directory.listFiles();
//        		int count=0;
    			Path _directory = Paths.get(path);
    			//Registering the parent directory with watchservice to monitor it.
    			WatchKey key = _directory.register(watchService,
                        		  	StandardWatchEventKinds.ENTRY_CREATE,
                        		   	StandardWatchEventKinds.ENTRY_DELETE,
                        		   	StandardWatchEventKinds.ENTRY_MODIFY);
//    			count++;


        		File[] fList = directory.listFiles();
        		//A loop that registers all the subdirectories of the folder with the watchservice so that they can be monitored for changes
        		for (int i=0;i<fList.length;i++){
        			File file = fList[i];
//        			System.out.println("\nCurrent : "+file.getName());
            		if (file.isDirectory()){
						try {
							String new_path= path+"\\"+file.getName();
    						Path _directotyToWatch = Paths.get(new_path);
 //   						System.out.println("Registering "+_directotyToWatch);
    						key = _directotyToWatch.register(watchService,
                        		  				 StandardWatchEventKinds.ENTRY_CREATE,
                        		   				StandardWatchEventKinds.ENTRY_DELETE,
                        		   				StandardWatchEventKinds.ENTRY_MODIFY);
  						} 
  						catch (IOException e) {
    						System.err.println(e);
  						}
//              		System.out.println("\nAdded!");
            		}
        		}







//        		System.out.println("Current Path: "+path+"\tnumber of files in present folder: "+fList.length);
        		//System.out.println(count+" folders registered.");
        		//Infinite loop to keep the Watch Thread always powered up and running.
        		Boolean valid = true;
        		do {
//        			System.out.println("Infinite Loop!");
					WatchKey watchKey = watchService.take();

					for (WatchEvent event : watchKey.pollEvents()) {
						WatchEvent.Kind kind = event.kind();
						if (StandardWatchEventKinds.ENTRY_CREATE.equals(event.kind())) {
							String fileName = event.context().toString();
							//new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
							System.out.println("File Created:" + fileName);
						}
						else if (StandardWatchEventKinds.ENTRY_DELETE.equals(event.kind())) {
							String fileName = event.context().toString();
							//new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
							System.out.println("File Deleted:" + fileName);
						}

					}	
					valid= watchKey.reset();	
            	} while(valid);
        	}
		catch(Exception e){
			System.out.println(e);
		}
	} 	
}







//This class stores the path string and all the files in a given path. A separate class is created for this because the user might need to switch between paths.
class Path_{

	String path_string;
	ArrayList<DirectoryFile> files= new ArrayList<DirectoryFile>();

	Path_(String path_to_folder){
		path_string= new String(path_to_folder);
		//store_file_list(path_string,0);
	}

	//This method traverses through the folders and the subfolders and stores all the files that are present in an ArrayList
	private void store_file_list(String path){

        File directory = new File(path);
        File[] fList = directory.listFiles();
//        System.out.println("Current Path: "+path+"\tnumber of files in present folder: "+fList.length);
        for (int i=0;i<fList.length;i++){
        	File file = fList[i];
//        	System.out.println("\nCurrent : "+file.getName());
            if (file.isFile()){
                files.add(new DirectoryFile(file));
//              System.out.println("\nAdded!");
            }
            else{
            	String new_path=path+"\\"+file.getName();
            	store_file_list(new_path);
            }
        }
	}

	//public method that will help the user to get the list of the files present in a given path_string.
	public ArrayList<DirectoryFile> get_files(){
		files= new ArrayList<DirectoryFile>();
		store_file_list(path_string);
		return this.files;
	}
}




















//This class stores all the attributes of a single file along with all the member functions that are needed to calculate the values of the attributes.
class DirectoryFile{

	private File file;
	private String type;
	private String name;
	private int lines;
	private long words;
	private long size;
	private long last_modified; 

	//Constructor that sets all the attributes of a file by calling suitable functions.
	DirectoryFile(File f){
		file = f;
		//Since BufferedReader is used, it might throw IOException
		try{
			type = set_type(file);
			name = set_name(file);
			set_lines();
			set_words();
			set_size();
			set_last_modified();
		}
		catch(IOException e){
			System.out.println("IO Exception !");
		}

	}
	//Getter mehtid for Name of the file
	public String get_file_name(){
		return name;
	}
	//Getter method for file type
	public String get_type(){
		return type;
	}
	//Getter method for Number of lines in the file
	public int get_lines(){
		return lines;
	}
	//Getter method for number of words in the file
	public long get_words(){
		return words;
	}
	////Getter method for the size of the file
	public long get_size(){
		return size;
	}
	//Getter method for the last modified timestamp of the file
	public long get_last_modified(){
		return last_modified;
	}
	//Method to set last modified timestamp
	private void set_last_modified(){

		last_modified=file.lastModified();
	
	}
	//Method to set the size of the file
	private void set_size(){
	
		size= file.length();
	
	}
	//Method to set the number of words int the file
	private void set_words() throws IOException{
	
		BufferedReader reader = new BufferedReader(new FileReader(file));
		String temp="";
		String[] words_;
		while(temp != null){
			try{
				temp= reader.readLine();
				words_= temp.split("\\s+");
				words+= words_.length;
			}
			catch(NullPointerException e){
//				System.out.println("File Empty!");
			}
	
		}
		reader.close();
	
	}
	//Method to set the number of lines in the file
	private void set_lines() throws IOException{
	
		BufferedReader reader = new BufferedReader(new FileReader(file));
		while (reader.readLine() != null) lines++;
		reader.close();
	}
	////Method to set the Name of the file
	private String set_name(File file){

        String fileName = file.getName();
        if(fileName.lastIndexOf(".") != -1 && fileName.lastIndexOf(".") != 0)
        	return fileName.substring(0,fileName.lastIndexOf("."));
        else return "";

	}
	////Method to set the file type
	private String set_type(File file){
	
        String fileName = file.getName();
        if(fileName.lastIndexOf(".") != -1 && fileName.lastIndexOf(".") != 0)
        	return fileName.substring(fileName.lastIndexOf(".")+1);
        else return "";
	
	}
	//Mehtod to print all the attributes of a file in a single row.
	public void print_file(){
		System.out.println("File Name: "+name+"\tExtension: "+type+"\tWords: "+words+"\tLines: "+lines+"\tLast Modified: "+last_modified+"\tSize: "+size);
	}


}














//Implementing Comparator interface and overriding the method compare to sort on the basis of File Name
class NameComparator implements Comparator<DirectoryFile>{

	public int compare(DirectoryFile file1, DirectoryFile file2){
		return file1.get_file_name().compareTo(file2.get_file_name());
	}
}














//Implementing Comparator interface and overriding the method compare to sort on the basis of File Size
class SizeComparator implements Comparator<DirectoryFile>{

	public int compare(DirectoryFile file1, DirectoryFile file2){
		return (int)(file1.get_size()-file2.get_size());
	}
}

















//Implementing Comparator interface and overriding the method compare to sort on the basis of Last modified timestamp
class LastModifiedComparator implements Comparator<DirectoryFile>{

	public int compare(DirectoryFile file1, DirectoryFile file2){
		return (int)(file2.get_last_modified()-file1.get_last_modified());
	}
}

















//The public class that contains the main method, the interaction with user will be done in this class.
public class FileStatistics{


/*	private void registerRecursive(final Path root) throws IOException {
    // register all subfolders
    	Files.walkFileTree(root, new SimpleFileVisitor<Path>() {
        	@Override
        	public FileVisitResult preVisitDirectory(Path dir, BasicFileAttributes attrs) throws IOException {
          		dir.register(watchService, ENTRY_CREATE, ENTRY_DELETE, ENTRY_MODIFY);
           	 	return FileVisitResult.CONTINUE;
        	}
    	});
	}

*/
	//Main method 
	public static void main(String args[]) throws IOException, InterruptedException{
		System.out.println("\nEnter the path: ");
		Scanner sc= new Scanner(System.in);
		String path_string=sc.nextLine();
		Path_ path = new Path_(path_string);

//		System.out.println("Path: "+path.path_string);
//		System.out.println("Number of files: "+path.get_files().size());
//		ArrayList<DirectoryFile> all_files= path.get_files();
//		for(DirectoryFile f: all_files){
//			f.print_file();
//		}
		WatchThread th= new WatchThread();
		th.set_path(path_string);
		th.start();
		int choice=0;
		int len= path.get_files().size();
/*    	Runnable r = new Runnable() {
        	public void run() {
        		while(true){
	        	//	System.out.println("Thread Running...");
					ArrayList<DirectoryFile> all_files= path.get_files();
					ArrayList<DirectoryFile> temp = new ArrayList<DirectoryFile>();
        			temp=all_files;
            		all_files= new ArrayList<DirectoryFile>(path.get_files());
            		//When a new file is added
            		//System.out.println("Size of all_files: "+all_files.size()+"   Size of temp: "+temp.size());
            		if(temp.size()<all_files.size()){
            			System.out.println("In first condition!");
            			for(int i=0; i<all_files.size();i++){
            				if(!temp.contains(all_files.get(i))){
            					System.out.println("Added: "+all_files.get(i));
            					break;
            				}
            			}
            		}
            		else if(temp.size()<all_files.size()){
            			for(int i=0;i<all_files.size();i++){
            				temp.remove(all_files.get(i));
            			}
            			System.out.println("Removed : "+temp.get(0));
            		}
            	}
        	}
    	};

		new Thread(r).start();
*/
		while(true){
			new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
			System.out.println("1. Display\n2. Sort\n3. Search\n4. Exit");
			System.out.println("Enter your choice:");
			//Scanner might throw InputMismatchException in case an invalid input is supplied
			try{
				Scanner sc1=new Scanner(System.in);
				choice= sc1.nextInt();
			}
			catch(InputMismatchException e){
				System.out.println("Enter a valid Integer!!");
				break;
			}
			//Condition when user wants to Display all the files at a given point of time
			if(choice == 1){
				new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
				System.out.println("PRESS ENTER TO GO TO THE MAIN MENU \n\n\n\n");
				ArrayList<DirectoryFile> temp= path.get_files();
				for(DirectoryFile f: temp)
				f.print_file();
				pressAnyKeyToContinue();
			}			
			//Condition when a user wants the files listed in a sorted manner.
			else if(choice == 2){
				new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
				System.out.println("1. By Name\n2. By Last Modified\n3. By Size");
				int ch = sc.nextInt();
				ArrayList<DirectoryFile> temp= path.get_files();
				switch(ch){
					//When sorting is to be done by Name
					case 1:
							Collections.sort(temp, new NameComparator());
							new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
							System.out.println("PRESS ENTER TO GO TO THE MAIN MENU \n\n\n\n");
							if(temp.size()==0)
								System.out.println("Nothing to Display!!");
							for(DirectoryFile f: temp)
								f.print_file();
							pressAnyKeyToContinue();


							break;
					//When sorting is to be done by Last Modified
					case 2:
							Collections.sort(temp, new LastModifiedComparator());
							//ArrayList<DirectoryFile> temp= path.get_files();
							new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
							System.out.println("PRESS ENTER TO GO TO THE MAIN MENU \n\n\n\n");
							if(temp.size()==0)
								System.out.println("Nothing to Display!!");
							for(DirectoryFile f: temp)
								f.print_file();
							pressAnyKeyToContinue();
							break;
					//When sorting is to be done by Size
					case 3:
							Collections.sort(temp, new SizeComparator());
							//ArrayList<DirectoryFile> temp= path.get_files();
							new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
							System.out.println("PRESS ENTER TO GO TO THE MAIN MENU \n\n\n\n");
							if(temp.size()==0)
								System.out.println("Nothing to Display!!");							
							for(DirectoryFile f: temp)
								f.print_file();
							pressAnyKeyToContinue();
							break;
					default:
							break;
				}
			}
			//When the user wants to search for a file
			else if(choice == 3){
				new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
				ArrayList<DirectoryFile> search_results = new ArrayList<DirectoryFile>();
				ArrayList<DirectoryFile> temp= path.get_files();
				System.out.println("1. By Name\n2. By Size");
				int ch = sc.nextInt();
				switch(ch){
					//When the search is to be done by name
					case 1:
							new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
							System.out.println("PRESS ENTER TO GO TO THE MAIN MENU \n\n\n\n");
							System.out.println("Enter Search string: ");
							String pattern= sc.next();
							KMPSearch obj= new KMPSearch();
							for(int i=0;i<temp.size();i++){
								int[] arr= obj.kmp(temp.get(i).get_file_name().toCharArray(), pattern.toCharArray());
								if(arr.length!=0){
									search_results.add(temp.get(i));
								}
							}
							new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
							System.out.println("PRESS ENTER TO GO TO THE MAIN MENU \n\n\n\n");
							if(search_results.size()==0)
								System.out.println("Nothing to Display!");
							for(DirectoryFile f: search_results)
								f.print_file();
							pressAnyKeyToContinue();
							break;
					//When the search is to be done by size.
					case 2:
							new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
							System.out.println("1. Greater than\n2. Smaller than");
							int ch1= sc.nextInt();
							new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
							System.out.println("Value: ");
							long val= sc.nextLong();
							switch(ch1){
								case 1:
									for(int i=0;i<temp.size();i++){
										if(temp.get(i).get_size()>val){
											search_results.add(temp.get(i));
										}
									}
									new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
									System.out.println("PRESS ENTER TO GO TO THE MAIN MENU \n\n\n\n");
									if(search_results.size()==0)
										System.out.println("Nothing to Display!");
									for(DirectoryFile f: search_results)
										f.print_file();
									pressAnyKeyToContinue();
									break;
								case 2:
									for(int i=0;i<temp.size();i++){
										if(temp.get(i).get_size()<val){
											search_results.add(temp.get(i));
										}
									}
									new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
									System.out.println("PRESS ENTER TO GO TO THE MAIN MENU \n\n\n\n");
									if(search_results.size()==0)
										System.out.println("Nothing to Display!");

									for(DirectoryFile f: search_results)
										f.print_file();
									pressAnyKeyToContinue();

									break;
								default:
									new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
									System.out.println("PRESS ENTER TO GO TO THE MAIN MENU \n\n\n\n");
									System.out.println("Invalid Option selected!");
									pressAnyKeyToContinue();
									break;

							}
							break;
					default:
							break;
				}
			}
			else if(choice == 4){
				//th.join();
				System.exit(0);
			}
			else{
				new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
				System.out.println("Invalid Choice");
			}
			//System.out.println(choice);
		}
	}
	private static void pressAnyKeyToContinue(){ 
        //System.out.println("Press Enter key to continue...");
        try
        {
            System.in.read();
        }  
        catch(Exception e)
        {}  
 	}
}




















class KMPSearch{
    public int[] kmp(char[] text, char[] pattern){
        int[] temp=calculateTemporaryArray(pattern);
        int i=0,j=0;
        ArrayList<Integer> res= new ArrayList<Integer>();
        while(i<text.length&&j<pattern.length){
            if(text[i]==pattern[j]){
                i++;
                j++;
                if(j==pattern.length){
                    res.add(i-pattern.length);
                    j=0;
                }
            }
            else{
                if(j!=0){
                    j=temp[j-1];
                }
                else
                    i++;
            }
        }
        int ret[]= new int[res.size()];
        i=0;
        for(Integer k:res)
            ret[i++]=k;
        return ret;
    }
    public int[] calculateTemporaryArray(char[] pattern){
        int size=pattern.length;
        int[] res= new int[size];
        res[0]=0;
        int index=0;
        for(int i=1;i<size;i++){
            if(pattern[i]==pattern[index]){
                res[i]=index+1;
                index++;
            }
            else{
                if(index!=0){
                    index=res[index-1];
                }
                else
                    res[i]=index+1;
            }
        }
        return res;
    }
}

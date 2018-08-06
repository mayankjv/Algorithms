import java.io.IOException;
import java.util.*;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

class Path{
	String path_string;
	ArrayList<DirectoryFile> files= new ArrayList<DirectoryFile>();

	Path(String path_to_folder){
		path_string= new String(path_to_folder);
		store_file_list(path_string);
	}
	private void store_file_list(String path){
        File directory = new File(path);
        File[] fList = directory.listFiles();
        for (int i=0;i<fList.length;i++){
        	File file = fList[i];
//        	System.out.println("\nCurrent : "+file.getName());
            if (file.isFile()){
                files.add(new DirectoryFile(file));
//                System.out.println("\nAdded!");
            }
            else{
            	String new_path=path+"\\"+file.getName();
            	store_file_list(new_path);
            }
        }
	}
	public ArrayList<DirectoryFile> get_files(){
		return this.files;
	}
}

class DirectoryFile{

	private File file;
	private String type;
	private String name;
	private int lines;
	private long words;
	private long size;
	private long last_modified; 
	DirectoryFile(File f){
		file = f;
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

	public String get_file_name(){
		return name;
	}

	public String get_type(){
		return type;
	}

	public int get_lines(){
		return lines;
	}

	public long get_words(){
		return words;
	}

	public long get_size(){
		return size;
	}

	public long get_last_modified(){
		return last_modified;
	}

	private void set_last_modified(){

		last_modified=file.lastModified();
	
	}
	private void set_size(){
	
		size= file.length();
	
	}

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
	
	}

	private void set_lines() throws IOException{
	
		BufferedReader reader = new BufferedReader(new FileReader(file));
		while (reader.readLine() != null) lines++;
		reader.close();
	
	}


	private String set_name(File file){

        String fileName = file.getName();
        if(fileName.lastIndexOf(".") != -1 && fileName.lastIndexOf(".") != 0)
        	return fileName.substring(0,fileName.lastIndexOf("."));
        else return "";

	}


	private String set_type(File file){
	
        String fileName = file.getName();
        if(fileName.lastIndexOf(".") != -1 && fileName.lastIndexOf(".") != 0)
        	return fileName.substring(fileName.lastIndexOf(".")+1);
        else return "";
	
	}

	public void print_file(){
		System.out.println("File Name: "+name+"\tExtension: "+type+"\tWords: "+words+"\tLines: "+lines+"\tLast Modified: "+last_modified);
	}


}




public class FileStatistics{

	public static void main(String args[]){
		System.out.println("\nEnter the path: ");
		Scanner sc= new Scanner(System.in);
		Path path = new Path(sc.nextLine());



//		System.out.println("Path: "+path.path_string);
//		System.out.println("Number of files: "+path.get_files().size());
//		ArrayList<DirectoryFile> all_files= path.get_files();
//		for(DirectoryFile f: all_files){
//			f.print_file();
//		}



		int choice=0;
		int len= path.get_files().size();
     	Runnable r = new Runnable() {
        	public void run() {
        		while(true){
	        	//	System.out.println("Thread Running...");
					ArrayList<DirectoryFile> all_files= path.get_files();
					ArrayList<DirectoryFile> temp = new ArrayList<DirectoryFile>();
        			temp=all_files;
            		all_files= new ArrayList<DirectoryFile>(path.get_files());
            		//When a new file is added
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
		while(true){
			System.out.println("1. Display\n2. Sort\n3.Search");
			System.out.println("Enter your choice: ");
			try{
				choice= sc.nextInt();
			}
			catch(InputMismatchException e){
				System.out.println("Enter a valid Integer!!");
				break;
			}
			switch (choice){
				case 1:
						for(DirectoryFile f: path.get_files())
							f.print_file();
						break;
				default:
						return ;
			//System.out.println(choice);
			}
		}
	}
}

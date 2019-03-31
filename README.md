# CS201-Portfolio-IMDB DataBase 

  Program Description:
        
          This program takes a datafile from IMDB and reads it into an AVL tree.  
      The user then can create a ".log" file.  The user can now add a movie to that file, 
      read the contents of that file, delete from a movie from that file, delete a file entirely, 
      create or edit another file or view all files.  The user has the ability to update 
      the Media Type in which they own the movie, and the Date Purchased for that movie.
      The program writes the contents of each list to their files as things are deleted.
      The program stores the existing ".log" file names in the file "ListNames.txt".
      "ListNames.txt" is written to at the end of the program being run and 
      read in at the begginning of the program being run. 
      
        
  Instructions for Compiling:
      
      The link to find the file is "https://datasets.imdbws.com/", and I used the third link down titled "titles.basics.tsv.az".
      In regards to thise file, within my make I use a line "grep "movie" data.tsv > movie_records". 
      The "data.tsv" in that grep command was the name given to the unzipped version of "titles.basics.tsv.av" 
      after using 7zip to unzip  the file.  Modify that wording to match the downloaded file on your computer.
    
  Program Stipulations:
      
      1) Name Lists Uniquely as the list search function only pulls up the first complete match.
      2) If the entered searchstring for a movie has multiple strncmp matches it will print them all, so dont be too general.
      3) Movie searches start from the beginning of the first non-article word that was entered.
      
  Decisions:
      
      1) The longest movie title is 191 characters so all of my buffers with regards to titles are 200 characters in capacity 
      2) I chose an AVL tree as my data structure for housing the archives of movies because it is easily alphabetically sorted.
         Titles beginning closest to "A" will be relatively towawrds the left and vice versa.
      3) Sticking an avl tree is advantageous for searching which is why I chose it, but it has a drawback that its initial upload of the
         data file takes ~2 minutes.  The program executes in real time and all necessary running logic can be checked within a single
         running of the program.
      4) I chose to store the names of .log files in a tree as well.  It makes it easier to store them preOrdered in file "ListNames.txt".

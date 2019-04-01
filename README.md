# CS201-Portfolio-IMDB DataBase 
 
  Link to tutorial:  https://youtu.be/UiJB3aWgqdI

  Program Description:
        
          This program takes a datafile from IMDB and reads it into an AVL tree.  
      The user then can create a ".log" file.  The user can now add a movie to that file, 
      read the contents of that file, delete a movie from that file, delete a file entirely, 
      create or edit another file or view all files.  When adding a movie to a ".log" file
      the user has the ability to update the Media Type and the Date Purchased fields for that movie.
      Media Type gives 3 options (BR, DVD, Dig), and the date field reads in a string which should be 
      inputted in (mm/dd/yyyy) format.  The program writes the contents of each list to their files as things are deleted.
      The program stores the existing ".log" file names in the file "ListNames.txt".  "ListNames.txt" is written to at the 
      end of running the program and it is read in at the begginning of the program being run. 
      
        
  Instructions for Compiling/Initial run:
      
      The link to find the file is "https://datasets.imdbws.com/", and I used the third link down on that site titled   "titles.basics.tsv.az".
      The file could also be retrieved through "wget https://datasets.imdbws.com/title.basics.tsv.gz"
      In regards to this file, within my make I use a line "grep "movie" data.tsv > movie_records" and read from the "movie_records" file. 
    
  Program Stipulations:
      
      1) Create your lists with unique names because the list search function only pulls up the first complete match. Also the search function is not case sensitive ("James.log" == "james.log").
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

IMDB: blankAVL.c main.c readIn.c

	wget https://datasets.imdbws.com/title.basics.tsv.gz
	gunzip -k title.basics.tsv.gz
	grep "movie" title.basics.tsv > movie_records

	gcc -o IMDB blankAVL.c main.c readIn.c

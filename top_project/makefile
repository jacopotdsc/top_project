CC = gcc
CFILES = process_stats.c plotter_process.c my_main.c general_stats.c
OBJECTS = process_stats.o plotter_process.o my_main.o general_stats.o
DIROBJ = obj
EXEC = top_ex

$(EXEC): $(OBJECTS) 
	$(CC) -o $@ $^ -w
	(cd $(DIROBJ) || mkdir $(DIROBJ) ) && cd $(DIROBJ)
	mv *.o $(DIROBJ)
	
%.o: %.c 
	$(CC) -c $(CFILES) -w
	

#process_stats.o: process_stats.c
#	$(CC) -c process_stats.c -w
	
#general_stat.o: general_stat.c
#	$(CC) -c general_stat.c -w
	
#plotter_process.o: plotter_process.c
#	$(CC) -c plotter_process.c -w	

# per compilare con warning
w:
	$(CC) -c $(CFILES) 
	$(CC) -o $(EXEC) $(OBJECTS) 
	(cd $(DIROBJ) || mkdir $(DIROBJ) ) && cd $(DIROBJ)
	mv *.o $(DIROBJ)

clean:
	rm $(EXEC)
	cd $(DIROBJ) && rm $(OBJECTS)
	rmdir $(DIROBJ)
	
	
# regole per dire che per fare i.o mi servono de i.h

process_stats.o: process_stats.h
general_stat.o: general_stat.h
plotter_process.o: plotter_process.h

INCLUDE_PATH=include
SOURCE_PATH=src
OUTPUT_PATH=exe

install:dependencies
		
	#gcc $(SOURCE_PATH)/main.c $(wildcard $(INCLUDE_PATH)/*) -I $(INCLUDE_PATH) -o run_program -g -lncurses;
	#gcc -I $(INCLUDE_PATH) -g -o run_program $(SOURCE_PATH)/main.c $(wildcard $(INCLUDE_PATH)/*) -lncurses ;
	#gcc -I $(INCLUDE_PATH) -g -o run_program $(SOURCE_PATH)/main.c $(SOURCE_PATH)/dfs_algorithm.c -lncurses;
	#cd $(SOURCE_PATH);
	gcc -I $(INCLUDE_PATH) -g -o run_program $(wildcard $(SOURCE_PATH)/*.c) -lncurses
	mv run_program $(OUTPUT_PATH)/

dependencies:
	mkdir $(OUTPUT_PATH)
clean:
	rm -rf exe/
save: 
	cd
	cp /home/meta/Desktop/INSIDEtheROOM/ANA_PROJE/project_maze_labyrienth/PROJE_KOD/ /media/meta/Other/UBUNTU/yedekler 
	

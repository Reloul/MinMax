CC = gcc
CFLAGS = -Wall -g -Wextra -ggdb
EXEC = exe
SRC = $(wildcard $(SRCDIR)*.c) #Fichiers sources
OBJ = $(subst $(SRCDIR), $(BINDIR), $(SRC:.c=.o))    #Fichiers objets
LDFLAGS = -lm

SAVDIR = save/
SRCDIR = src/
BINDIR = bin/
DOCDIR = doc/


all: $(EXEC)
$(EXEC) : $(OBJ) #Compilation du programme
		@mkdir -p $(SAVDIR)
		@mkdir -p $(BINDIR)
		@mkdir -p $(SRCDIR)
		@mkdir -p $(DOCDIR)
		@echo "compiling files..."
		@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
		@mv $(EXEC) $(BINDIR)
		@cp ./bin/* $(SAVDIR)
		@cp ./src/* $(SAVDIR)
		@echo "done!"

./bin/%.o : ./src/%.c   #Compilation des objets
		@$(CC) $(CFLAGS) -c $^ -o $@


.bin/%.o : ./src/%.c  #Compilation des objets
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY : clean createSave save restore doc
clean : save        #Sauvegarde des fichiers .c et .h + effacement des objets
	@echo "removing files..."
	@rm -rf $(OBJ) $(BINDIR)$(EXEC) $(DOCDIR)/html/ $(DOCDIR)/latex Doxyfile.bak Doxyfile

createSave :
	@echo "creating save folder..."
	@mkdir -p $(SAVDIR)

save: createSave
	@echo "moving files into save folder..."
	@cp -r *$(SRCDIR) src/*.h $(SAVDIR)
	@cp -r $(DOCDIR) $(SAVDIR)


restore:
	cp $(SAVDIR)*.c $(SRCDIR)
	cp $(SAVDIR)*.o $(BINDIR)
	cp $(SAVDIR)*.h $(SRCDIR)

help: #make help permet d'afficher l'aide des commandes
	@echo 'Targets list: '
	@echo ' help    - display this help'
	@echo ' all     - build the project'
	@echo ' doc     - build documentation'
	@echo ' restore - restore the code stored in save folder'
	@echo ' clean   - save all the .c and .h files and remove anything that can be generated'

doc:
	@echo "creating documentation file..."
	@echo "PROJECT_NAME = SERRES_Valentin-TP9" > Doxyfile
	@echo "OUTPUT_LANGUAGE = FRENCH" >> Doxyfile
	@echo "QUIET = YES" >> Doxyfile
	@echo "INPUT += $(SRCDIR)" >> Doxyfile
	@echo "USE_MAINPAGE = YES" >> Doxyfile
	@echo "RECURSIVE = YES" >> Doxyfile
	@echo "OPTIMIZE_OUTPUT_FOR_C = YES" >> Doxyfile
	@echo "OUTPUT_DIRECTORY = ./doc/" >> Doxyfile
	@echo "EXCLUDE = ./save/" >> Doxyfile
	@echo "running doxyfile..."
	@doxygen Doxyfile
	@echo "done!"
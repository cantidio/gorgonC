#biblioteca gorgon makefile
#	ar tv libgorgon.a lista os conteúdos da lib
#	ar ds libnome.a lista_de_ficheiros_objecto para apagar os lobjteos
#	ar rus libnome.a lista_de_ficheiros_objecto para atualizar
#	ar rs libnome.a lista_de_ficheiros_objecto para criar
COMP := gcc

all: STATIC #SHARED

STATIC: GORGON_PALETTE GORGON_PCX GORGON_SFF GORGON_SPRITE GORGON_SPRITE_FILE GORGON_SOUND GORGON_ANIMATION GORGON_ANIMATION_FILE GORGON_BACKGROUND GORGON_BACKGROUND_FILE
	ar rc libgorgon.a				\
	./obj/gorgon_palette.o			\
	./obj/gorgon_pcx.o			\
	./obj/gorgon_sff.o			\
	./obj/gorgon_sprite.o			\
	./obj/gorgon_sprite_file.o		\
	./obj/gorgon_sound.o			\
	./obj/gorgon_animation.o    		\
	./obj/gorgon_animation_file.o		\
	./obj/gorgon_background.o		\
	./obj/gorgon_background_file.o
	mv ./libgorgon.a ./static/libgorgon.a

#SHARED: GORGON_ANIMATION GORGON_ANIMATION_FILE GORGON_PALETTE GORGON_SFF GORGON_SOUND GORGON_SPRITE 
#	gcc -shared -Wl,-soname,libgorgon.so.0.0.1 -o libgorgon.so.0.0.1 \
#	./obj/gorgon_palette.o 			\	
#	./obj/gorgon_pcx.o			\
#	./obj/gorgon_sff.o			\
#	./obj/gorgon_sprite.o			\
#	./obj/gorgon_sprite_file.o		\
#	./obj/gorgon_sound.o			\
#	./obj/gorgon_animation.o		\
#	./obj/gorgon_animation_file.o		\
#	./obj/gorgon_background.o		\
#	./fmod/lib/libfmodex.so.4.08.08 	\
#	$ ln -s libfoo.so.1.0 libfoo.so.1
#	$ ln -s libfoo.so.1 libfoo.so
#	$ LD_LIBRARY_PATH=`pwd`:$LD_LIBRARY_PATH ; export LD_LIBRARY_P
#	mv ./libgorgon.so.0.0.1 ./shared/libgorgon.so.0.0.1

#update: GORGON_ANIMATION GORGON_ANIMATION_FILE GORGON_PALETTE GORGON_SFF GORGON_SPRITE 
#	ar rus libgorgon.a ./obj/sff.o ./obj/gorgon_animation.o ./obj/gorgon_animation_file.o ./obj/gorgon_palette.o ./obj/gorgon_sprite.o

GORGON_PALETTE: ./src/gorgon_palette.c ./include/gorgon_palette.h
	$(COMP) -c ./src/gorgon_palette.c
	mv gorgon_palette.o ./obj/gorgon_palette.o

GORGON_PCX: ./src/gorgon_pcx.c ./include/gorgon_pcx.h
	$(COMP) -c ./src/gorgon_pcx.c
	mv gorgon_pcx.o ./obj/gorgon_pcx.o

GORGON_SFF: ./src/gorgon_sff.c ./include/gorgon_sff.h
	$(COMP) -c ./src/gorgon_sff.c
	mv gorgon_sff.o ./obj/gorgon_sff.o

GORGON_SPRITE: ./src/gorgon_sprite.c ./include/gorgon_sprite.h
	$(COMP) -c ./src/gorgon_sprite.c
	mv gorgon_sprite.o ./obj/gorgon_sprite.o

GORGON_SPRITE_FILE: ./src/gorgon_sprite_file.c ./include/gorgon_sprite_file.h
	$(COMP) -c ./src/gorgon_sprite_file.c
	mv gorgon_sprite_file.o ./obj/gorgon_sprite_file.o

GORGON_SOUND: ./include/gorgon_sound.h ./src/gorgon_sound.c ./fmod/include/fmod.h ./fmod/lib/libfmodex.so.4.08.08
	$(COMP) -c ./src/gorgon_sound.c 
	mv gorgon_sound.o ./obj/gorgon_sound.o
		
GORGON_ANIMATION: ./src/gorgon_animation.c ./include/gorgon_animation.h
	$(COMP) -c ./src/gorgon_animation.c
	mv ./gorgon_animation.o ./obj/gorgon_animation.o

GORGON_ANIMATION_FILE: ./src/gorgon_animation_file.c ./include/gorgon_animation_file.h
	$(COMP) -c ./src/gorgon_animation_file.c
	mv gorgon_animation_file.o ./obj/gorgon_animation_file.o
	
GORGON_BACKGROUND: ./include/gorgon_background.h ./src/gorgon_background.c
	$(COMP) -c ./src/gorgon_background.c 
	mv gorgon_background.o ./obj/gorgon_background.o

GORGON_BACKGROUND_FILE: ./include/gorgon_background_file.h ./src/gorgon_background_file.c
	$(COMP) -c ./src/gorgon_background_file.c
	mv gorgon_background_file.o ./obj/gorgon_background_file.o

list:
	ar tv libgorgon.a
	
test: ./static/libgorgon.a
	$(COMP) ./testes/test.c -o ./testes/test.e ./static/libgorgon.a `allegro-config --libs` ./fmod/lib/libfmodex.so.4.08.08 -O2

#oi eu sou o fim

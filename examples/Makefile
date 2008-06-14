#examples make file
COMP:= g++

all: animation_file sprite_file

animation_file: ./animation.c ../include/gorgon.h ../static/libgorgon.a
	$(COMP) animation.c -o animation.e ../static/libgorgon.a `allegro-config --libs`

sprite_file: ./sprite.c ../include/gorgon.h ../static/libgorgon.a
	$(COMP) sprite.c -o sprite.e ../static/libgorgon.a `allegro-config --libs`

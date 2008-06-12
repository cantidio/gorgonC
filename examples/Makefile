#examples make file
COMP:= g++

all: animation

animation: ./animation.c ../include/gorgon.h ../static/libgorgon.a
	$(COMP) animation.c -o animation.e ../static/libgorgon.a `allegro-config --libs`

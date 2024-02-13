all:
	g++ Cursor.cpp Bullet.cpp Player.cpp Background.cpp Math.cpp renderwindow.cpp  Entity.cpp main.cpp -I src/include -L src/lib -o main -lmingw32 -lSDL2main -lSDL2_image -lSDL2
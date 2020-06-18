CXX = g++
CXXFLAGS = -Wall -pedantic -g -Og -std=c++14 -fsanitize=address 
LD = g++
LDFLAGS = -fsanitize=address
LDLIBS = -lSDL2 -lSDL2_image -lSDL2_ttf 
EXECUTABLE=tolkunik
FOLDER=src/

all: ${EXECUTABLE}

compile: ${EXECUTABLE}

run:
	@./${EXECUTABLE} 2>./asan.txt

${EXECUTABLE}: GameEngine.o main.o TextureManager.o GameObject.o Used.o Card.o GameState.o GUI.o Lightning.o Smoke.o UI_text.o Button.o AttackCard.o DefenseCard.o IntroState.o MenuState.o PlayState.o ConfirmState.o GameOverState.o Player.o AI.o Human.o
		${LD} ${LDFLAGS} $^ -o ${EXECUTABLE} ${LDLIBS}

%.o:
	${CXX} ${CXXFLAGS} -c $< -o $@

.PHONY: clean all compile run 

clean:
	@rm -f *.o
	@rm -f ${EXECUTABLE}
	@rm -rf doc/

GameEngine.o: ${FOLDER}GameEngine.cpp ${FOLDER}GLBL.h 
main.o: ${FOLDER}main.cpp ${FOLDER}GLBL.h ${FOLDER}GameEngine.h
TextureManager.o: ${FOLDER}TextureManager.cpp ${FOLDER}TextureManager.h
GameState.o: ${FOLDER}GameState.cpp ${FOLDER}GLBL.h ${FOLDER}GameState.h
ConfirmState.o: ${FOLDER}ConfirmState.cpp ${FOLDER}GameState.h ${FOLDER}ConfirmState.h
GameOverState.o: ${FOLDER}GameOverState.cpp ${FOLDER}GameState.h ${FOLDER}GameOverState.h
IntroState.o: ${FOLDER}IntroState.cpp ${FOLDER}GameState.h ${FOLDER}IntroState.h
MenuState.o: ${FOLDER}MenuState.cpp ${FOLDER}GameState.h ${FOLDER}MenuState.h
PlayState.o: ${FOLDER}PlayState.cpp ${FOLDER}GameState.h ${FOLDER}PlayState.h
Player.o: ${FOLDER}Player.cpp ${FOLDER}GLBL.h ${FOLDER}Player.h
AI.o: ${FOLDER}AI.cpp ${FOLDER}Player.h ${FOLDER}AI.h
Human.o: ${FOLDER}Human.cpp ${FOLDER}Player.h ${FOLDER}Human.h
Used.o: ${FOLDER}Used.cpp ${FOLDER}GameObject.h ${FOLDER}Used.h
Card.o: ${FOLDER}Card.cpp ${FOLDER}Used.h ${FOLDER}Card.h
AttackCard.o: ${FOLDER}AttackCard.cpp ${FOLDER}Card.h ${FOLDER}AttackCard.h
DefenseCard.o: ${FOLDER}DefenseCard.cpp ${FOLDER}Card.h ${FOLDER}DefenseCard.h
GameObject.o: ${FOLDER}GameObject.cpp ${FOLDER}GLBL.h ${FOLDER}GameObject.h
Button.o: ${FOLDER}Button.cpp ${FOLDER}Used.h ${FOLDER}Button.h
GUI.o: ${FOLDER}GUI.cpp ${FOLDER}GameObject.h ${FOLDER}GUI.h
Lightning.o: ${FOLDER}Lightning.cpp ${FOLDER}GameObject.h ${FOLDER}Lightning.h
Smoke.o: ${FOLDER}Smoke.cpp ${FOLDER}GameObject.h ${FOLDER}Smoke.h
UI_text.o: ${FOLDER}UI_text.cpp ${FOLDER}GameObject.h ${FOLDER}UI_text.h

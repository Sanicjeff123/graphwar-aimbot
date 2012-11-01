CC := g++ -Wall

CFLAGS := `pkg-config --cflags x11` 
 
LIBS := `pkg-config --libs x11` 

all: exe 

exe: .build/AcquirePoints.o
	${CC} .build/AcquirePoints.o ${LIBS} -o AcquirePoints

.build/AcquirePoints.o: .build src/AcquirePoints.cpp
	${CC} -c src/AcquirePoints.cpp ${CFLAGS} -o .build/AcquirePoints.o

.build:
	mkdir .build

clean:
	rm -r .build
	rm AcquirePoints

DIR1 = prog1
DIR2 = prog2
TARGET1 = program1
TARGET2 = program2

all: build

build:
	cd $(DIR1) && make $(TARGET1)
	cd $(DIR2) && make $(TARGET2)

$(TARGET1):
	cd $(DIR1) && make run

$(TARGET2):
	cd $(DIR2) && make run

clean:
	cd $(DIR1) && make clean
	cd $(DIR2) && make clean

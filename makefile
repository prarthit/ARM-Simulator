Compiler = g++
Obj = OBJ/
Src = SRC/
Exe = EXE/

# $@ means name of target eg execute or exec $< means name of first target

#Header = check.h executes.h small.h

all: $(Obj)main.o $(Obj)check.o $(Obj)executes.o $(Obj)small.o $(Obj)latency.o $(Obj)decoders.o $(Obj)topfivefun.o execute

execute: processor_simulator
	./$<

processor_simulator:
	$(Compiler) $(Obj)main.o $(Obj)check.o $(Obj)executes.o $(Obj)small.o $(Obj)latency.o $(Obj)decoders.o $(Obj)topfivefun.o -o $@

$(Obj)main.o: $(Src)main.cpp $(Src)check.h $(Src)executes.h $(Src)small.h $(Src)topfivefun.h
	$(Compiler) -c $<
	mv main.o $(Obj)

$(Obj)check.o: $(Src)check.cpp $(Src)check.h $(Src)executes.h $(Src)small.h
	$(Compiler) -c $<
	mv check.o $(Obj)

$(Obj)executes.o: $(Src)executes.cpp $(Src)check.h $(Src)executes.h $(Src)small.h $(Src)topfivefun.h
	$(Compiler) -c $<
	mv executes.o $(Obj)

$(Obj)small.o: $(Src)small.cpp $(Src)check.h $(Src)executes.h $(Src)small.h
	$(Compiler) -c $<
	mv small.o $(Obj)

$(Obj)latency.o: $(Src)latency.cpp $(Src)small.h
	$(Compiler) -c $<
	mv latency.o $(Obj)

$(Obj)decoders.o: $(Src)decoders.cpp $(Src)topfivefun.h $(Src)check.h $(Src)executes.h $(Src)small.h
	$(Compiler) -c $<
	mv decoders.o $(Obj)

$(Obj)topfivefun.o: $(Src)topfivefun.cpp $(Src)topfivefun.h $(Src)check.h $(Src)executes.h $(Src)small.h
	$(Compiler) -c $<
	mv topfivefun.o $(Obj)

clean:
	rm processor_simulator $(Obj)main.o $(Obj)check.o $(Obj)executes.o $(Obj)small.o $(Obj)latency.o $(Obj)topfivefun.o $(Obj)decoders.o

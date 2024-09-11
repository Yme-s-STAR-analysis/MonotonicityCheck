all: run runOri runZero

run: main.cxx GraphGenerator.cxx FitTool.cxx
	g++ $^ -o $@ `root-config --libs --cflags` -std=c++17 -O3

runOri: mainOri.cxx GraphGenerator.cxx FitTool.cxx
	g++ $^ -o $@ `root-config --libs --cflags` -std=c++17 -O3

runZero: mainZero.cxx GraphGenerator.cxx FitTool.cxx
	g++ $^ -o $@ `root-config --libs --cflags` -std=c++17 -O3

UnitTest_Graph: UnitTest_Graph.cxx GraphGenerator.cxx
	g++ $^ -o $@ `root-config --libs --cflags` -std=c++17 -O3
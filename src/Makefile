
EXE = iccad19gr 
CXX = g++
SYSTEM = x86-64_linux
LIBFORMAT = static_pic
OBJECT = ./objects

#CXXOPTS = -m64 -O2 -pg -fopenmp -fPIC -fno-strict-aliasing -fexceptions -fpermissive -DNDEBUG -DIL_STD -Wno-ctor-dtor-privacy 
CXXOPTS = -m64 -O2 -fopenmp -fPIC -fno-strict-aliasing -fexceptions -fpermissive -DNDEBUG -DIL_STD -Wno-ctor-dtor-privacy 
#CFLAGS = $(CXXOPTS) $(LIBINCLUDE) -fopenmp -std=c++11

#CFLAGS_NW = -std=c++11 -static-libstdc++ -O2 -pg -fopenmp -fpermissive -g -ggdb -DNDEBUG -DIL_STD -Wno-ctor-dtor-privacy $(LIBINCLUDE)
#CFLAGS = -std=c++11 -static-libstdc++ -O2 -pg -fopenmp -fpermissive -g -W -ggdb -DNDEBUG -DIL_STD -Wno-ctor-dtor-privacy $(LIBINCLUDE)
CFLAGS_NW = -std=c++11 -static-libstdc++ -O2 -fopenmp -fpermissive -DNDEBUG -DIL_STD -Wno-ctor-dtor-privacy $(LIBINCLUDE)
CFLAGS = -std=c++11 -static-libstdc++ -O2 -fopenmp -fpermissive -DNDEBUG -DIL_STD -Wno-ctor-dtor-privacy $(LIBINCLUDE)

# include library settings..
LIBINCLUDE = -I$(SRCHASH)/include -I$(SRCDEF)/include -I$(SRCLEF)/include -I$(BOOST)/include -I$(CPLEXDIR) -I$(CONCERTDIR)

# linking flag settings
LINKCFLAGS = $(CFLAGS) -static-libstdc++ $(DEFLIBS) $(LEFLIBS) $(CPLEXLIBS) $(CONCERTLIBS) $(LIBGOMP)

# source settings.
SRCLEF = ../lib/lef/5.8-p027
SRCDEF = ../lib/def/5.8-p027
SRCHASH = /home/tool/cpplib/sparsehash/install/2.0.3
BOOST = /home/tool/cpplib/boost/install/1.67.0
CPLEXDIR = /home/tool/ibm/install/12.7.0/cplex/include 
CONCERTDIR = /home/tool/ibm/install/12.7.0/concert/include

DEFLIBS         = -L$(SRCDEF)/lib -ldef -ldefzlib -lcdef -lcdefzlib
LEFLIBS         = -L$(SRCLEF)/lib -llef -llefzlib -lclef -lclefzlib

CPLEXLIBS 		= -L/home/tool/ibm/install/12.7.0/cplex/lib/$(SYSTEM)/$(LIBFORMAT) -lilocplex -lcplex
CONCERTLIBS 	= -L/home/tool/ibm/install/12.7.0/concert/lib/$(SYSTEM)/$(LIBFORMAT) -lconcert -lm -pthread -fopenmp -static-libstdc++ -std=c++11

DEBUG = -g -gstrict-dwarf -gdwarf-2

LIBGOMP = -L/home/tool/gcc/install/5.4.0/lib64/libgomp.a -static

SRC = ./object/hgGrid.o \
	  ./object/hgRtree.o \
	  ./object/hgGeometry.o \
	  ./object/hgFunc.o	\
	  ./object/hgInit.o	\
	  ./object/hgGR.o \
	  ./object/hgNet.o \
	  ./object/hgDRC.o \
	  ./object/hgPinExt.o \
	  ./object/hgPinAccess.o \
	  ./object/hgDefReader.o \
	  ./object/hgLefReader.o \
	  ./object/hgGuideReader.o \
	  ./object/hgImg.o \
	  ./object/main.o \
	  ./object/mymeasure.o

#main.o hgFunc.o hgLefreader.o hgDefreader.o hgGuidereader.o hgGlobal.o hgGrid.o hgUtil.o hgILP.o hgTA.o hgShift.o \
	  hgPin.o hgNet.o \
	  hgVia.o hgPreRoute.o hgMinArea.o hgOverlap.o hgRipup.o hgMaze.o hgDRC.o hgPinExt.o hgTopology.o hgConnect.o mymeasure.o 

$(EXE): $(SRC)
	@echo " "
	@echo "Linking..."
	@echo " "
	#$(CXX) $(DEBUG) $(CXXOPTS) $^ -o $@ $(LINKCFLAGS)
	$(CXX) $(CXXOPTS) $^ -o $@ $(LINKCFLAGS)
	@echo " "
	@echo "Linking is Completed !!"
	@echo " "
	@echo "Tagging..."
	@echo " "
	ctags -R
	@echo " "
	@echo "Finished..!"
	@echo " "
	@echo "GNU GCC/G++ compiler has been used as"
	@g++ --version

./object/hgGeometry.o: hgGeometry.cpp hgGeometry.h
	$(CXX) $(CFLAGS) -c -o $@ $<

./object/hgGrid.o: hgGrid.cpp hgGrid.h
	$(CXX) $(CFLAGS) -c -o $@ $<

./object/hgRtree.o: hgRtree.cpp hgRtree.h
	$(CXX) $(CFLAGS) -c -o $@ $<

./object/hgFunc.o: hgFunc.cpp hgRouter.h
	$(CXX) $(CFLAGS) -c -o $@ $<

./object/hgInit.o: hgInit.cpp hgRouter.h
	$(CXX) $(CFLAGS) -c -o $@ $<

./object/hgGR.o: hgGR.cpp hgRouter.h
	$(CXX) $(CFLAGS) -c -o $@ $<

./object/hgNet.o: hgNet.cpp hgCircuit.h
	$(CXX) $(CFLAGS) -c -o $@ $<

./object/hgDRC.o: hgDRC.cpp hgDRC.h
	$(CXX) $(CFLAGS) -c -o $@ $<

./object/hgPinExt.o: hgPinExt.cpp hgRouter.h
	$(CXX) $(CFLAGS) -c -o $@ $<
	
./object/hgPinAccess.o: hgPinAccess.cpp hgRouter.h
	$(CXX) $(CFLAGS) -c -o $@ $<

./object/hgDefReader.o: hgDefReader.cpp hgCircuit.h
	$(CXX) $(CFLAGS_NW) -c -o $@ $<

./object/hgLefReader.o: hgLefReader.cpp hgCircuit.h
	$(CXX) $(CFLAGS_NW) -c -o $@ $<

./object/hgGuideReader.o: hgGuideReader.cpp hgCircuit.h
	$(CXX) $(CFLAGS) -c -o $@ $<

./object/hgImg.o: hgImg.cpp hgImg.h hgRouter.h
	$(CXX) $(CFLAGS) -c -o $@ $<

./object/main.o: main.cpp hgCircuit.h 
	$(CXX) $(CFLAGS) -c -o $@ $<

./object/mymeasure.o: mymeasure.cpp mymeasure.h
	$(CXX) $(CFLAGS) -c -o $@ $<


.PHONY: clean
clean: 
	/bin/rm -f ./object/*.o 2> /dev/null;  /bin/rm -f $(EXE) 2> /dev/null; /bin/rm -f defreader defwriter lefreader lefwriter 2> /dev/null; /bin/rm -f *.log;



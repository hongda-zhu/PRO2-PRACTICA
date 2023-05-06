OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Area_Espera.o Prioridad.o Procesador.o Proceso.o Cluster.o
	g++ -o program.exe *.o 

program.o: program.cc Area_Espera.cc Area_Espera.hh Prioridad.cc Prioridad.hh Procesador.cc Procesador.hh Proceso.cc Proceso.hh Cluster.cc Cluster.hh
	g++ -c program.cc $(OPCIONS) 

Area_Espera.o: Area_Espera.cc Area_Espera.hh 
	g++ -c Area_Espera.cc $(OPCIONS) 

Prioridad.o: Prioridad.cc Prioridad.hh
	g++ -c Prioridad.cc $(OPCIONS) 

Procesador.o: Procesador.cc Procesador.hh
	g++ -c Procesador.cc $(OPCIONS) 

Proceso.o: Proceso2.cc Proceso.hh
	g++ -c Proceso2.cc $(OPCIONS) 

Cluster.o: Cluster.cc Cluster.hh
	g++ -c Cluster.cc $(OPCIONS) 

clean:
	del *.o /f /q
	del *.exe /f /q
	del *.tar /f /q

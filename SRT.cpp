#include<iostream>
#include<string>
#include<list>
#include<ctime>
#include <iomanip>

class BCP{
    public:
        std::string nombre;
        double tServicio, tLlegada, tEstancia, tTiempoEstancia, tRestante, tCPU;

};
//ordenar los procesos
void SRT(std::list<BCP>& procesos) {
    procesos.sort([](const BCP& a, const BCP& b) {
        return a.tRestante < b.tRestante;
    });
}

int main(){

    int n = 50;
    int numSimulaciones = 30;
    double tasaCreacion = 0.3;
    double tablaResultados[numSimulaciones+1][2] = {0}; // [0] = Tiempo de Estancia, [1] = Tiempo de Servicio
    std::srand(static_cast<unsigned>(std::time(0)));
    
    for (int i = 0; i < numSimulaciones; i++){
        int t=0;
        int cantidadProcesos = 0;
        std::list<BCP> procesos;
        std::list<BCP> procesosFinalizados;

        while(cantidadProcesos<n || !procesos.empty()){
            double random_number = static_cast<double>(std::rand()) / RAND_MAX;
            //Creacion de Servicio y encolarlos procesos
            if(random_number<tasaCreacion && cantidadProcesos<n){
                BCP proceso;
                proceso.nombre = "Proceso " + std::to_string(cantidadProcesos + 1);
                proceso.tLlegada=t;
                proceso.tServicio=rand()%11+2;
                proceso.tRestante=proceso.tServicio;
                proceso.tCPU=0;
                proceso.tEstancia=0;
                procesos.push_back(proceso); 
                SRT(procesos);
                cantidadProcesos++;
    
            }
            
            // Ta ocupado el CPU
            if(!procesos.empty() && procesos.front().tRestante>0){
                procesos.front().tRestante--;
                procesos.front().tCPU++;
            } 
            //Termina proceso y hay cola
            if(!procesos.empty() && procesos.front().tRestante==0){
                procesos.front().tEstancia = t - procesos.front().tLlegada;
                procesos.front().tTiempoEstancia = procesos.front().tEstancia / procesos.front().tServicio;
                procesosFinalizados.push_back(procesos.front());
                procesos.pop_front();
            }
    
            t++;
            
        }
        
        double sumaEstancia = 0;
        double sumatasaTES = 0;

        for (auto it = procesosFinalizados.begin(); it != procesosFinalizados.end(); ++it)
        {
           sumaEstancia=it->tEstancia + sumaEstancia;
           sumatasaTES = it->tTiempoEstancia + sumatasaTES;
        }
     
        tablaResultados[i][0]= sumaEstancia / n;
        tablaResultados[i][1] = sumatasaTES / n;

        
        procesos.clear();
        procesosFinalizados.clear();
    }
// Fin del For

    for (int i = 0; i < 2;i++)
    {
        for (int j = 0; j < numSimulaciones; j++){

            //iter+1 es la ultima fila que da los promedios finales
            tablaResultados[numSimulaciones][i] += tablaResultados[j][i];
            
        }

        tablaResultados[numSimulaciones][i] = tablaResultados[numSimulaciones][i] / numSimulaciones;
    }

    std::cout<<"No.Sim|TE|TE/TS| \n";
    // Solo es para imprimir la tabla
    for (int i = 0; i < numSimulaciones+1; i++)
    {
        if (i<9)
        {
            std::cout<<"0"<< i+1;
        }else{
            std::cout << i+1;
            
        }
        
        for (int j = 0; j < 2; j++)
        {
            if (j ==1)
            {
                std::cout << "" << "|" << tablaResultados[i][j];
            }else{
                std::cout << " " << "|" << tablaResultados[i][j];
            }
            
        } 
        std::cout << "|\n";
      
    }

    std::cout << "Tiempo promedio de estancia: " << tablaResultados[numSimulaciones][0] << "\n";
    std::cout << "Tasa de TE/TS: " << tablaResultados[numSimulaciones][1] << "\n";
}
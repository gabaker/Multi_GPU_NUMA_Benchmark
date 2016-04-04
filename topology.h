
//benchmark header
#ifndef BENCH_HEADER_INC
#define BENCH_HEADER_INC
#include "benchmark.h"
#endif

#ifndef TOPOLOGY_CLASS_INC
#define TOPOLOGY_CLASS_INC
class SystemTopo
{
   public:
      void GetTopology(hwloc_topology_t &dupTopology);

      // Print system hardware properties and topology
      void PrintTopology(std::ofstream &OutFile);
      void PrintDeviceProps(BenchParams &params);

      //Topology pinning - numa and cpuset
      void PinNumaNode(int nodeIdx);
      void PinSocket(int socketIdx);
      void PinCoreBySocket(int coreIdx, int socketIdx);
      //void PinPUBySocket(int socketIdx, int puIdx);
      //void PinPURange(int FirstPU, int LastPU);
      //void PinNumaNodeByPU(int puIdx); 
 
      //Memory management by cpu/nodes/devices
      void * AllocMemByNode(int nodeIdx, long long numBytes);
      void * AllocMemBySocket(int socketIdx, long long numBytes);
      void AllocDeviceMem(void **addr, long long numBytes, int deviceIdx);
      void SetHostMem(void *addr, int value, long long numBytes);
      void SetDeviceMem(void *addr, int value, long long numBytes, int deviceIdx);
      void FreeMem(void *addr, long long numBytes);     
      void FreeDeviceMem(void *addr, int deviceIdx);
      bool DeviceUVA(int deviceIdx);  
      bool DeviceGroupUVA(int deviceA, int deviceB); 
      bool DeviceGroupCanP2P(int deviceA, int deviceB);
      void DeviceGroupSetP2P(int deviceA, int deviceB, bool status); 

      // Device Utility Functions
      void SetActiveDevice(int devIdx);
      void ResetDevices(); 
      std::string GetDeviceName(int devIdx);
      int NumPeerGroups();      
      std::vector<std::vector<int> > GetPeerGroups();

      //return class local variables
      int NumNodes();
      int NumSockets();
      int NumCores();
      int NumPUs();  
      int NumCoresPerSocket();
      int NumPUsPerCore();
      int NumGPUs();

      SystemTopo();
      ~SystemTopo();

   private: 
      // HWLOC topology object
      hwloc_topology_t topology;

      //Device Info
      cudaDeviceProp *devProps;
      std::vector<std::vector<int> > PeerGroups;
      int PeerGroupCount;

      // Depths of obj types
      int TopoDepth;
      int NodeDepth;
      int SocketDepth;
      int CoreDepth;
      int PUDepth;

      // Numbers by type and hierarchy level
      int NodesInSystem;
      int SocketsInSystem;
      int PUsInSystem;
      int CoresInSystem;
      int CoresPerSocket;
      int PUsPerCore;
      int NumDevices;

      // Structure types
      bool HyperThreaded;
      bool SymmetricTopo;

      void GetAllDeviceProps(); 
      void InitTopology();
      void ParseTopology();
      void FreeTopology();
};
#endif


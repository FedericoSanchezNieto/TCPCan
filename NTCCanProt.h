#include "EthInc.h" 
#include "NTC.h"

struct {
  short CanId;
  long   Data;
} MsgFormat; 


class NTCCanProf{
 private:
  EthInc *rcvport; 
  EthInc *sndport; 
  int requestid; 

 public:
  EthInc(std::string Address,int port); 
  std::string CreateRequest(int CanId,int ReqId,long Msg);
  void   Request(int CanId,int ReqId,int Msg);
  
  int    WaitAnswer(char *msg, bool wait); 
  void   DecodeAnswer(long *msg); 
  void ReportCanError(short errcode);


  // Specific Commands 
  void Abort(int CanId); `

 

}

#include "NTCanProt.h"

NTCCanProt::NTCanProt(std::string Address,int port){

  rcvport = new EthInt("",port,true);

  sndport =   ethcan = new EthInt(Address,port,false);

}


void NTCCanProt::Request(int CanId,int ReqId,long Msg) {

  MsgFormat message = CreateRequest(CanId,ReqId,Msg);

  char *msg = (char*) message; 

  ethcan->Send(msg);
}

MsgFormat NTCCanProt::CreateRequest(int CanId,short ReqId,long Msg) {

  string message; 

  MsgFormat format; 
  format.CanId = CanId&CANIDMASK;                                       // 2 bytes          
  format.Data  = (Msg&PAYLOADMASK) | ((ReqId&0xREQIDMASK)<<REQIDSHIFT); // 1 byte |  7 bytes

  return format;
}

int NTCCanProt::WaitAnswer(char *msg, int &length, bool wait){
  int retcode; 

  do{ 
    retcode = ethcan->Receive(msg); 
  }while( retcode == 1 && wait );  // timeout 
  
  if(retcode == 2 ) exit(errno); 
  
  return retcode; 
}

void   NTCCanProt::DecodeAnswer(long *msg,int length){
   
  for( int i = 0; i < length; i++ ) {
    int Byte0 = (msg[i]>>56)&0xFF; 
    if( Byte0 == 0x0 ) {// Error 
      short errorcode = (msg[i]>>48)&0xFF;
      ReportCanError(errorcode); 

 
      

      }

    }


    int FrameNumber = (Byte0>>5)&0x7;
    int AnsId = Byte0&0x1F;
    
  }
  
}

void NTCCanProt::ReportCanError(short errcode){

  switch(errrcode)
    {
    case 0x01; 
    std::cout<< "Unknown command" << std::endl;
    break;
    case 0x02; 
    std::cout<< "Wrong Number of Parameters" << std::endl;
    break;
    case 0x03; 
    std::cout<< "Wrong frame number sequenced" << std::endl;
    break;
    case 0x04; 
    std::cout<< "Frame sequence timeout" << std::endl;
    break;
    case 0x05; 
    std::cout<< "Command not yet supported" << std::endl;
    break;
    case 0x06; 
    std::cout<< "Wrong expected command" << std::endl;
    break;
    case 0x07; 
    std::cout<< "Rejected command on uninitialised node" << std::endl;
    break;
    case 0x09; 
    std::cout<< "Protection Error" << std::endl;
    break;
    default: 
      std::cout << " Unknown error " << errcode << std::endl;
      break;
    }
  return;
} 

void NTCCanProt:Abort(int CanId){

  Request(CanId,++requestid,R_ABORT); 

}

#include "EthInt.h"
#include <iostream>

int main(int argc,char **argv){

  EthInt *ethcan; 

  if( !strcmp(argv[1],"R") ) {
    std::cout << "Receiving " << std::endl;
    ethcan = new EthInt("127.0.0.1",12345,true);
    while(1){
      char msg[MSGSIZE];
      ethcan->Receive(msg);


      std::string msgstring(msg);
      std::cout << msgstring << std::endl; 
    }
  }
  else {
    char msg[MSGSIZE];
    bool ok = true;
    ethcan = new EthInt("127.0.0.1",12345,false);
    while(ok){
    fprintf(stdout,"Message: ");
    scanf("%s",msg);
    fprintf(stdout,"\n");
    ok = (msg[0] != '0');
    std::string message(msg);
    ethcan->Send(message.c_str());
    }
  }

  return 0;
}

const int BT_BUF_LEN=128;

class RecBuf{  
    char receiveStr[BT_BUF_LEN+16];
    int receivePos = 0;
    int cmdNamePos = -1;
    public:
    String cmd = ""; 
    String val = "";
    String origVal = "";
    bool onRecv(int c, int otherTerm =0) {
      if (receivePos < BT_BUF_LEN) {
          receiveStr[receivePos++] = (char)c;
          receiveStr[receivePos] = 0;
          if (c == ':') {
            cmdNamePos = receivePos;
          }
          if (c== '\n' || c == otherTerm) {
            receiveStr[receivePos-1]=0;
            if (receivePos >= 2 && receiveStr[receivePos-2] =='\r')receiveStr[receivePos-2]= 0;
            receivePos = 0;
            origVal = receiveStr;
            if (cmdNamePos >=0) {
              cmd = origVal.substring(0,cmdNamePos-1);
              val = origVal.substring(cmdNamePos);
            }else {
              cmd = "";
              val = origVal;
            }
            cmdNamePos = -1;
            return true;
          }
        }else {
          receivePos = 0; //warning, over flow
        }
        return false;
    }
};

#define TFT_RST 0 //p33
#define TFT_CS  1 //p27
#define TFT_RS  2 //p26
#define TFT_WR  3 //p25
#define TFT_RD  4 //p32

volatile const unsigned char P0[8] = {14,13,11,9,8,7,6,5}; //p00-p07
volatile const unsigned char P1[8] = {22,21,20,19,18,17,16,15}; //p10-p17
#define TFT_XMAX 176
#define TFT_YMAX 220

void TFT_WriteCmd(unsigned int cmd);
void TFT_WriteData(unsigned int dat);
void TFT_WriteCmdData(unsigned int cmd,unsigned int dat);
void TFT_Init();
void TFT_SetWindow(unsigned int xStart,unsigned int yStart,unsigned int xEnd,unsigned int yEnd);
void TFT_ClearScreen(unsigned int color);

//can add oldCmd and oldDat that hold last state, check if the state is same as last one so do not have to call digitalWrite.
#define writeData(h,l) {for (int i = 0; i<8; i++) {digitalWriteFast(P1[i], bitRead(h, i));digitalWriteFast(P0[i], bitRead(l, i));}}

static inline void TFT_WriteCmd(unsigned int cmd){
    unsigned char cmdH,cmdL;
    cmdH = cmd >> 8;
    cmdL = cmd & 0xff;
    
    digitalWriteFast(TFT_WR, HIGH);
    digitalWriteFast(TFT_CS, LOW);
    digitalWriteFast(TFT_RS, LOW);
    digitalWriteFast(TFT_RD, HIGH);

    writeData(cmdH,cmdL)
    
    digitalWrite(TFT_WR, LOW);
    digitalWriteFast(TFT_WR, HIGH);
    digitalWriteFast(TFT_CS, HIGH);
}


static inline void TFT_WriteData(unsigned int dat){
    unsigned char datH,datL;
    datH = dat >> 8;
    datL = dat & 0xff;
    
    digitalWriteFast(TFT_WR, HIGH);
    digitalWriteFast(TFT_CS, LOW);
    digitalWriteFast(TFT_RS, HIGH);
    digitalWriteFast(TFT_RD, HIGH);
    
    writeData(datH,datL)
    
    digitalWriteFast(TFT_WR, LOW);
    digitalWrite(TFT_WR, HIGH);
    digitalWriteFast(TFT_CS, HIGH);
}



void TFT_WriteCmdData(unsigned int cmd,unsigned int dat){
    TFT_WriteCmd(cmd);
    TFT_WriteData(dat);
}


void TFT_Init(){
    unsigned int i;
    
    digitalWriteFast(TFT_RST, HIGH);
    for (i=500; i>0; i--);
    digitalWriteFast(TFT_RST, LOW);
    for (i=500; i>0; i--);
    digitalWriteFast(TFT_RST, HIGH);
    for (i=500; i>0; i--);
    
    digitalWriteFast(TFT_CS, LOW);
    
    TFT_WriteCmdData(0x0000, 0x0001);
    TFT_WriteCmdData(0x0007, 0x0000);
    TFT_WriteCmdData(0x0012, 0x0000);
    TFT_WriteCmdData(0x00A4, 0x0001);
    
    for(i=5000; i>0; i--);
    
    //--------GAMMA SETTINGS---------
    TFT_WriteCmdData(0x0008, 0x0808);
    TFT_WriteCmdData(0x0018 ,0x0001);
    TFT_WriteCmdData(0x0010, 0x11B0);
    TFT_WriteCmdData(0x0011, 0x0000);
    TFT_WriteCmdData(0x0012, 0x1115);
    TFT_WriteCmdData(0x0013, 0x8B0B);
    TFT_WriteCmdData(0x0012, 0x1135);
    TFT_WriteCmdData(0x0014, 0x8000);
    TFT_WriteCmdData(0x0001, 0x0100);
    TFT_WriteCmdData(0x0002, 0x0700);
    TFT_WriteCmdData(0x0003, 0x1030);
    TFT_WriteCmdData(0x0070, 0x1B00);
    
    TFT_WriteCmdData(0x0071, 0x0001);
    TFT_WriteCmdData(0x0090, 0x0002);
    TFT_WriteCmdData(0x0091, 0x0000);
    TFT_WriteCmdData(0x0092, 0x0001);
    TFT_WriteCmdData(0x0007, 0x0001);
    for(i=5000; i>0; i--);
    
    TFT_WriteCmdData(0x0007, 0x0021);
    for(i=5000; i>0; i--);
    
    TFT_WriteCmdData(0x0012, 0x1135);
    TFT_WriteCmdData(0x0007, 0x0233);                 
    
    TFT_WriteCmd(0x0022);
}

void TFT_SetWindow(unsigned int xStart,unsigned int yStart,unsigned int xEnd,unsigned int yEnd){
    TFT_WriteCmdData(0x0050, xStart);   //水平线起始
    TFT_WriteCmdData(0x0052, yStart);  //垂直线起始
    TFT_WriteCmdData(0x0051, xEnd);  //水平线结束
    TFT_WriteCmdData(0x0053, yEnd);  //垂直线结束
    
    TFT_WriteCmdData(0x0020, xEnd);
    TFT_WriteCmdData(0x0021, yEnd);
    
    TFT_WriteCmd(0x0022);
}



void TFT_ClearScreen(unsigned int color){
    unsigned int i, j;
    
    TFT_SetWindow(0, 0, TFT_XMAX-1, TFT_YMAX-1);   //作用区域
    for(i=0; i<TFT_XMAX; i++)
    {
        for (j=0; j<TFT_YMAX; j++)
        {
            TFT_WriteData(color);
        }
    }
}

void setup() {
  // put your setup code here, to run once:
  for(int i = 0;i<23;i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }
  Serial.begin(9600);
  TFT_Init();
  TFT_ClearScreen(0xffff);
}

inline void GUI_Dot(unsigned int x,unsigned int y,unsigned int color);

inline void GUI_Dot(unsigned int x,unsigned int y,unsigned int color){
  TFT_SetWindow(x,y,x,y);
  TFT_WriteData(color);
}


unsigned int color = 0xf800;
unsigned i=0,j=0;
void loop() {
  for(;;){
  TFT_ClearScreen(0xf800);
  TFT_ClearScreen(0x07e0);
  TFT_ClearScreen(0x001f);
  }
}

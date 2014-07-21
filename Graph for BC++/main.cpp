//---------------------------------------------------------------------------
#include <math.h>
#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MSCommLib_OCX"
#pragma resource "*.dfm"

#define GRAPH_SIZE 100

TForm1 *Form1;

int   GraphSize[4] = { 0, 0, 0, 0 };
TList *pGraphData[4];

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
    pGraphData[0] = new TList;
    pGraphData[1] = new TList;
    pGraphData[2] = new TList;
    pGraphData[3] = new TList;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
    delete pGraphData[0];
    delete pGraphData[1];
    delete pGraphData[2];
    delete pGraphData[3];
}
//---------------------------------------------------------------------------

void AddGraphData( int channel, double data )
{
    double *punit = new double;
    *punit = data;
    if( GraphSize[channel] == GRAPH_SIZE )
    {
        GraphSize[channel]--;
        pGraphData[channel]->Delete(0);
    }
    GraphSize[channel]++;
    pGraphData[channel]->Add( (void *)punit );
}

void UpdateGraphView( int channel )
{
    int cnt;

    if( channel == 0 ) Form1->Series1->Clear();
    if( channel == 1 ) Form1->Series2->Clear();
    if( channel == 2 ) Form1->Series3->Clear();
    if( channel == 3 ) Form1->Series4->Clear();
    for( cnt = 0; cnt < GraphSize[channel]; cnt++ )
    {
        if( channel == 0 ) Form1->Series1->Add( *((double *)pGraphData[channel]->Items[cnt]), AnsiString(cnt), 0xffff00 );
        if( channel == 1 ) Form1->Series2->Add( *((double *)pGraphData[channel]->Items[cnt]), AnsiString(cnt), 0xffff00 );
        if( channel == 2 ) Form1->Series3->Add( *((double *)pGraphData[channel]->Items[cnt]), AnsiString(cnt), 0xffff00 );
        if( channel == 3 ) Form1->Series4->Add( *((double *)pGraphData[channel]->Items[cnt]), AnsiString(cnt), 0xffff00 );
    }
    for( ; cnt < GRAPH_SIZE; cnt++ )
    {
        if( channel == 0 ) Form1->Series1->Add( 0.0, AnsiString(cnt), 0xffff00 );
        if( channel == 1 ) Form1->Series2->Add( 0.0, AnsiString(cnt), 0xffff00 );
        if( channel == 2 ) Form1->Series3->Add( 0.0, AnsiString(cnt), 0xffff00 );
        if( channel == 3 ) Form1->Series4->Add( 0.0, AnsiString(cnt), 0xffff00 );
    }
}


void __fastcall TForm1::TestTimerTimer(TObject *Sender)
{
    static double value = 0.0;
    value += 0.01;
    AddGraphData( 0, 2.0 + 1.0 * sin( 5 * value ) );
    AddGraphData( 1, 2.0 + 1.5 * sin( 2 * value ) );
    AddGraphData( 2, 2.0 + 0.5 * sin( 7 * value ) );
    AddGraphData( 3, 2.0 + 1.3 * sin( 9 * value ) );
    UpdateGraphView( 0 );
    UpdateGraphView( 1 );
    UpdateGraphView( 2 );
    UpdateGraphView( 3 );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TestOnBtnClick(TObject *Sender)
{
    TestTimer->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TestOffBtnClick(TObject *Sender)
{
    TestTimer->Enabled = false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::MSComm1Comm(TObject *Sender)
{
   struct
   {
       char ch;
       float value;
   }Packet;
   AnsiString rvStr, viewStr;

   switch( MSComm1->CommEvent )
   {
      case comEvReceive:
         rvStr = MSComm1->Input;
         viewStr.printf("Loaded %.2x %.2x %.2x %.2x %.2x",rvStr[0], rvStr[1], rvStr[2], rvStr[3], rvStr[4]);
         memcpy( (void *)&Packet, (void *)rvStr.c_str(), MSComm1->InputLen );
         AddGraphData( Packet.ch, Packet.value );
         UpdateGraphView( Packet.ch );
         StatusPanel->Caption = viewStr;
         break;
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SerialOnBtnClick(TObject *Sender)
{
   MSComm1->PortOpen = true;
   StatusPanel->Caption = "Serial Opened : COM" + AnsiString(MSComm1->CommPort) + "," + MSComm1->Settings;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SerialOffBtnClick(TObject *Sender)
{
   MSComm1->PortOpen = false;
   StatusPanel->Caption = "Serial Not Opened";
}
//---------------------------------------------------------------------------


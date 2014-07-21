//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include "MSCommLib_OCX.h"
#include <OleCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TChart *Chart1;
        TChart *Chart2;
        TChart *Chart3;
        TChart *Chart4;
        TFastLineSeries *Series1;
        TFastLineSeries *Series2;
        TFastLineSeries *Series3;
        TFastLineSeries *Series4;
        TButton *TestOnBtn;
        TTimer *TestTimer;
        TButton *TestOffBtn;
        TButton *SerialOnBtn;
        TMSComm *MSComm1;
        TPanel *StatusPanel;
        TButton *SerialOffBtn;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall TestTimerTimer(TObject *Sender);
        void __fastcall TestOnBtnClick(TObject *Sender);
        void __fastcall TestOffBtnClick(TObject *Sender);
        void __fastcall MSComm1Comm(TObject *Sender);
        void __fastcall SerialOnBtnClick(TObject *Sender);
        void __fastcall SerialOffBtnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

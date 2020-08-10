#include <TGButton.h>
#include <TGFrame.h>
#include <TGLabel.h>
#include <TGTextEntry.h>
#include <TVirtualX.h>
#include <RQ_OBJECT.h>

class MyDialog
{

    RQ_OBJECT("MyDialog")

private:
    TGTransientFrame *fMain;
    TGCompositeFrame *fHor1;
    TGButton *fOk;
    TGGroupFrame *fGframe;
    TGTextEntry *fText;
    TGLabel *fLabel;

public:
    MyDialog(const TGWindow *p, const TGWindow *main, UInt_t w, UInt_t h,
             UInt_t options = kVerticalFrame);
    virtual ~MyDialog();

    // slots
    void CloseWindow();
    void DoOK();
    void DoSetlabel();
};

MyDialog::MyDialog(const TGWindow *p, const TGWindow *main, UInt_t w, UInt_t h,
                   UInt_t options)
{
    // 1st: to create an window with respect to its parent (main) window

    fMain = new TGTransientFrame(p, main, w, h, options);
    fMain->Connect("CloseWindow()", "MyDialog", this, "CloseWindow()");

    fHor1 = new TGHorizontalFrame(fMain, 80, 20, kFixedWidth);
    fOk = new TGTextButton(fHor1, " &Ok ", 1);
    fOk->Connect("Clicked()", "MyDialog", this, "DoOK()");
    fHor1->AddFrame(fOk, new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX,
                                           4, 4, 4, 4));
    fHor1->Resize(150, fOk->GetDefaultHeight());
    fMain->AddFrame(fHor1, new TGLayoutHints(kLHintsBottom | kLHintsRight, 2, 2, 5, 1));

    // 2nd: create widgets in the dialog
    fText = new TGTextEntry(fMain, new TGTextBuffer(100));
    fText->SetToolTipText("Enter the label and hit Enter key");
    fText->Connect("ReturnPressed()", "MyDialog", this, "DoSetlabel()");
    fMain->AddFrame(fText, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 5, 5));
    fGframe = new TGGroupFrame(fMain, "Last Input");
    fLabel = new TGLabel(fGframe, "No Intut ");
    fGframe->AddFrame(fLabel, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 5, 5));
    fMain->AddFrame(fGframe, new TGLayoutHints(kLHintsExpandX, 2, 2, 1, 1));
    fText->Resize(150, fText->GetDefaultHeight());

    fMain->MapSubwindows();
    fMain->Resize(fMain->GetDefaultSize());

    // position of the dialog relative to the parent's window
    Window_t wdum;
    int ax, ay;
    gVirtualX->TranslateCoordinates(main->GetId(), fMain->GetParent()->GetId(),
                                    (Int_t)(((TGFrame *)main)->GetWidth() - fMain->GetWidth()) >> 1,
                                    (Int_t)(((TGFrame *)main)->GetHeight() - fMain->GetHeight()) >> 1,
                                    ax, ay, wdum);
    fMain->Move(ax, ay);

    fMain->SetWindowName("My Dialog");

    fMain->MapWindow();
}

MyDialog::~MyDialog()
{
    delete fText;
    delete fLabel;
    delete fOk;
    delete fHor1;
    delete fGframe;

    delete fMain;
}

void MyDialog::CloseWindow()
{
    // Called when the window is closed via the window manager.

    delete this;
}

void MyDialog::DoSetlabel()
{
    printf("\nThe Enter key is pressed\n");

    fLabel->SetText(fText->GetBuffer()->GetString());
    fGframe->Layout();
}

void MyDialog::DoOK()
{
    TQObject::Disconnect(fText, "ReturnPressed()", this, "DoSetlabel()");
    printf("\nThe OK button is pressed\n");
    fMain->SendCloseMessage();
}

class MyMainFrame
{
    RQ_OBJECT("MyMainFrame")
private:
    TGMainFrame *fMain;

public:
    MyMainFrame(const TGWindow *p, UInt_t w, UInt_t h);
    virtual ~MyMainFrame();
    void FetchPyqtApp();
};

MyMainFrame::MyMainFrame(const TGWindow *p, UInt_t w, UInt_t h)
{
    // Create a main frame
    fMain = new TGMainFrame(p, w, h);

    // Create a horizontal frame widget with buttons
    TGHorizontalFrame *hframe = new TGHorizontalFrame(fMain, 200, 40);
    TGTextButton *fetch = new TGTextButton(hframe, "&Fetch");
    fetch->Connect("Clicked()", "MyMainFrame", this, "FetchPyqtApp()");
    hframe->AddFrame(fetch, new TGLayoutHints(kLHintsCenterX,
                                              5, 5, 3, 4));
    TGTextButton *exit = new TGTextButton(hframe, "&Exit",
                                          "gApplication->Terminate(0)");
    hframe->AddFrame(exit, new TGLayoutHints(kLHintsCenterX,
                                             5, 5, 3, 4));
    fMain->AddFrame(hframe, new TGLayoutHints(kLHintsCenterX,
                                              2, 2, 2, 2));

    // Set a name to the main frame
    fMain->SetWindowName("Simple Example");

    // Map all subwindows of main frame
    fMain->MapSubwindows();

    // Initialize the layout algorithm
    fMain->Resize(fMain->GetDefaultSize());

    // Map main frame
    fMain->MapWindow();
}

MyMainFrame::~MyMainFrame()
{
    // Clean up used widgets: frames, buttons, layout hints
    fMain->Cleanup();
    delete fMain;
}

void MyMainFrame::FetchPyqtApp()
{
    // Source:
    // https://root-forum.cern.ch/t/dialogue-box/1511/5
    // Testing a dialog box
    new MyDialog(gClient->GetRoot(), fMain, 400, 200);
    Printf("Create MyDialog window...");
}

void fetch_python_gui()
{
    new MyMainFrame(gClient->GetRoot(), 200, 200);
}
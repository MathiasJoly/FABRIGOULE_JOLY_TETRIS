#ifndef _LISEUSEFRAME_CPP_
#define _LISEUSEFRAME_CPP_

#include "LiseuseFrame.h"

BEGIN_EVENT_TABLE(LiseuseFrame, wxFrame)
	EVT_MENU(ID_OPEN, LiseuseFrame::OnOpen)
	EVT_MENU(ID_LOAD,  LiseuseFrame::OnOpenImage)
	EVT_MENU(ID_SAVE,  LiseuseFrame::OnSaveImage)
  EVT_MENU(ID_QUIT,  LiseuseFrame::OnQuit)
  EVT_MENU(ID_ABOUT, LiseuseFrame::OnAbout)
	EVT_MENU(ID_SYNC_SETTING, LiseuseFrame::OnSyncSetting)
	EVT_MENU(ID_ZOOM, LiseuseFrame::OnZoom)
	EVT_MENU(ID_DISPLAY, LiseuseFrame::OnDisplay)
	EVT_MENU(ID_BEST_SIZE,  LiseuseFrame::OnBestSize)
	EVT_CLOSE(LiseuseFrame::OnClose)
END_EVENT_TABLE()


LiseuseFrame::LiseuseFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
	wxMenu *menuFile = new wxMenu();
	menuFile->Append(ID_OPEN, _T("&Open Sheet\tCtrl-O"), _T("Browse folders"));

	wxMenu *OpenRecent = new wxMenu();
    	OpenRecent->Append(ID_OPEN, _T("Sheet1"));
    	OpenRecent->Append(ID_OPEN, _T("&Sheet2"));
	menuFile->AppendSubMenu(OpenRecent, "&Open Recent Sheet");
	OpenRecent->Append(ID_OPEN, "Sheet3");
    	menuFile->AppendSeparator();
	menuFile->Append(ID_LOAD, _T("&Open image..."));
	menuFile->Append(ID_SAVE, _T("&Save image as..."));
	menuFile->AppendSeparator();
    	menuFile->Append(ID_SYNC_SETTING, "&Sync Setting");
    	menuFile->AppendSeparator();
	menuFile->Append(ID_QUIT, _T("&Exit"));

	wxMenu *menuHelp = new wxMenu();
	menuHelp->Append(ID_ABOUT, _T("&About..."));

	wxMenu *menuView = new wxMenu();
	menuView->Append(ID_ZOOM, "&Zoom");
	menuView->AppendSeparator();
	menuView->Append(ID_DISPLAY, "&Display");
	menuView->Append(ID_BEST_SIZE, _T("&Best size"));

	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(menuFile, _T("&File"));
	menuBar->Append(menuHelp, _T("&Help"));
	menuBar->Append(menuView, _T("&View"));
	SetMenuBar( menuBar );
	CreateStatusBar();
	SetStatusText(_T("Welcome to wxWidgets"));

// create the panel that will manage the image
	panel = new LiseusePanel( this, -1, wxDefaultPosition, wxDefaultSize);
	imageLoaded = false ;
	pageWidth = 657;
	pageHeight = 850;
	Centre() ;
}

void LiseuseFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true) ;
}

void LiseuseFrame::OnClose(wxCloseEvent& event)
{
	delete panel ;
	event.Skip() ;
}

void LiseuseFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox( _T("Pour Annoter faites un clic droit"),
                  _T(APP_NAME), wxOK | wxICON_INFORMATION ) ;
}

void LiseuseFrame::OnOpenImage(wxCommandEvent& WXUNUSED(event) )
{
	wxBitmap bitmap;

	wxFileDialog openFileDialog(this,
		_("Open .jpg files"), "", "", "All files (*.*)|*.*",
		wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE);

		if (openFileDialog.ShowModal() == wxID_CANCEL)
			return; // the user changed idea

	openFileDialog.GetPaths(filesPaths);
	nbPages = filesPaths.GetCount();
	pagesVector.resize(nbPages);

	for(int i=0; i<nbPages; i++) {
		wxString filename = filesPaths.Item(i);

	//	wxString filename = wxFileSelector(_T("Select file"),_T(""),_T(""),_T(""), _T("All files (*.*)|*.*") );
		if ( !filename.empty() )
		{
			tempImage = panel->LoadImage(filename);
			pagesVector.at(i) = tempImage;
			//update GUI
			panel->SetScrollbars(1,1,nbPages*pageWidth,pageHeight,0,0);
			panel->SetSize(pageWidth, pageHeight);
			panel->GetParent()->SetClientSize(panel->GetSize());
			// update display
			panel->Refresh(false);

			imageLoaded = true;
		}
	}
	panel->LoadPagesVector(pagesVector);
}
void LiseuseFrame::OnSaveImage(wxCommandEvent & WXUNUSED(event))
{
//	char str[128] = "" ; // proposed file name

	if (!imageLoaded)
		return ;

	wxString filename = wxFileSelector(_T("Save image as"),_T(""),_T(""),_T("*.bmp"), _T("BMP files (*.bmp)|*.bmp|GIF files (*gif)|*.gif|JPEG files (*jpg)|*.jpg|PNG files (*png)|*.png|TIFF files (*tif)|*.tif|XPM files (*xpm)|*.xpm|All files (*.*)|*.*"), wxFD_SAVE );
	if ( !filename.empty() )
		panel->SaveImage(filename) ;
}

void LiseuseFrame::OnBestSize(wxCommandEvent& WXUNUSED(event))
{
    panel->BestSize() ;
}

void LiseuseFrame::OnOpen(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

void LiseuseFrame::OnSyncSetting(wxCommandEvent& event)
{
    wxLogMessage("You can set the tempo and the number of bar for each page !");
}

void LiseuseFrame::OnZoom(wxCommandEvent& event)
{
    wxLogMessage("You'll be able to change zoom");
}

void LiseuseFrame::OnDisplay(wxCommandEvent& event)
{
    wxLogMessage("You can set the number of page and how to scroll !");
}

#endif

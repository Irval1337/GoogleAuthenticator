#include <string>
#include <msclr\marshal_cppstd.h>
#include "user.hpp"
#include <sysinfoapi.h>

using namespace System::Net;
using namespace System::IO;
using namespace System::Text;

System::String^ sendRequest(System::String^ uri) {
	System::String^ resp;
	HttpWebRequest^ request = dynamic_cast<HttpWebRequest^>(WebRequest::Create(uri));
	request->MaximumAutomaticRedirections = 4;
	request->MaximumResponseHeadersLength = 4;
	request->Credentials = CredentialCache::DefaultCredentials;
	HttpWebResponse^ response = dynamic_cast<HttpWebResponse^>(request->GetResponse());
	Stream^ receiveStream = response->GetResponseStream();
	StreamReader^ readStream = gcnew StreamReader(receiveStream, Encoding::UTF8);
	resp = readStream->ReadToEnd();
	response->Close();
	readStream->Close();
	return resp;
}

namespace WinApp {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace std;
	using namespace System::Configuration;
	using namespace Newtonsoft::Json;
	using namespace Newtonsoft::Json::Converters;
	using namespace System::Threading;
	using namespace System::Threading::Tasks;
	using namespace System::Diagnostics;
	using namespace System::Reflection;
	using namespace Google::Authenticator;
	using namespace System::Collections::Generic;
	/// <summary>
	/// Сводка для Main
	/// </summary>
	public ref class Main : public System::Windows::Forms::Form {
	public:
		Main(void) {
			InitializeComponent();
			SetStyle(ControlStyles::SupportsTransparentBackColor, true);
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Main() {
			if (components)
				delete components;
		}

	public: System::String^ host = "https://yoursite.com/";
	private: System::String^ login = "";
	private: System::String^ password = "";
	private: bool remember = "";
	private: bool isAuthed = false;
	public: User^ user;
	private: int lastTab = 0;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::PictureBox^ close;

	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::TabControl^ tabControl1;
	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::Button^ continue_auth;
	private: System::Windows::Forms::Label^ register_label;


	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ password_auth;

	private: System::Windows::Forms::TextBox^ login_auth;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ forgot_password;

	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ info_auth;

	private: System::Windows::Forms::TabPage^ tabPage3;

	private: System::Windows::Forms::TabPage^ tabPage5;
	private: System::Windows::Forms::PictureBox^ back;
	private: System::Windows::Forms::Label^ info_recovery;
	private: System::Windows::Forms::Button^ continue_recovery;

	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::TextBox^ data_recovery;

	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ info_register;

	private: System::Windows::Forms::Panel^ panel7;
	private: System::Windows::Forms::Panel^ panel5;
	private: System::Windows::Forms::Panel^ panel6;
	private: System::Windows::Forms::Button^ continue_register;

	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ password_register2;

	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ password_register;
	private: System::Windows::Forms::TextBox^ login_register;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::TabPage^ tabPage6;
	private: System::Windows::Forms::Label^ info_email;
	private: System::Windows::Forms::Button^ continue_email;
	private: System::Windows::Forms::Panel^ panel8;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::TextBox^ email;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Panel^ authpanel_1;
	private: System::Windows::Forms::Label^ infolabel_1;
	private: System::Windows::Forms::Label^ codelabel_1;

	private: System::Windows::Forms::Label^ timelabel_1;

	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::PictureBox^ editbox_1;

	private: System::Windows::Forms::PictureBox^ deletebox_1;
	private: System::Windows::Forms::Panel^ elementpanel;
	private: System::Windows::Forms::Panel^ AddPanel;
	private: System::Windows::Forms::Label^ AddService;


	private: System::Windows::Forms::Panel^ panel9;
	private: System::Windows::Forms::Button^ EnterManually;

	private: System::Windows::Forms::Button^ ScanQR;
	private: System::Windows::Forms::Panel^ customPanel;

	private: System::Windows::Forms::Panel^ panel11;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ addUsername;
	private: System::Windows::Forms::TextBox^ addSite;

	private: System::Windows::Forms::Panel^ panel12;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::TextBox^ addSecret;

	private: System::Windows::Forms::Panel^ panel13;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::Button^ addCustomService;
	private: System::Windows::Forms::Panel^ panel10;
	private: System::Windows::Forms::Panel^ editPanel_1;
	private: System::Windows::Forms::TextBox^ editTextBox_1;
	private: System::Windows::Forms::Panel^ editLine_1;

	private: System::Windows::Forms::Label^ editLabel_1;
	private: System::Windows::Forms::PictureBox^ down_1;

	private: System::Windows::Forms::PictureBox^ up_1;
	private: System::Windows::Forms::PictureBox^ settings;

	private: System::Windows::Forms::TabPage^ tabPage7;
	private: System::Windows::Forms::RichTextBox^ servicesBox;
	private: System::Windows::Forms::TabPage^ tabPage8;
	private: System::Windows::Forms::RichTextBox^ dataBox;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Button^ loadDB;

	private: System::Windows::Forms::Button^ createDB;
	private: System::Windows::Forms::TabPage^ tabPage4;
	private: System::Windows::Forms::Button^ source;
	private: System::Windows::Forms::Button^ clearServices;
	private: System::Windows::Forms::Button^ services;
	private: System::Windows::Forms::Button^ sync;
	private: System::Windows::Forms::Button^ security;
	private: System::Windows::Forms::Button^ import;
	private: System::Windows::Forms::Button^ appinfo;

	private: System::ComponentModel::IContainer^ components;
	protected:
	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void) {
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Main::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->close = (gcnew System::Windows::Forms::PictureBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->info_auth = (gcnew System::Windows::Forms::Label());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->continue_auth = (gcnew System::Windows::Forms::Button());
			this->register_label = (gcnew System::Windows::Forms::Label());
			this->forgot_password = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->password_auth = (gcnew System::Windows::Forms::TextBox());
			this->login_auth = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->info_register = (gcnew System::Windows::Forms::Label());
			this->panel7 = (gcnew System::Windows::Forms::Panel());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->panel6 = (gcnew System::Windows::Forms::Panel());
			this->continue_register = (gcnew System::Windows::Forms::Button());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->password_register2 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->password_register = (gcnew System::Windows::Forms::TextBox());
			this->login_register = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->info_recovery = (gcnew System::Windows::Forms::Label());
			this->continue_recovery = (gcnew System::Windows::Forms::Button());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->data_recovery = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->source = (gcnew System::Windows::Forms::Button());
			this->clearServices = (gcnew System::Windows::Forms::Button());
			this->services = (gcnew System::Windows::Forms::Button());
			this->sync = (gcnew System::Windows::Forms::Button());
			this->security = (gcnew System::Windows::Forms::Button());
			this->import = (gcnew System::Windows::Forms::Button());
			this->appinfo = (gcnew System::Windows::Forms::Button());
			this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
			this->authpanel_1 = (gcnew System::Windows::Forms::Panel());
			this->down_1 = (gcnew System::Windows::Forms::PictureBox());
			this->editPanel_1 = (gcnew System::Windows::Forms::Panel());
			this->editTextBox_1 = (gcnew System::Windows::Forms::TextBox());
			this->editLine_1 = (gcnew System::Windows::Forms::Panel());
			this->editLabel_1 = (gcnew System::Windows::Forms::Label());
			this->up_1 = (gcnew System::Windows::Forms::PictureBox());
			this->editbox_1 = (gcnew System::Windows::Forms::PictureBox());
			this->deletebox_1 = (gcnew System::Windows::Forms::PictureBox());
			this->timelabel_1 = (gcnew System::Windows::Forms::Label());
			this->infolabel_1 = (gcnew System::Windows::Forms::Label());
			this->codelabel_1 = (gcnew System::Windows::Forms::Label());
			this->AddPanel = (gcnew System::Windows::Forms::Panel());
			this->customPanel = (gcnew System::Windows::Forms::Panel());
			this->addCustomService = (gcnew System::Windows::Forms::Button());
			this->addSecret = (gcnew System::Windows::Forms::TextBox());
			this->addSite = (gcnew System::Windows::Forms::TextBox());
			this->panel13 = (gcnew System::Windows::Forms::Panel());
			this->panel12 = (gcnew System::Windows::Forms::Panel());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->addUsername = (gcnew System::Windows::Forms::TextBox());
			this->panel11 = (gcnew System::Windows::Forms::Panel());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->EnterManually = (gcnew System::Windows::Forms::Button());
			this->ScanQR = (gcnew System::Windows::Forms::Button());
			this->AddService = (gcnew System::Windows::Forms::Label());
			this->elementpanel = (gcnew System::Windows::Forms::Panel());
			this->tabPage6 = (gcnew System::Windows::Forms::TabPage());
			this->info_email = (gcnew System::Windows::Forms::Label());
			this->continue_email = (gcnew System::Windows::Forms::Button());
			this->panel8 = (gcnew System::Windows::Forms::Panel());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->email = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->tabPage7 = (gcnew System::Windows::Forms::TabPage());
			this->servicesBox = (gcnew System::Windows::Forms::RichTextBox());
			this->tabPage8 = (gcnew System::Windows::Forms::TabPage());
			this->dataBox = (gcnew System::Windows::Forms::RichTextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->loadDB = (gcnew System::Windows::Forms::Button());
			this->createDB = (gcnew System::Windows::Forms::Button());
			this->panel9 = (gcnew System::Windows::Forms::Panel());
			this->back = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel10 = (gcnew System::Windows::Forms::Panel());
			this->settings = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->close))->BeginInit();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->tabPage4->SuspendLayout();
			this->tabPage5->SuspendLayout();
			this->authpanel_1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->down_1))->BeginInit();
			this->editPanel_1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->up_1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->editbox_1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->deletebox_1))->BeginInit();
			this->AddPanel->SuspendLayout();
			this->customPanel->SuspendLayout();
			this->tabPage6->SuspendLayout();
			this->tabPage7->SuspendLayout();
			this->tabPage8->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->back))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->settings))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(86, 8);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(150, 16);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Google Authenticator";
			// 
			// close
			// 
			this->close->Cursor = System::Windows::Forms::Cursors::Hand;
			this->close->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"close.Image")));
			this->close->Location = System::Drawing::Point(298, 6);
			this->close->Name = L"close";
			this->close->Size = System::Drawing::Size(20, 20);
			this->close->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->close->TabIndex = 3;
			this->close->TabStop = false;
			this->close->Click += gcnew System::EventHandler(this, &Main::exit_Click);
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(57)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(57)));
			this->panel2->Location = System::Drawing::Point(0, 30);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(326, 4);
			this->panel2->TabIndex = 4;
			// 
			// tabControl1
			// 
			this->tabControl1->Alignment = System::Windows::Forms::TabAlignment::Bottom;
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Controls->Add(this->tabPage5);
			this->tabControl1->Controls->Add(this->tabPage6);
			this->tabControl1->Controls->Add(this->tabPage7);
			this->tabControl1->Controls->Add(this->tabPage8);
			this->tabControl1->Location = System::Drawing::Point(-4, 30);
			this->tabControl1->Multiline = true;
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(335, 399);
			this->tabControl1->TabIndex = 5;
			this->tabControl1->SelectedIndexChanged += gcnew System::EventHandler(this, &Main::tabControl1_SelectedIndexChanged);
			// 
			// tabPage1
			// 
			this->tabPage1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->tabPage1->Controls->Add(this->info_auth);
			this->tabPage1->Controls->Add(this->panel3);
			this->tabPage1->Controls->Add(this->panel1);
			this->tabPage1->Controls->Add(this->continue_auth);
			this->tabPage1->Controls->Add(this->register_label);
			this->tabPage1->Controls->Add(this->forgot_password);
			this->tabPage1->Controls->Add(this->label5);
			this->tabPage1->Controls->Add(this->label4);
			this->tabPage1->Controls->Add(this->label3);
			this->tabPage1->Controls->Add(this->password_auth);
			this->tabPage1->Controls->Add(this->login_auth);
			this->tabPage1->Controls->Add(this->label2);
			this->tabPage1->Location = System::Drawing::Point(4, 4);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(327, 355);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Login";
			// 
			// info_auth
			// 
			this->info_auth->Font = (gcnew System::Drawing::Font(L"Century Gothic", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->info_auth->ForeColor = System::Drawing::Color::White;
			this->info_auth->Location = System::Drawing::Point(0, 250);
			this->info_auth->Name = L"info_auth";
			this->info_auth->Size = System::Drawing::Size(326, 13);
			this->info_auth->TabIndex = 4;
			this->info_auth->Text = L"label8";
			this->info_auth->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->info_auth->Visible = false;
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::Color::White;
			this->panel3->Location = System::Drawing::Point(42, 209);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(239, 1);
			this->panel3->TabIndex = 3;
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::White;
			this->panel1->Location = System::Drawing::Point(42, 146);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(239, 1);
			this->panel1->TabIndex = 3;
			// 
			// continue_auth
			// 
			this->continue_auth->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(29)), static_cast<System::Int32>(static_cast<System::Byte>(137)),
				static_cast<System::Int32>(static_cast<System::Byte>(174)));
			this->continue_auth->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(29)),
				static_cast<System::Int32>(static_cast<System::Byte>(137)), static_cast<System::Int32>(static_cast<System::Byte>(174)));
			this->continue_auth->FlatAppearance->BorderSize = 0;
			this->continue_auth->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(59)),
				static_cast<System::Int32>(static_cast<System::Byte>(167)), static_cast<System::Int32>(static_cast<System::Byte>(204)));
			this->continue_auth->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)),
				static_cast<System::Int32>(static_cast<System::Byte>(152)), static_cast<System::Int32>(static_cast<System::Byte>(189)));
			this->continue_auth->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->continue_auth->Font = (gcnew System::Drawing::Font(L"Century Gothic", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->continue_auth->ForeColor = System::Drawing::Color::White;
			this->continue_auth->Location = System::Drawing::Point(72, 269);
			this->continue_auth->Name = L"continue_auth";
			this->continue_auth->Size = System::Drawing::Size(178, 31);
			this->continue_auth->TabIndex = 2;
			this->continue_auth->TabStop = false;
			this->continue_auth->Text = L"Продолжить";
			this->continue_auth->UseVisualStyleBackColor = false;
			this->continue_auth->Click += gcnew System::EventHandler(this, &Main::button1_Click);
			// 
			// register_label
			// 
			this->register_label->AutoSize = true;
			this->register_label->Cursor = System::Windows::Forms::Cursors::Hand;
			this->register_label->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9));
			this->register_label->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(59)), static_cast<System::Int32>(static_cast<System::Byte>(167)),
				static_cast<System::Int32>(static_cast<System::Byte>(204)));
			this->register_label->Location = System::Drawing::Point(143, 361);
			this->register_label->Name = L"register_label";
			this->register_label->Size = System::Drawing::Size(125, 15);
			this->register_label->TabIndex = 0;
			this->register_label->Text = L"Зарегистрируйтесь";
			this->register_label->Click += gcnew System::EventHandler(this, &Main::label6_Click);
			// 
			// forgot_password
			// 
			this->forgot_password->AutoSize = true;
			this->forgot_password->Cursor = System::Windows::Forms::Cursors::Hand;
			this->forgot_password->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9));
			this->forgot_password->ForeColor = System::Drawing::Color::White;
			this->forgot_password->Location = System::Drawing::Point(108, 337);
			this->forgot_password->Name = L"forgot_password";
			this->forgot_password->Size = System::Drawing::Size(104, 15);
			this->forgot_password->TabIndex = 0;
			this->forgot_password->Text = L"Забыли пароль\?";
			this->forgot_password->Click += gcnew System::EventHandler(this, &Main::label7_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9));
			this->label5->ForeColor = System::Drawing::Color::White;
			this->label5->Location = System::Drawing::Point(55, 361);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(92, 15);
			this->label5->TabIndex = 0;
			this->label5->Text = L"Нет аккаунта\?";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Century Gothic", 8));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(39, 216);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(49, 13);
			this->label4->TabIndex = 0;
			this->label4->Text = L"Пароль";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Century Gothic", 8));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(39, 153);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(73, 13);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Логин/email";
			// 
			// password_auth
			// 
			this->password_auth->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->password_auth->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->password_auth->Font = (gcnew System::Drawing::Font(L"Century Gothic", 11));
			this->password_auth->ForeColor = System::Drawing::Color::White;
			this->password_auth->Location = System::Drawing::Point(42, 188);
			this->password_auth->Name = L"password_auth";
			this->password_auth->Size = System::Drawing::Size(239, 18);
			this->password_auth->TabIndex = 1;
			this->password_auth->TabStop = false;
			this->password_auth->UseSystemPasswordChar = true;
			// 
			// login_auth
			// 
			this->login_auth->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->login_auth->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->login_auth->Font = (gcnew System::Drawing::Font(L"Century Gothic", 11));
			this->login_auth->ForeColor = System::Drawing::Color::White;
			this->login_auth->Location = System::Drawing::Point(42, 125);
			this->login_auth->Name = L"login_auth";
			this->login_auth->Size = System::Drawing::Size(239, 18);
			this->login_auth->TabIndex = 1;
			this->login_auth->TabStop = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Century Gothic", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(85, 73);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(151, 22);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Авторизизация";
			// 
			// tabPage2
			// 
			this->tabPage2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->tabPage2->Controls->Add(this->info_register);
			this->tabPage2->Controls->Add(this->panel7);
			this->tabPage2->Controls->Add(this->panel5);
			this->tabPage2->Controls->Add(this->panel6);
			this->tabPage2->Controls->Add(this->continue_register);
			this->tabPage2->Controls->Add(this->label12);
			this->tabPage2->Controls->Add(this->label7);
			this->tabPage2->Controls->Add(this->password_register2);
			this->tabPage2->Controls->Add(this->label8);
			this->tabPage2->Controls->Add(this->password_register);
			this->tabPage2->Controls->Add(this->login_register);
			this->tabPage2->Controls->Add(this->label11);
			this->tabPage2->Location = System::Drawing::Point(4, 4);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(327, 393);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Registration";
			// 
			// info_register
			// 
			this->info_register->Font = (gcnew System::Drawing::Font(L"Century Gothic", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->info_register->ForeColor = System::Drawing::Color::White;
			this->info_register->Location = System::Drawing::Point(0, 288);
			this->info_register->Name = L"info_register";
			this->info_register->Size = System::Drawing::Size(326, 13);
			this->info_register->TabIndex = 13;
			this->info_register->Text = L"label8";
			this->info_register->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->info_register->Visible = false;
			// 
			// panel7
			// 
			this->panel7->BackColor = System::Drawing::Color::White;
			this->panel7->Location = System::Drawing::Point(42, 248);
			this->panel7->Name = L"panel7";
			this->panel7->Size = System::Drawing::Size(239, 1);
			this->panel7->TabIndex = 11;
			// 
			// panel5
			// 
			this->panel5->BackColor = System::Drawing::Color::White;
			this->panel5->Location = System::Drawing::Point(42, 185);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(239, 1);
			this->panel5->TabIndex = 11;
			// 
			// panel6
			// 
			this->panel6->BackColor = System::Drawing::Color::White;
			this->panel6->Location = System::Drawing::Point(42, 122);
			this->panel6->Name = L"panel6";
			this->panel6->Size = System::Drawing::Size(239, 1);
			this->panel6->TabIndex = 12;
			// 
			// continue_register
			// 
			this->continue_register->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(29)),
				static_cast<System::Int32>(static_cast<System::Byte>(137)), static_cast<System::Int32>(static_cast<System::Byte>(174)));
			this->continue_register->FlatAppearance->BorderSize = 0;
			this->continue_register->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->continue_register->Font = (gcnew System::Drawing::Font(L"Century Gothic", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->continue_register->ForeColor = System::Drawing::Color::White;
			this->continue_register->Location = System::Drawing::Point(71, 307);
			this->continue_register->Name = L"continue_register";
			this->continue_register->Size = System::Drawing::Size(178, 31);
			this->continue_register->TabIndex = 10;
			this->continue_register->TabStop = false;
			this->continue_register->Text = L"Продолжить";
			this->continue_register->UseVisualStyleBackColor = false;
			this->continue_register->Click += gcnew System::EventHandler(this, &Main::continue_register_Click);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Century Gothic", 8));
			this->label12->ForeColor = System::Drawing::Color::White;
			this->label12->Location = System::Drawing::Point(39, 253);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(108, 13);
			this->label12->TabIndex = 5;
			this->label12->Text = L"Повторите пароль";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Century Gothic", 8));
			this->label7->ForeColor = System::Drawing::Color::White;
			this->label7->Location = System::Drawing::Point(39, 190);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(49, 13);
			this->label7->TabIndex = 5;
			this->label7->Text = L"Пароль";
			// 
			// password_register2
			// 
			this->password_register2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->password_register2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->password_register2->Font = (gcnew System::Drawing::Font(L"Century Gothic", 11));
			this->password_register2->ForeColor = System::Drawing::Color::White;
			this->password_register2->Location = System::Drawing::Point(42, 226);
			this->password_register2->Name = L"password_register2";
			this->password_register2->Size = System::Drawing::Size(239, 18);
			this->password_register2->TabIndex = 8;
			this->password_register2->TabStop = false;
			this->password_register2->UseSystemPasswordChar = true;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Century Gothic", 8));
			this->label8->ForeColor = System::Drawing::Color::White;
			this->label8->Location = System::Drawing::Point(39, 127);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(39, 13);
			this->label8->TabIndex = 6;
			this->label8->Text = L"Логин";
			// 
			// password_register
			// 
			this->password_register->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->password_register->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->password_register->Font = (gcnew System::Drawing::Font(L"Century Gothic", 11));
			this->password_register->ForeColor = System::Drawing::Color::White;
			this->password_register->Location = System::Drawing::Point(42, 163);
			this->password_register->Name = L"password_register";
			this->password_register->Size = System::Drawing::Size(239, 18);
			this->password_register->TabIndex = 8;
			this->password_register->TabStop = false;
			this->password_register->UseSystemPasswordChar = true;
			// 
			// login_register
			// 
			this->login_register->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->login_register->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->login_register->Font = (gcnew System::Drawing::Font(L"Century Gothic", 11));
			this->login_register->ForeColor = System::Drawing::Color::White;
			this->login_register->Location = System::Drawing::Point(42, 100);
			this->login_register->Name = L"login_register";
			this->login_register->Size = System::Drawing::Size(239, 18);
			this->login_register->TabIndex = 9;
			this->login_register->TabStop = false;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Century Gothic", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label11->ForeColor = System::Drawing::Color::White;
			this->label11->Location = System::Drawing::Point(97, 49);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(129, 22);
			this->label11->TabIndex = 7;
			this->label11->Text = L"Регистрация";
			// 
			// tabPage3
			// 
			this->tabPage3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->tabPage3->Controls->Add(this->info_recovery);
			this->tabPage3->Controls->Add(this->continue_recovery);
			this->tabPage3->Controls->Add(this->panel4);
			this->tabPage3->Controls->Add(this->label9);
			this->tabPage3->Controls->Add(this->data_recovery);
			this->tabPage3->Controls->Add(this->label10);
			this->tabPage3->Location = System::Drawing::Point(4, 4);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(327, 393);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Password recovery";
			// 
			// info_recovery
			// 
			this->info_recovery->Font = (gcnew System::Drawing::Font(L"Century Gothic", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->info_recovery->ForeColor = System::Drawing::Color::White;
			this->info_recovery->Location = System::Drawing::Point(0, 242);
			this->info_recovery->Name = L"info_recovery";
			this->info_recovery->Size = System::Drawing::Size(326, 13);
			this->info_recovery->TabIndex = 9;
			this->info_recovery->Text = L"label11";
			this->info_recovery->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->info_recovery->Visible = false;
			// 
			// continue_recovery
			// 
			this->continue_recovery->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(29)),
				static_cast<System::Int32>(static_cast<System::Byte>(137)), static_cast<System::Int32>(static_cast<System::Byte>(174)));
			this->continue_recovery->FlatAppearance->BorderSize = 0;
			this->continue_recovery->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->continue_recovery->Font = (gcnew System::Drawing::Font(L"Century Gothic", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->continue_recovery->ForeColor = System::Drawing::Color::White;
			this->continue_recovery->Location = System::Drawing::Point(71, 261);
			this->continue_recovery->Name = L"continue_recovery";
			this->continue_recovery->Size = System::Drawing::Size(178, 31);
			this->continue_recovery->TabIndex = 8;
			this->continue_recovery->TabStop = false;
			this->continue_recovery->Text = L"Продолжить";
			this->continue_recovery->UseVisualStyleBackColor = false;
			this->continue_recovery->Click += gcnew System::EventHandler(this, &Main::continue_recovery_Click);
			// 
			// panel4
			// 
			this->panel4->BackColor = System::Drawing::Color::White;
			this->panel4->Location = System::Drawing::Point(42, 181);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(239, 1);
			this->panel4->TabIndex = 7;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Century Gothic", 8));
			this->label9->ForeColor = System::Drawing::Color::White;
			this->label9->Location = System::Drawing::Point(39, 188);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(73, 13);
			this->label9->TabIndex = 4;
			this->label9->Text = L"Логин/email";
			// 
			// data_recovery
			// 
			this->data_recovery->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->data_recovery->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->data_recovery->Font = (gcnew System::Drawing::Font(L"Century Gothic", 11));
			this->data_recovery->ForeColor = System::Drawing::Color::White;
			this->data_recovery->Location = System::Drawing::Point(42, 159);
			this->data_recovery->Name = L"data_recovery";
			this->data_recovery->Size = System::Drawing::Size(239, 18);
			this->data_recovery->TabIndex = 6;
			this->data_recovery->TabStop = false;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Century Gothic", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label10->ForeColor = System::Drawing::Color::White;
			this->label10->Location = System::Drawing::Point(78, 81);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(171, 44);
			this->label10->TabIndex = 5;
			this->label10->Text = L"Восстановление \r\nпароля";
			this->label10->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// tabPage4
			// 
			this->tabPage4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->tabPage4->Controls->Add(this->source);
			this->tabPage4->Controls->Add(this->clearServices);
			this->tabPage4->Controls->Add(this->services);
			this->tabPage4->Controls->Add(this->sync);
			this->tabPage4->Controls->Add(this->security);
			this->tabPage4->Controls->Add(this->import);
			this->tabPage4->Controls->Add(this->appinfo);
			this->tabPage4->Location = System::Drawing::Point(4, 4);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(327, 355);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"Settings";
			// 
			// source
			// 
			this->source->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->source->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->source->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->source->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)),
				static_cast<System::Int32>(static_cast<System::Byte>(75)), static_cast<System::Int32>(static_cast<System::Byte>(75)));
			this->source->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->source->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->source->ForeColor = System::Drawing::Color::White;
			this->source->Location = System::Drawing::Point(16, 257);
			this->source->Name = L"source";
			this->source->Size = System::Drawing::Size(293, 34);
			this->source->TabIndex = 0;
			this->source->TabStop = false;
			this->source->Text = L"Исходный код";
			this->source->UseVisualStyleBackColor = false;
			this->source->Click += gcnew System::EventHandler(this, &Main::source_Click);
			// 
			// clearServices
			// 
			this->clearServices->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->clearServices->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->clearServices->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->clearServices->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)),
				static_cast<System::Int32>(static_cast<System::Byte>(75)), static_cast<System::Int32>(static_cast<System::Byte>(75)));
			this->clearServices->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->clearServices->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->clearServices->ForeColor = System::Drawing::Color::White;
			this->clearServices->Location = System::Drawing::Point(16, 212);
			this->clearServices->Name = L"clearServices";
			this->clearServices->Size = System::Drawing::Size(293, 34);
			this->clearServices->TabIndex = 0;
			this->clearServices->TabStop = false;
			this->clearServices->Text = L"Очистить список сервисов";
			this->clearServices->UseVisualStyleBackColor = false;
			this->clearServices->Click += gcnew System::EventHandler(this, &Main::clearServices_Click);
			// 
			// services
			// 
			this->services->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->services->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->services->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->services->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)),
				static_cast<System::Int32>(static_cast<System::Byte>(75)), static_cast<System::Int32>(static_cast<System::Byte>(75)));
			this->services->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->services->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->services->ForeColor = System::Drawing::Color::White;
			this->services->Location = System::Drawing::Point(16, 177);
			this->services->Name = L"services";
			this->services->Size = System::Drawing::Size(293, 34);
			this->services->TabIndex = 0;
			this->services->TabStop = false;
			this->services->Text = L"Полная информация о сервисах";
			this->services->UseVisualStyleBackColor = false;
			this->services->Click += gcnew System::EventHandler(this, &Main::services_Click);
			// 
			// sync
			// 
			this->sync->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->sync->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->sync->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->sync->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)),
				static_cast<System::Int32>(static_cast<System::Byte>(75)), static_cast<System::Int32>(static_cast<System::Byte>(75)));
			this->sync->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->sync->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->sync->ForeColor = System::Drawing::Color::White;
			this->sync->Location = System::Drawing::Point(16, 132);
			this->sync->Name = L"sync";
			this->sync->Size = System::Drawing::Size(293, 34);
			this->sync->TabIndex = 0;
			this->sync->TabStop = false;
			this->sync->Text = L"Синхронизировать время с Google";
			this->sync->UseVisualStyleBackColor = false;
			this->sync->Click += gcnew System::EventHandler(this, &Main::sync_Click);
			// 
			// security
			// 
			this->security->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->security->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->security->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->security->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)),
				static_cast<System::Int32>(static_cast<System::Byte>(75)), static_cast<System::Int32>(static_cast<System::Byte>(75)));
			this->security->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->security->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->security->ForeColor = System::Drawing::Color::White;
			this->security->Location = System::Drawing::Point(16, 97);
			this->security->Name = L"security";
			this->security->Size = System::Drawing::Size(293, 34);
			this->security->TabIndex = 0;
			this->security->TabStop = false;
			this->security->Text = L"Автосохранение данных: ВКЛ";
			this->security->UseVisualStyleBackColor = false;
			this->security->Click += gcnew System::EventHandler(this, &Main::security_Click);
			// 
			// import
			// 
			this->import->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->import->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->import->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->import->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)),
				static_cast<System::Int32>(static_cast<System::Byte>(75)), static_cast<System::Int32>(static_cast<System::Byte>(75)));
			this->import->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->import->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->import->ForeColor = System::Drawing::Color::White;
			this->import->Location = System::Drawing::Point(16, 62);
			this->import->Name = L"import";
			this->import->Size = System::Drawing::Size(293, 34);
			this->import->TabIndex = 0;
			this->import->TabStop = false;
			this->import->Text = L"Импорт / Экспорт данных";
			this->import->UseVisualStyleBackColor = false;
			this->import->Click += gcnew System::EventHandler(this, &Main::import_Click);
			// 
			// appinfo
			// 
			this->appinfo->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->appinfo->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->appinfo->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->appinfo->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)),
				static_cast<System::Int32>(static_cast<System::Byte>(75)), static_cast<System::Int32>(static_cast<System::Byte>(75)));
			this->appinfo->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->appinfo->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->appinfo->ForeColor = System::Drawing::Color::White;
			this->appinfo->Location = System::Drawing::Point(16, 17);
			this->appinfo->Name = L"appinfo";
			this->appinfo->Size = System::Drawing::Size(293, 34);
			this->appinfo->TabIndex = 0;
			this->appinfo->TabStop = false;
			this->appinfo->Text = L"Информация о приложении";
			this->appinfo->UseVisualStyleBackColor = false;
			this->appinfo->Click += gcnew System::EventHandler(this, &Main::appinfo_Click);
			// 
			// tabPage5
			// 
			this->tabPage5->AutoScroll = true;
			this->tabPage5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->tabPage5->Controls->Add(this->authpanel_1);
			this->tabPage5->Controls->Add(this->AddPanel);
			this->tabPage5->Controls->Add(this->elementpanel);
			this->tabPage5->Location = System::Drawing::Point(4, 4);
			this->tabPage5->Name = L"tabPage5";
			this->tabPage5->Size = System::Drawing::Size(327, 393);
			this->tabPage5->TabIndex = 4;
			this->tabPage5->Text = L"Main";
			// 
			// authpanel_1
			// 
			this->authpanel_1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->authpanel_1->Controls->Add(this->down_1);
			this->authpanel_1->Controls->Add(this->editPanel_1);
			this->authpanel_1->Controls->Add(this->up_1);
			this->authpanel_1->Controls->Add(this->editbox_1);
			this->authpanel_1->Controls->Add(this->deletebox_1);
			this->authpanel_1->Controls->Add(this->timelabel_1);
			this->authpanel_1->Controls->Add(this->infolabel_1);
			this->authpanel_1->Controls->Add(this->codelabel_1);
			this->authpanel_1->Location = System::Drawing::Point(16, 20);
			this->authpanel_1->Name = L"authpanel_1";
			this->authpanel_1->Size = System::Drawing::Size(293, 84);
			this->authpanel_1->TabIndex = 0;
			// 
			// down_1
			// 
			this->down_1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->down_1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"down_1.Image")));
			this->down_1->Location = System::Drawing::Point(268, 32);
			this->down_1->Name = L"down_1";
			this->down_1->Size = System::Drawing::Size(13, 13);
			this->down_1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->down_1->TabIndex = 4;
			this->down_1->TabStop = false;
			this->down_1->Click += gcnew System::EventHandler(this, &Main::down_Click);
			// 
			// editPanel_1
			// 
			this->editPanel_1->Controls->Add(this->editTextBox_1);
			this->editPanel_1->Controls->Add(this->editLine_1);
			this->editPanel_1->Controls->Add(this->editLabel_1);
			this->editPanel_1->Location = System::Drawing::Point(13, 49);
			this->editPanel_1->Name = L"editPanel_1";
			this->editPanel_1->Size = System::Drawing::Size(229, 26);
			this->editPanel_1->TabIndex = 3;
			this->editPanel_1->Visible = false;
			// 
			// editTextBox_1
			// 
			this->editTextBox_1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->editTextBox_1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->editTextBox_1->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9));
			this->editTextBox_1->ForeColor = System::Drawing::Color::White;
			this->editTextBox_1->Location = System::Drawing::Point(79, 7);
			this->editTextBox_1->Name = L"editTextBox_1";
			this->editTextBox_1->Size = System::Drawing::Size(130, 15);
			this->editTextBox_1->TabIndex = 11;
			this->editTextBox_1->TabStop = false;
			this->editTextBox_1->Text = L"Irval1337";
			// 
			// editLine_1
			// 
			this->editLine_1->BackColor = System::Drawing::Color::White;
			this->editLine_1->Location = System::Drawing::Point(79, 25);
			this->editLine_1->Name = L"editLine_1";
			this->editLine_1->Size = System::Drawing::Size(130, 1);
			this->editLine_1->TabIndex = 10;
			// 
			// editLabel_1
			// 
			this->editLabel_1->AutoSize = true;
			this->editLabel_1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->editLabel_1->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->editLabel_1->ForeColor = System::Drawing::Color::White;
			this->editLabel_1->Location = System::Drawing::Point(-4, 7);
			this->editLabel_1->Name = L"editLabel_1";
			this->editLabel_1->Size = System::Drawing::Size(82, 15);
			this->editLabel_1->TabIndex = 0;
			this->editLabel_1->Text = L"Новый логин:";
			this->editLabel_1->Click += gcnew System::EventHandler(this, &Main::AddService_Click);
			// 
			// up_1
			// 
			this->up_1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->up_1->Enabled = false;
			this->up_1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"up_1.Image")));
			this->up_1->Location = System::Drawing::Point(255, 35);
			this->up_1->Name = L"up_1";
			this->up_1->Size = System::Drawing::Size(13, 13);
			this->up_1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->up_1->TabIndex = 4;
			this->up_1->TabStop = false;
			this->up_1->Click += gcnew System::EventHandler(this, &Main::up_Click);
			// 
			// editbox_1
			// 
			this->editbox_1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->editbox_1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"editbox_1.Image")));
			this->editbox_1->Location = System::Drawing::Point(248, 57);
			this->editbox_1->Name = L"editbox_1";
			this->editbox_1->Size = System::Drawing::Size(18, 18);
			this->editbox_1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->editbox_1->TabIndex = 2;
			this->editbox_1->TabStop = false;
			this->editbox_1->Tag = L"0";
			this->editbox_1->Click += gcnew System::EventHandler(this, &Main::editbox_Click);
			// 
			// deletebox_1
			// 
			this->deletebox_1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->deletebox_1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"deletebox_1.Image")));
			this->deletebox_1->Location = System::Drawing::Point(269, 57);
			this->deletebox_1->Name = L"deletebox_1";
			this->deletebox_1->Size = System::Drawing::Size(18, 18);
			this->deletebox_1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->deletebox_1->TabIndex = 2;
			this->deletebox_1->TabStop = false;
			this->deletebox_1->Click += gcnew System::EventHandler(this, &Main::deletebox_Click);
			// 
			// timelabel_1
			// 
			this->timelabel_1->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->timelabel_1->ForeColor = System::Drawing::Color::White;
			this->timelabel_1->Location = System::Drawing::Point(233, 7);
			this->timelabel_1->Name = L"timelabel_1";
			this->timelabel_1->Size = System::Drawing::Size(54, 15);
			this->timelabel_1->TabIndex = 1;
			this->timelabel_1->Text = L"21 сек.";
			this->timelabel_1->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// infolabel_1
			// 
			this->infolabel_1->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->infolabel_1->ForeColor = System::Drawing::Color::White;
			this->infolabel_1->Location = System::Drawing::Point(10, 56);
			this->infolabel_1->Name = L"infolabel_1";
			this->infolabel_1->Size = System::Drawing::Size(220, 15);
			this->infolabel_1->TabIndex = 1;
			this->infolabel_1->Text = L"DataStock.biz (Irval)";
			// 
			// codelabel_1
			// 
			this->codelabel_1->AutoSize = true;
			this->codelabel_1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->codelabel_1->Font = (gcnew System::Drawing::Font(L"Century Gothic", 21.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->codelabel_1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(49)), static_cast<System::Int32>(static_cast<System::Byte>(157)),
				static_cast<System::Int32>(static_cast<System::Byte>(194)));
			this->codelabel_1->Location = System::Drawing::Point(5, 12);
			this->codelabel_1->Name = L"codelabel_1";
			this->codelabel_1->Size = System::Drawing::Size(111, 34);
			this->codelabel_1->TabIndex = 0;
			this->codelabel_1->Text = L"987123";
			this->codelabel_1->DoubleClick += gcnew System::EventHandler(this, &Main::CopyCode_Click);
			// 
			// AddPanel
			// 
			this->AddPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->AddPanel->Controls->Add(this->customPanel);
			this->AddPanel->Controls->Add(this->EnterManually);
			this->AddPanel->Controls->Add(this->ScanQR);
			this->AddPanel->Controls->Add(this->AddService);
			this->AddPanel->Location = System::Drawing::Point(16, 122);
			this->AddPanel->Name = L"AddPanel";
			this->AddPanel->Size = System::Drawing::Size(293, 28);
			this->AddPanel->TabIndex = 0;
			// 
			// customPanel
			// 
			this->customPanel->Controls->Add(this->addCustomService);
			this->customPanel->Controls->Add(this->addSecret);
			this->customPanel->Controls->Add(this->addSite);
			this->customPanel->Controls->Add(this->panel13);
			this->customPanel->Controls->Add(this->panel12);
			this->customPanel->Controls->Add(this->label16);
			this->customPanel->Controls->Add(this->label15);
			this->customPanel->Controls->Add(this->addUsername);
			this->customPanel->Controls->Add(this->panel11);
			this->customPanel->Controls->Add(this->label6);
			this->customPanel->Location = System::Drawing::Point(11, 30);
			this->customPanel->Name = L"customPanel";
			this->customPanel->Size = System::Drawing::Size(271, 131);
			this->customPanel->TabIndex = 4;
			this->customPanel->Visible = false;
			// 
			// addCustomService
			// 
			this->addCustomService->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(29)), static_cast<System::Int32>(static_cast<System::Byte>(137)),
				static_cast<System::Int32>(static_cast<System::Byte>(174)));
			this->addCustomService->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(29)),
				static_cast<System::Int32>(static_cast<System::Byte>(137)), static_cast<System::Int32>(static_cast<System::Byte>(174)));
			this->addCustomService->FlatAppearance->BorderSize = 0;
			this->addCustomService->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(59)),
				static_cast<System::Int32>(static_cast<System::Byte>(167)), static_cast<System::Int32>(static_cast<System::Byte>(204)));
			this->addCustomService->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)),
				static_cast<System::Int32>(static_cast<System::Byte>(152)), static_cast<System::Int32>(static_cast<System::Byte>(189)));
			this->addCustomService->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->addCustomService->Font = (gcnew System::Drawing::Font(L"Century Gothic", 8));
			this->addCustomService->ForeColor = System::Drawing::Color::White;
			this->addCustomService->Location = System::Drawing::Point(69, 100);
			this->addCustomService->Name = L"addCustomService";
			this->addCustomService->Size = System::Drawing::Size(130, 25);
			this->addCustomService->TabIndex = 10;
			this->addCustomService->TabStop = false;
			this->addCustomService->Text = L"Добавить";
			this->addCustomService->UseVisualStyleBackColor = false;
			this->addCustomService->Click += gcnew System::EventHandler(this, &Main::addCustomService_Click);
			// 
			// addSecret
			// 
			this->addSecret->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->addSecret->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->addSecret->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9));
			this->addSecret->ForeColor = System::Drawing::Color::White;
			this->addSecret->Location = System::Drawing::Point(6, 52);
			this->addSecret->Name = L"addSecret";
			this->addSecret->Size = System::Drawing::Size(259, 15);
			this->addSecret->TabIndex = 9;
			this->addSecret->TabStop = false;
			// 
			// addSite
			// 
			this->addSite->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->addSite->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->addSite->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9));
			this->addSite->ForeColor = System::Drawing::Color::White;
			this->addSite->Location = System::Drawing::Point(144, 2);
			this->addSite->Name = L"addSite";
			this->addSite->Size = System::Drawing::Size(121, 15);
			this->addSite->TabIndex = 9;
			this->addSite->TabStop = false;
			// 
			// panel13
			// 
			this->panel13->BackColor = System::Drawing::Color::White;
			this->panel13->Location = System::Drawing::Point(6, 70);
			this->panel13->Name = L"panel13";
			this->panel13->Size = System::Drawing::Size(259, 1);
			this->panel13->TabIndex = 8;
			// 
			// panel12
			// 
			this->panel12->BackColor = System::Drawing::Color::White;
			this->panel12->Location = System::Drawing::Point(144, 20);
			this->panel12->Name = L"panel12";
			this->panel12->Size = System::Drawing::Size(121, 1);
			this->panel12->TabIndex = 8;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Century Gothic", 8));
			this->label16->ForeColor = System::Drawing::Color::White;
			this->label16->Location = System::Drawing::Point(3, 77);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(98, 13);
			this->label16->TabIndex = 7;
			this->label16->Text = L"Секретный ключ";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Century Gothic", 8));
			this->label15->ForeColor = System::Drawing::Color::White;
			this->label15->Location = System::Drawing::Point(141, 27);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(50, 13);
			this->label15->TabIndex = 7;
			this->label15->Text = L"Сервис";
			// 
			// addUsername
			// 
			this->addUsername->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->addUsername->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->addUsername->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9));
			this->addUsername->ForeColor = System::Drawing::Color::White;
			this->addUsername->Location = System::Drawing::Point(6, 2);
			this->addUsername->Name = L"addUsername";
			this->addUsername->Size = System::Drawing::Size(121, 15);
			this->addUsername->TabIndex = 6;
			this->addUsername->TabStop = false;
			// 
			// panel11
			// 
			this->panel11->BackColor = System::Drawing::Color::White;
			this->panel11->Location = System::Drawing::Point(6, 20);
			this->panel11->Name = L"panel11";
			this->panel11->Size = System::Drawing::Size(121, 1);
			this->panel11->TabIndex = 5;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Century Gothic", 8));
			this->label6->ForeColor = System::Drawing::Color::White;
			this->label6->Location = System::Drawing::Point(3, 27);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(105, 13);
			this->label6->TabIndex = 4;
			this->label6->Text = L"Имя пользователя";
			// 
			// EnterManually
			// 
			this->EnterManually->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->EnterManually->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->EnterManually->FlatAppearance->BorderSize = 0;
			this->EnterManually->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)),
				static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(120)));
			this->EnterManually->FlatAppearance->MouseOverBackColor = System::Drawing::Color::DimGray;
			this->EnterManually->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->EnterManually->Font = (gcnew System::Drawing::Font(L"Century Gothic", 8));
			this->EnterManually->ForeColor = System::Drawing::Color::White;
			this->EnterManually->Location = System::Drawing::Point(152, 30);
			this->EnterManually->Name = L"EnterManually";
			this->EnterManually->Size = System::Drawing::Size(130, 25);
			this->EnterManually->TabIndex = 3;
			this->EnterManually->TabStop = false;
			this->EnterManually->Text = L"Ввести вручную";
			this->EnterManually->UseVisualStyleBackColor = false;
			this->EnterManually->Click += gcnew System::EventHandler(this, &Main::EnterManually_Click);
			// 
			// ScanQR
			// 
			this->ScanQR->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->ScanQR->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->ScanQR->FlatAppearance->BorderSize = 0;
			this->ScanQR->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)),
				static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(120)));
			this->ScanQR->FlatAppearance->MouseOverBackColor = System::Drawing::Color::DimGray;
			this->ScanQR->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ScanQR->Font = (gcnew System::Drawing::Font(L"Century Gothic", 8));
			this->ScanQR->ForeColor = System::Drawing::Color::White;
			this->ScanQR->Location = System::Drawing::Point(11, 30);
			this->ScanQR->Name = L"ScanQR";
			this->ScanQR->Size = System::Drawing::Size(130, 25);
			this->ScanQR->TabIndex = 3;
			this->ScanQR->TabStop = false;
			this->ScanQR->Text = L"Сканировать QR";
			this->ScanQR->UseVisualStyleBackColor = false;
			this->ScanQR->Click += gcnew System::EventHandler(this, &Main::ScanQR_Click);
			// 
			// AddService
			// 
			this->AddService->AutoSize = true;
			this->AddService->Cursor = System::Windows::Forms::Cursors::Hand;
			this->AddService->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->AddService->ForeColor = System::Drawing::Color::White;
			this->AddService->Location = System::Drawing::Point(71, 6);
			this->AddService->Name = L"AddService";
			this->AddService->Size = System::Drawing::Size(151, 15);
			this->AddService->TabIndex = 0;
			this->AddService->Text = L"Добавить новый сервис";
			this->AddService->Click += gcnew System::EventHandler(this, &Main::AddService_Click);
			// 
			// elementpanel
			// 
			this->elementpanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->elementpanel->Location = System::Drawing::Point(0, 0);
			this->elementpanel->Name = L"elementpanel";
			this->elementpanel->Size = System::Drawing::Size(327, 393);
			this->elementpanel->TabIndex = 1;
			// 
			// tabPage6
			// 
			this->tabPage6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->tabPage6->Controls->Add(this->info_email);
			this->tabPage6->Controls->Add(this->continue_email);
			this->tabPage6->Controls->Add(this->panel8);
			this->tabPage6->Controls->Add(this->label13);
			this->tabPage6->Controls->Add(this->email);
			this->tabPage6->Controls->Add(this->label14);
			this->tabPage6->Location = System::Drawing::Point(4, 4);
			this->tabPage6->Name = L"tabPage6";
			this->tabPage6->Padding = System::Windows::Forms::Padding(3);
			this->tabPage6->Size = System::Drawing::Size(327, 355);
			this->tabPage6->TabIndex = 5;
			this->tabPage6->Text = L"Add email";
			// 
			// info_email
			// 
			this->info_email->Font = (gcnew System::Drawing::Font(L"Century Gothic", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->info_email->ForeColor = System::Drawing::Color::White;
			this->info_email->Location = System::Drawing::Point(0, 243);
			this->info_email->Name = L"info_email";
			this->info_email->Size = System::Drawing::Size(326, 13);
			this->info_email->TabIndex = 15;
			this->info_email->Text = L"label11";
			this->info_email->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->info_email->Visible = false;
			// 
			// continue_email
			// 
			this->continue_email->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(29)), static_cast<System::Int32>(static_cast<System::Byte>(137)),
				static_cast<System::Int32>(static_cast<System::Byte>(174)));
			this->continue_email->FlatAppearance->BorderSize = 0;
			this->continue_email->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->continue_email->Font = (gcnew System::Drawing::Font(L"Century Gothic", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->continue_email->ForeColor = System::Drawing::Color::White;
			this->continue_email->Location = System::Drawing::Point(72, 262);
			this->continue_email->Name = L"continue_email";
			this->continue_email->Size = System::Drawing::Size(178, 31);
			this->continue_email->TabIndex = 14;
			this->continue_email->Text = L"Продолжить";
			this->continue_email->UseVisualStyleBackColor = false;
			this->continue_email->Click += gcnew System::EventHandler(this, &Main::continue_email_Click);
			// 
			// panel8
			// 
			this->panel8->BackColor = System::Drawing::Color::White;
			this->panel8->Location = System::Drawing::Point(42, 182);
			this->panel8->Name = L"panel8";
			this->panel8->Size = System::Drawing::Size(239, 1);
			this->panel8->TabIndex = 13;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Century Gothic", 8));
			this->label13->ForeColor = System::Drawing::Color::White;
			this->label13->Location = System::Drawing::Point(39, 189);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(35, 13);
			this->label13->TabIndex = 10;
			this->label13->Text = L"Email";
			// 
			// email
			// 
			this->email->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->email->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->email->Font = (gcnew System::Drawing::Font(L"Century Gothic", 11));
			this->email->ForeColor = System::Drawing::Color::White;
			this->email->Location = System::Drawing::Point(42, 160);
			this->email->Name = L"email";
			this->email->Size = System::Drawing::Size(239, 18);
			this->email->TabIndex = 12;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Century Gothic", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label14->ForeColor = System::Drawing::Color::White;
			this->label14->Location = System::Drawing::Point(80, 82);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(162, 44);
			this->label14->TabIndex = 11;
			this->label14->Text = L"Подтверждение\r\nEmail";
			this->label14->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// tabPage7
			// 
			this->tabPage7->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->tabPage7->Controls->Add(this->servicesBox);
			this->tabPage7->Location = System::Drawing::Point(4, 4);
			this->tabPage7->Name = L"tabPage7";
			this->tabPage7->Padding = System::Windows::Forms::Padding(3);
			this->tabPage7->Size = System::Drawing::Size(327, 355);
			this->tabPage7->TabIndex = 6;
			this->tabPage7->Text = L"Services";
			// 
			// servicesBox
			// 
			this->servicesBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->servicesBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->servicesBox->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->servicesBox->ForeColor = System::Drawing::Color::White;
			this->servicesBox->Location = System::Drawing::Point(16, 20);
			this->servicesBox->Name = L"servicesBox";
			this->servicesBox->ReadOnly = true;
			this->servicesBox->Size = System::Drawing::Size(293, 348);
			this->servicesBox->TabIndex = 0;
			this->servicesBox->TabStop = false;
			this->servicesBox->Text = L"";
			// 
			// tabPage8
			// 
			this->tabPage8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->tabPage8->Controls->Add(this->dataBox);
			this->tabPage8->Controls->Add(this->label17);
			this->tabPage8->Controls->Add(this->loadDB);
			this->tabPage8->Controls->Add(this->createDB);
			this->tabPage8->Location = System::Drawing::Point(4, 4);
			this->tabPage8->Name = L"tabPage8";
			this->tabPage8->Padding = System::Windows::Forms::Padding(3);
			this->tabPage8->Size = System::Drawing::Size(327, 355);
			this->tabPage8->TabIndex = 7;
			this->tabPage8->Text = L"Import";
			// 
			// dataBox
			// 
			this->dataBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->dataBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dataBox->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->dataBox->ForeColor = System::Drawing::Color::White;
			this->dataBox->Location = System::Drawing::Point(16, 134);
			this->dataBox->Name = L"dataBox";
			this->dataBox->ReadOnly = true;
			this->dataBox->Size = System::Drawing::Size(293, 233);
			this->dataBox->TabIndex = 3;
			this->dataBox->TabStop = false;
			this->dataBox->Text = L"";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label17->ForeColor = System::Drawing::Color::White;
			this->label17->Location = System::Drawing::Point(13, 116);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(110, 15);
			this->label17->TabIndex = 2;
			this->label17->Text = L"Текущие данные:";
			// 
			// loadDB
			// 
			this->loadDB->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->loadDB->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->loadDB->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->loadDB->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)),
				static_cast<System::Int32>(static_cast<System::Byte>(75)), static_cast<System::Int32>(static_cast<System::Byte>(75)));
			this->loadDB->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->loadDB->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->loadDB->ForeColor = System::Drawing::Color::White;
			this->loadDB->Location = System::Drawing::Point(16, 69);
			this->loadDB->Name = L"loadDB";
			this->loadDB->Size = System::Drawing::Size(293, 34);
			this->loadDB->TabIndex = 1;
			this->loadDB->TabStop = false;
			this->loadDB->Text = L"Загрузить настройки существующей";
			this->loadDB->UseVisualStyleBackColor = false;
			this->loadDB->Click += gcnew System::EventHandler(this, &Main::loadDB_Click);
			// 
			// createDB
			// 
			this->createDB->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->createDB->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->createDB->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->createDB->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)),
				static_cast<System::Int32>(static_cast<System::Byte>(75)), static_cast<System::Int32>(static_cast<System::Byte>(75)));
			this->createDB->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->createDB->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->createDB->ForeColor = System::Drawing::Color::White;
			this->createDB->Location = System::Drawing::Point(16, 17);
			this->createDB->Name = L"createDB";
			this->createDB->Size = System::Drawing::Size(293, 51);
			this->createDB->TabIndex = 1;
			this->createDB->TabStop = false;
			this->createDB->Text = L"Создать резервную копию настроек сервисов";
			this->createDB->UseVisualStyleBackColor = false;
			this->createDB->Click += gcnew System::EventHandler(this, &Main::createDB_Click);
			// 
			// panel9
			// 
			this->panel9->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->panel9->Location = System::Drawing::Point(309, 34);
			this->panel9->Name = L"panel9";
			this->panel9->Size = System::Drawing::Size(13, 395);
			this->panel9->TabIndex = 0;
			// 
			// back
			// 
			this->back->Cursor = System::Windows::Forms::Cursors::Hand;
			this->back->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"back.Image")));
			this->back->Location = System::Drawing::Point(7, 8);
			this->back->Name = L"back";
			this->back->Size = System::Drawing::Size(18, 18);
			this->back->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->back->TabIndex = 10;
			this->back->TabStop = false;
			this->back->Click += gcnew System::EventHandler(this, &Main::back_Click);
			// 
			// timer1
			// 
			this->timer1->Interval = 500;
			this->timer1->Tick += gcnew System::EventHandler(this, &Main::timer1_Tick);
			// 
			// panel10
			// 
			this->panel10->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(55)), static_cast<System::Int32>(static_cast<System::Byte>(55)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->panel10->Location = System::Drawing::Point(0, 32);
			this->panel10->Name = L"panel10";
			this->panel10->Size = System::Drawing::Size(326, 2);
			this->panel10->TabIndex = 4;
			// 
			// settings
			// 
			this->settings->Cursor = System::Windows::Forms::Cursors::Hand;
			this->settings->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"settings.Image")));
			this->settings->Location = System::Drawing::Point(30, 6);
			this->settings->Name = L"settings";
			this->settings->Size = System::Drawing::Size(20, 20);
			this->settings->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->settings->TabIndex = 10;
			this->settings->TabStop = false;
			this->settings->Click += gcnew System::EventHandler(this, &Main::settings_Click);
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->ClientSize = System::Drawing::Size(326, 426);
			this->Controls->Add(this->panel9);
			this->Controls->Add(this->settings);
			this->Controls->Add(this->back);
			this->Controls->Add(this->panel10);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->close);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Main";
			this->Text = L"Main";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Main::Main_FormClosed);
			this->Load += gcnew System::EventHandler(this, &Main::Main_Load);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Main::Main_MouseDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->close))->EndInit();
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			this->tabPage4->ResumeLayout(false);
			this->tabPage5->ResumeLayout(false);
			this->authpanel_1->ResumeLayout(false);
			this->authpanel_1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->down_1))->EndInit();
			this->editPanel_1->ResumeLayout(false);
			this->editPanel_1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->up_1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->editbox_1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->deletebox_1))->EndInit();
			this->AddPanel->ResumeLayout(false);
			this->AddPanel->PerformLayout();
			this->customPanel->ResumeLayout(false);
			this->customPanel->PerformLayout();
			this->tabPage6->ResumeLayout(false);
			this->tabPage6->PerformLayout();
			this->tabPage7->ResumeLayout(false);
			this->tabPage8->ResumeLayout(false);
			this->tabPage8->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->back))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->settings))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Main_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) { // Движение окна
		this->Capture = false;
		Message m = Message::Create(this->Handle, 0xa1, IntPtr(2), IntPtr::Zero);
		this->WndProc(m);
	}
	private: System::Void exit_Click(System::Object^ sender, System::EventArgs^ e) { // Выход
		Application::Exit();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) { // Авторизация
		if (login_auth->Text != "" && password_auth->Text != "") {
			try {
				auto response = sendRequest(host + "/User/login.php?login=" + login_auth->Text + "&password=" + password_auth->Text);
				if (response == "INCORRECT")
					info_auth->Text = "Неверный логин и/или пароль";
				else if (response == "ERROR")
					info_auth->Text = "Ошибка на стороне сервера";
				else {
					info_auth->Text = "Успешная авторизация";
					login = login_auth->Text;
					password = password_auth->Text;
					user = JsonConvert::DeserializeObject<User^>(response);
					tabControl1->SelectedIndex = 4;
				}
				isAuthed = true;
			} catch (int ex) {
				info_auth->Text = "Ошибка на стороне клиента";
			}
		} else if (login_auth->Text == password_auth->Text) {
			isAuthed = false;
			try {
				String^ dir = System::Environment::GetFolderPath(System::Environment::SpecialFolder::ApplicationData) + "\\GoogleAuthetificator";
				if (!Directory::Exists(dir)) {
					Directory::CreateDirectory(dir);
					File::WriteAllText(dir + "\\Data.json", "{\"Id\":\"0\",\"Username\":\"NOTAUTHED\",\"Email\":\"NOTAUTHED\",\"Password\":\"NOTAUTHED\",\"Applications\":[]}");
				}
				user = JsonConvert::DeserializeObject<User^>(File::ReadAllText(dir + "\\Data.json"));
				tabControl1->SelectedIndex = 4;
			} catch (int ex) {}
		} else
			info_auth->Text = "Ошибка заполнения полей";
		info_auth->Visible = true;
	}
	private: System::Void label6_Click(System::Object^ sender, System::EventArgs^ e) {
		tabControl1->SelectedIndex = 1;
	}
	private: System::Void label7_Click(System::Object^ sender, System::EventArgs^ e) {
		tabControl1->SelectedIndex = 2;
	}
	private: System::Void back_Click(System::Object^ sender, System::EventArgs^ e) { // Назад
		if (tabControl1->SelectedIndex == 3)
			tabControl1->SelectedIndex = lastTab;
		else if (tabControl1->SelectedIndex < 4)
			tabControl1->SelectedIndex = 0;
		else if (tabControl1->SelectedIndex == 4) {
			tabControl1->SelectedIndex = 0;
			login = "";
			password = "";
			user = nullptr;
		} else if (tabControl1->SelectedIndex > 4)
			tabControl1->SelectedIndex = 3;
	}
	private: System::Void continue_recovery_Click(System::Object^ sender, System::EventArgs^ e) { // Восстановление пароля
		if (data_recovery->Text != "") {
			if (label9->Text == "Логин/email") {
				try {
					auto data = sendRequest(host + "/User/Mail/check.php?login=" + data_recovery->Text);
					if (data == "YES") {
						if (info_recovery->Visible)
							info_recovery->Visible = false;
						label9->Text = "Новый пароль";
						login = data_recovery->Text;
						data_recovery->Text = "";
					} else if (data == "NO")
						info_recovery->Text = "Почта пользователя не подтверждена";
					else if (data == "INCORRECT")
						info_recovery->Text = "Пользователь не найден";
					else if (data == "ERROR")
						info_recovery->Text = "Ошибка на стороне сервера";
					else
						info_recovery->Text = "Неизвестная ошибка";
					if (!info_recovery->Visible && data != "YES")
						info_recovery->Visible = true;
				} catch (int ex) {
					info_recovery->Text = "Ошибка на стороне клиента";
					if (!info_recovery->Visible)
						info_recovery->Visible = true;
				}
			} else {
				try {
					auto data = sendRequest(host + "/User/Mail/sendReset.php?login=" + login + "&newPassword=" + data_recovery->Text);
					if (data == "OK") {
						info_recovery->Text = "Письмо с подтверждением успешно отправлено";
						login = "";
					} else if (data == "INCORRECT")
						info_recovery->Text = "Пользователь не найден";
					else if (data == "ERROR")
						info_recovery->Text = "Ошибка на стороне сервера";
					else if (data == "NO EMAIL")
						info_recovery->Text = "Почтовый адрес не найден";
					else
						info_recovery->Text = "Неизвестная ошибка";
				} catch (int ex) {
					info_recovery->Text = "Ошибка на стороне клиента";
				}
				info_recovery->Visible = true;
			}
		} else {
			info_auth->Text = "Ошибка заполнения полей";
			if (!info_recovery->Visible)
				info_recovery->Visible = true;
		}
	}
	private: System::Void Main_Load(System::Object^ sender, System::EventArgs^ e) { // Загрузка формы
		auto configFile = ConfigurationManager::OpenExeConfiguration(ConfigurationUserLevel::None);
		remember = configFile->AppSettings->Settings["remember"]->Value == "true";
		login = configFile->AppSettings->Settings["login"]->Value;
		password = configFile->AppSettings->Settings["password"]->Value; // Загрузка настроек программы
		if (login != "" && password != "" && remember && isAuthed) { // Проверка логина и пароля
			auto response = sendRequest(host + "/User/login.php?login=" + login + "&password=" + password);
			try {
				user = JsonConvert::DeserializeObject<User^>(response);
				tabControl1->SelectedIndex = 4;
			} catch (int ex) {}
		}
	}
	private: System::Void Main_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) { // Закрытие формы
		auto configFile = ConfigurationManager::OpenExeConfiguration(ConfigurationUserLevel::None);
		configFile->AppSettings->Settings["login"]->Value = login;
		configFile->AppSettings->Settings["password"]->Value = password;
		configFile->AppSettings->Settings["remember"]->Value = remember ? "true" : "false";
		configFile->Save(ConfigurationSaveMode::Modified); // Сохранение настроек
		if (!isAuthed)
			File::WriteAllText(System::Environment::GetFolderPath(System::Environment::SpecialFolder::ApplicationData) +
				"\\GoogleAuthetificator\\Data.json", JsonConvert::SerializeObject(user));
	}
	private: System::Void continue_register_Click(System::Object^ sender, System::EventArgs^ e) { // Регистрация
		if (login_register->Text != "" && password_register->Text != "" && password_register->Text == password_register2->Text) {
			try {
				auto response = sendRequest(host + "/User/register.php?login=" + login_register->Text + "&password=" + password_register->Text);
				if (response == "INCORRECT")
					info_register->Text = "Неверный формат данных";
				else if (response == "EXISTS")
					info_register->Text = "Указанный логин занят";
				else if (response == "ERROR")
					info_register->Text = "Ошибка на стороне сервера";
				else {
					login = login_register->Text;
					password = password_register->Text;
					user = JsonConvert::DeserializeObject<User^>(response);
					tabControl1->SelectedIndex = 5;
				}
				if (!info_register->Visible && tabControl1->SelectedIndex != 5)
					info_register->Visible = true;
			} catch (int ex) {
				info_register->Text = "Ошибка на стороне клиента";
			}
		} else {
			info_register->Text = "Ошибка заполнения полей";
			if (!info_register->Visible)
				info_register->Visible = true;
		}
	}
	private: System::Void continue_email_Click(System::Object^ sender, System::EventArgs^ e) { // Подтверждение почты
		if (login != "" && password != "" && email->Text != "") {
			try {
				if (continue_email->Text == "Продолжить") {
					auto response = sendRequest(host + "/User/Mail/sendLink.php?login=" + login + "&password=" + password + "&email=" + email->Text);
					if (response == "OK")
						continue_email->Text = "Проверить";
					else if (response == "INCORRECT")
						info_email->Text = "Неверный логин и/или пароль";
					else if (response == "EXISTS")
						info_email->Text = "Почтовый ящик уже привязан";
					else if (response == "ERROR")
						info_email->Text = "Ошибка на стороне сервера";
					else
						info_email->Text = "Неизвестная ошибка";
				} else {
					auto data = sendRequest(host + "/User/Mail/check.php?login=" + login);
					if (data == "YES")
						tabControl1->SelectedIndex = 4;
					else if (data == "NO")
						info_email->Text = "Почта пользователя не подтверждена";
					else if (data == "INCORRECT")
						info_email->Text = "Пользователь не найден";
					else if (data == "ERROR")
						info_email->Text = "Ошибка на стороне сервера";
					else
						info_email->Text = "Неизвестная ошибка";
				}
			} catch (int ex) {
				info_email->Text = "Ошибка на стороне клиента";
			}
			if (info_email->Text != "label11")
				info_email->Visible = true;

		} else 
			info_email->Text = "Ошибка заполнения полей";
		if (!info_email->Visible)
			info_email->Visible = true;
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		auto datetime = DateTime::UtcNow;
		auto seconds_remain = 30 - (datetime.Second + 1) % 30;
		if (authpanel_1->Visible) {
			timelabel_1->Text = seconds_remain.ToString() + " сек.";
		}
		for each (Control^ panel in elementpanel->Controls)
		{
			if (panel->GetType() == (gcnew Panel)->GetType() && panel->Visible && panel->Name->Contains("_") && !panel->Name->StartsWith("editPanel_")) {
				String^ number = panel->Name->Split('_')[1];
				try {
					panel->Controls["timelabel_" + number]->Text = seconds_remain.ToString() + " сек.";
				} catch (int ex) {}
			}
		}
		ThreadStart^ thread_start = gcnew ThreadStart(this, &Main::Updater);
		Thread^ thread = gcnew Thread(thread_start);
		thread->Start();
	}
	private: void changeLabel(String^ text) {
		auto data = text->Split('|');
		if (data[0] != "authpanel_1")
			this->elementpanel->Controls[data[0]]->Controls[data[1]]->Text = data[2];
		else
			authpanel_1->Controls[data[1]]->Text = data[2];
	}
	private: void Updater(void) {
		if (authpanel_1->Visible) {
			try {
				if (isAuthed) {
					auto response = sendRequest(host + "/Auth/getCode.php?secretKey=" + authpanel_1->Controls["codelabel_1"]->Tag);
					App^ app = JsonConvert::DeserializeObject<App^>(response);
					if (app->Code != codelabel_1->Text)
						this->Invoke(gcnew Action<String^>(this, &Main::changeLabel), "authpanel_1|codelabel_1|" + app->Code);
				} else {
					TwoFactorAuthenticator^ tfa = gcnew TwoFactorAuthenticator();
					auto code = tfa->GetCurrentPIN(codelabel_1->Tag->ToString());
					if (code != codelabel_1->Text)
						this->Invoke(gcnew Action<String^>(this, &Main::changeLabel), "authpanel_1|codelabel_1|" + code);
				}
			} catch (int ex) {
				authpanel_1->Controls["codelabel_1"]->Text = "??????";
				this->Invoke(gcnew Action<String^>(this, &Main::changeLabel), "authpanel_1|codelabel_1|" + "|??????");
			}
		}
		for each (Control ^ panel in elementpanel->Controls)
		{
			if (panel->GetType() == (gcnew Panel)->GetType() && panel->Visible && panel->Name->Contains("_") && !panel->Name->StartsWith("editPanel_")) {
				String^ number = panel->Name->Split('_')[1];
				try {
					if (isAuthed) {
						auto response = sendRequest(host + "/Auth/getCode.php?secretKey=" + panel->Controls["codelabel_" + number]->Tag);
						App^ app = JsonConvert::DeserializeObject<App^>(response);
						if (app->Code != panel->Controls["codelabel_" + number]->Text)
							this->Invoke(gcnew Action<String^>(this, &Main::changeLabel), panel->Name + "|codelabel_" + number + "|" + app->Code);
					} else {
						TwoFactorAuthenticator^ tfa = gcnew TwoFactorAuthenticator();
						auto code = tfa->GetCurrentPIN(panel->Controls["codelabel_" + number]->Tag->ToString());
						if (code != panel->Controls["codelabel_" + number]->Text)
							this->Invoke(gcnew Action<String^>(this, &Main::changeLabel), panel->Name + "|codelabel_" + number + "|" + code);
					}
				} catch (int ex) {
					panel->Controls["codelabel_" + number]->Text = "??????";
					this->Invoke(gcnew Action<String^>(this, &Main::changeLabel), panel->Name + "|codelabel_" + number + "|??????");
				}
			}
		}
	}
	private: System::Void tabControl1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (!isAuthed)
			File::WriteAllText(System::Environment::GetFolderPath(System::Environment::SpecialFolder::ApplicationData) +
				"\\GoogleAuthetificator\\Data.json", JsonConvert::SerializeObject(user));
		timer1->Stop();
		if (tabControl1->SelectedIndex == 0)
			isAuthed = false;
		if (tabControl1->SelectedIndex == 4) {
			AddPanel->Height = 28;
			up_1->Visible = false;
			down_1->Visible = false;
			editPanel_1->Visible = false;
			elementpanel->Controls->Clear();
			try {
				tabPage5->Controls->Remove(tabPage5->Controls["spacepanel"]);
			} catch (int ex) {}
			int count = user->Applications == nullptr ? 0 : user->Applications->Length;
			if (count == 0) {
				authpanel_1->Visible = false;
				AddPanel->Location = authpanel_1->Location;
			} else {
				authpanel_1->Visible = true;
				infolabel_1->Text = user->Applications[0]->Site + " (" + user->Applications[0]->Login + ")";
				codelabel_1->Tag = user->Applications[0]->Secret;
				codelabel_1->Text = "??????";
				
				for (int i = 1; i < count; i++) {
					Panel^ panel = gcnew Panel();
					panel->BackColor = authpanel_1->BackColor;
					panel->Size = authpanel_1->Size;
					panel->Name = "authpanel_" + (i + 1).ToString();
					panel->Location = Point(authpanel_1->Location.X, authpanel_1->Location.Y * (i + 1) + authpanel_1->Height * i);

					Label^ infolabel = gcnew Label();
					infolabel->AutoSize = false;
					infolabel->Size = infolabel_1->Size;
					infolabel->Font = infolabel_1->Font;
					infolabel->ForeColor = infolabel_1->ForeColor;
					infolabel->Location = infolabel_1->Location;
					infolabel->Text = user->Applications[i]->Site + " (" + user->Applications[i]->Login + ")";
					infolabel->Name = "infolabel_" + (i + 1).ToString();
					panel->Controls->Add(infolabel);

					Label^ codelabel = gcnew Label();
					codelabel->AutoSize = true;
					codelabel->Font = codelabel_1->Font;
					codelabel->ForeColor = codelabel_1->ForeColor;
					codelabel->Location = codelabel_1->Location;
					codelabel->Tag = user->Applications[i]->Secret;
					codelabel->Text = "??????";
					codelabel->Cursor = codelabel_1->Cursor;
					codelabel->Name = "codelabel_" + (i + 1).ToString();
					codelabel->DoubleClick += gcnew EventHandler(this, &Main::CopyCode_Click);
					panel->Controls->Add(codelabel);

					Label^ timelabel = gcnew Label();
					timelabel->Size = timelabel_1->Size;
					timelabel->Font = timelabel_1->Font;
					timelabel->ForeColor = timelabel_1->ForeColor;
					timelabel->TextAlign = timelabel_1->TextAlign;
					timelabel->Location = timelabel_1->Location;
					timelabel->Text = "30 сек.";
					timelabel->Name = "timelabel_" + (i + 1).ToString();
					panel->Controls->Add(timelabel);

					PictureBox^ deletebox = gcnew PictureBox();
					deletebox->Size = deletebox_1->Size;
					deletebox->Location = deletebox_1->Location;
					deletebox->SizeMode = deletebox_1->SizeMode;
					deletebox->Image = deletebox_1->Image;
					deletebox->Cursor = deletebox_1->Cursor;
					deletebox->Name = "deletebox_" + (i + 1).ToString();
					deletebox->Click += gcnew EventHandler(this, &Main::deletebox_Click);
					panel->Controls->Add(deletebox);

					PictureBox^ editbox = gcnew PictureBox();
					editbox->Size = editbox_1->Size;
					editbox->Location = editbox_1->Location;
					editbox->SizeMode = editbox_1->SizeMode;
					editbox->Image = editbox_1->Image;
					editbox->Cursor = editbox_1->Cursor;
					editbox->Tag = "0";
					editbox->Name = "editbox_" + (i + 1).ToString();
					editbox->Click += gcnew EventHandler(this, &Main::editbox_Click);
					panel->Controls->Add(editbox);

					elementpanel->Controls->Add(panel);
				}
				AddPanel->Location = Point(AddPanel->Location.X, authpanel_1->Location.Y * (count + 1) + authpanel_1->Height * count);
				customPanel->Visible = false;
				addUsername->Text = "", addSite->Text = "", addSecret->Text = "";
				Panel^ space = gcnew Panel();
				System::Windows::Forms::SystemInformation::HorizontalScrollBarThumbWidth;
				space->BackColor = Color::Red;
				space->Width = AddPanel->Width;
				space->Height = authpanel_1->Location.Y;
				space->Location = Point(AddPanel->Location.X, AddPanel->Location.Y + AddPanel->Height);
				space->Name = "spacepanel";
				tabPage5->Controls->Add(space);
				timer1->Start();
			}
		} else {
			timer1->Stop();
			if (tabControl1->SelectedIndex == 3)
				security->Text = "Автосохранение данных: " + (remember ? "ВКЛ" : "ВЫКЛ");
			else if (tabControl1->SelectedIndex == 6) {
				servicesBox->Text = "";
				for each (App^ app in user->Applications) {
					servicesBox->Text += "Сервис: " + app->Site + "\n";
					servicesBox->Text += "Имя пользователя: " + app->Login + "\n";
					servicesBox->Text += "Секретный ключ: " + app->Secret + "\n";
					servicesBox->Text += "Код: " + app->Code + "\n";
					servicesBox->Text += "Ссылка на QR код: " + app->QR + "\n\n";
				}
			} else if (tabControl1->SelectedIndex == 7) {
				dataBox->Text = "";
				try { dataBox->Text = JsonConvert::SerializeObject(user); }
				catch (int ex) {}
			}
		}

	}
	private: System::Void CopyCode_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			auto label = (Label^)sender;
			Clipboard::SetText(label->Text);
		} catch (int ex) {}
	}
	private: static bool secretCheck(App^ app, String^ secret) {
		return app->Secret != secret;
	}
	private: System::Void deletebox_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			auto picturebox = (PictureBox^)sender;
			if (isAuthed) {
				auto response = sendRequest(host + "/User/deleteSecretKey.php?login=" + user->Username + "&password=" + user->Password + "&secretKey=" +
					user->Applications[Convert::ToInt32(picturebox->Name->Split('_')[1]) - 1]->Secret);
				if (response != "OK")
					throw 1;
				else {
					auto response = sendRequest(host + "/User/login.php?login=" + login + "&password=" + password);
					try { user = JsonConvert::DeserializeObject<User^>(response); }
					catch (int ex) {}
					tabControl1_SelectedIndexChanged(sender, e);
				}
			} else {
				auto list = gcnew List<App^>(user->Applications);
				list->RemoveAt(Convert::ToInt32(picturebox->Name->Split('_')[1]) - 1);
				user->Applications = list->ToArray();
				tabControl1_SelectedIndexChanged(sender, e);
			}
		} catch (int ex) {}
	}
	private: System::Void editbox_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			auto picturebox = (PictureBox^)sender;
			int id = Convert::ToInt32(picturebox->Name->Split('_')[1]);
			if ((String^)picturebox->Tag == "0") {
				if (id == 1) {
					editPanel_1->Visible = true;
					up_1->Visible = true;
					down_1->Visible = true;
					editTextBox_1->Text = user->Applications[id - 1]->Login;
				} else {
					Panel^ panel = gcnew Panel();
					panel->BackColor = editPanel_1->BackColor;
					panel->Size = editPanel_1->Size;
					panel->Name = "editPanel_" + id.ToString();
					panel->Location = Point(editPanel_1->Location.X, editPanel_1->Location.Y + picturebox->Location.Y - editbox_1->Location.Y);

					Label^ editLabel = gcnew Label();
					editLabel->AutoSize = true;
					editLabel->Font = editLabel_1->Font;
					editLabel->ForeColor = editLabel_1->ForeColor;
					editLabel->Location = editLabel_1->Location;
					editLabel->Text = "Новый логин:";
					editLabel->Name = "editLabel_" + id.ToString();
					panel->Controls->Add(editLabel);

					TextBox^ editTextBox = gcnew TextBox();
					editTextBox->Font = editTextBox_1->Font;
					editTextBox->ForeColor = editTextBox_1->ForeColor;
					editTextBox->BackColor = editTextBox_1->BackColor;
					editTextBox->BorderStyle = editTextBox_1->BorderStyle;
					editTextBox->Size = editTextBox_1->Size;
					editTextBox->Location = editTextBox_1->Location;
					editTextBox->Text = user->Applications[id - 1]->Login;
					editTextBox->TabStop = false;
					editTextBox->Name = "editTextBox_" + id.ToString();
					panel->Controls->Add(editTextBox);

					Panel^ editLine = gcnew Panel();
					editLine->BackColor = editLine_1->BackColor;
					editLine->Size = editLine_1->Size;
					editLine->Name = "editLine_" + id.ToString();
					editLine->Location = editLine_1->Location;
					panel->Controls->Add(editLine);

					PictureBox^ up = gcnew PictureBox();
					up->Size = up_1->Size;
					up->Location = up_1->Location;
					up->SizeMode = up_1->SizeMode;
					up->Image = up_1->Image;
					up->Cursor = up_1->Cursor;
					up->Name = "up_" + id.ToString();
					up->Click += gcnew EventHandler(this, &Main::up_Click);
					up->Enabled = id != 1;
					picturebox->Parent->Controls->Add(up);

					PictureBox^ down = gcnew PictureBox();
					down->Size = down_1->Size;
					down->Location = down_1->Location;
					down->SizeMode = down_1->SizeMode;
					down->Image = down_1->Image;
					down->Cursor = down_1->Cursor;
					down->Name = "down_" + id.ToString();
					down->Click += gcnew EventHandler(this, &Main::down_Click);
					down->Enabled = id != user->Applications->Length;
					picturebox->Parent->Controls->Add(down);

					picturebox->Parent->Controls->Add(panel);
					panel->BringToFront();
				}
				picturebox->Tag = "1";
			} else if (!String::IsNullOrEmpty(picturebox->Parent->Controls["editPanel_" + id.ToString()]->Controls["editTextBox_" + id.ToString()]->Text)) {
				auto text = picturebox->Parent->Controls["editPanel_" + id.ToString()]->Controls["editTextBox_" + id.ToString()]->Text;
				String^ response = "OK";
				if (isAuthed) {
					response = sendRequest(host + "/User/changeUsername.php?login=" + user->Username + "&password=" + user->Password + "&secretKey=" +
						user->Applications[id - 1]->Secret + "&newUsername=" + text);
				} else
					user->Applications[id - 1]->Login = text;
				if (response != "OK")
					throw 1;
				else {
					picturebox->Parent->Controls["infolabel_" + id.ToString()]->Text = user->Applications[id - 1]->Site + " (" + text + ")";
					if (id != 1) {
						picturebox->Parent->Controls->Remove(picturebox->Parent->Controls["editPanel_" + id.ToString()]);
						picturebox->Parent->Controls->Remove(picturebox->Parent->Controls["up_" + id.ToString()]);
						picturebox->Parent->Controls->Remove(picturebox->Parent->Controls["down_" + id.ToString()]);
					} else {
						editPanel_1->Visible = false;
						up_1->Visible = false;
						down_1->Visible = false;
					}
					picturebox->Tag = "0";
				}
			} else throw 2;
		} catch (int ex) {}
	}
	private: System::Void up_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			auto picturebox = (PictureBox^)sender;
			int id = Convert::ToInt32(picturebox->Name->Split('_')[1]);
			if (isAuthed) {
				auto response = sendRequest(host + "/User/changePosition.php?login=" + user->Username + "&password=" + user->Password + "&secretKey=" +
					user->Applications[id - 1]->Secret + "&newPosition=" + (id - 2).ToString());
				if (response != "OK")
					throw 1;
				else {
					auto response = sendRequest(host + "/User/login.php?login=" + login + "&password=" + password);
					try { user = JsonConvert::DeserializeObject<User^>(response); }
					catch (int ex) {}
					tabControl1_SelectedIndexChanged(sender, e);
				}
			} else {
				auto tmp = user->Applications[id - 1];
				user->Applications[id - 1] = user->Applications[id - 2];
				user->Applications[id - 2] = tmp;
				tabControl1_SelectedIndexChanged(sender, e);
			}
		} catch (int ex) {}
	}
	private: System::Void down_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			auto picturebox = (PictureBox^)sender;
			int id = Convert::ToInt32(picturebox->Name->Split('_')[1]);
			if (isAuthed) {
				auto response = sendRequest(host + "/User/changePosition.php?login=" + user->Username + "&password=" + user->Password + "&secretKey=" +
					user->Applications[id - 1]->Secret + "&newPosition=" + id.ToString());
				if (response != "OK")
					throw 1;
				else {
					auto response = sendRequest(host + "/User/login.php?login=" + login + "&password=" + password);
					try { user = JsonConvert::DeserializeObject<User^>(response); }
					catch (int ex) {}
					tabControl1_SelectedIndexChanged(sender, e);
				}
			} else {
				auto tmp = user->Applications[id - 1];
				user->Applications[id - 1] = user->Applications[id];
				user->Applications[id] = tmp;
				tabControl1_SelectedIndexChanged(sender, e);
			}
		}
		catch (int ex) {}
	}
	private: System::Void AddService_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			tabPage5->Controls->Remove(tabPage5->Controls["spacepanel"]);
		} catch (int ex) {}
		AddPanel->Height = AddPanel->Height == 28 ? 65 : 28;
		customPanel->Visible = false;
		Panel^ space = gcnew Panel();
		System::Windows::Forms::SystemInformation::HorizontalScrollBarThumbWidth;
		space->BackColor = Color::Red;
		space->Width = AddPanel->Width;
		space->Height = authpanel_1->Location.Y;
		space->Location = Point(AddPanel->Location.X, AddPanel->Location.Y + AddPanel->Height);
		space->Name = "spacepanel";
		tabPage5->Controls->Add(space);
	}
	private: System::Void ScanQR_Click(System::Object^ sender, System::EventArgs^ e) {
		Process^ scaner = gcnew Process();
		String^ currentPath = Assembly::GetExecutingAssembly()->Location;
		scaner->StartInfo->FileName = currentPath->Substring(0, currentPath->LastIndexOf("\\")) + "\\getQR.exe";
		scaner->Start();
		scaner->WaitForExit();
		String^ data = Clipboard::GetText();
		
		if (data != "NULL") {
			try {
				data->Replace("\/", "/");
				data = data->Substring(data->LastIndexOf("/") + 1);
				if (isAuthed) {
					auto response = sendRequest(host + "/User/addSecretKey.php?login=" + user->Username + "&password=" + user->Password +
						"&secretKey=" + data->Substring(data->IndexOf("=") + 1) + "&username=" + data->Substring(0, data->IndexOf("@")) +
						"&site=" + data->Substring(data->IndexOf("@") + 1, data->IndexOf("?") - data->IndexOf("@") - 1));
					if (response != "OK")
						throw 1;
					else {
						auto response = sendRequest(host + "/User/login.php?login=" + login + "&password=" + password);
						try { user = JsonConvert::DeserializeObject<User^>(response); }
						catch (int ex) {}
						tabControl1_SelectedIndexChanged(sender, e);
					}
				} else {
					auto app = gcnew App();
					app->Secret = data->Substring(data->IndexOf("=") + 1);
					app->Login = data->Substring(0, data->IndexOf("@"));
					app->Site = data->Substring(data->IndexOf("@") + 1, data->IndexOf("?") - data->IndexOf("@") - 1);
					auto list = gcnew List<App^>(user->Applications);
					list->Add(app);
					user->Applications = list->ToArray();
					tabControl1_SelectedIndexChanged(sender, e);
				}
			} catch (int ex) {}
		}
	}
	private: System::Void addCustomService_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!String::IsNullOrEmpty(addUsername->Text) && !String::IsNullOrEmpty(addSite->Text) && !String::IsNullOrEmpty(addSecret->Text)) {
			try {
				if (isAuthed) {
					auto response = sendRequest(host + "/User/addSecretKey.php?login=" + user->Username + "&password=" + user->Password +
						"&secretKey=" + addSecret->Text + "&username=" + addUsername->Text + "&site=" + addSite->Text);
					if (response != "OK")
						throw 1;
					else {
						auto response = sendRequest(host + "/User/login.php?login=" + login + "&password=" + password);
						try { user = JsonConvert::DeserializeObject<User^>(response); }
						catch (int ex) {}
						tabControl1_SelectedIndexChanged(sender, e);
					}
				} else {
					auto app = gcnew App();
					app->Secret = addSecret->Text;
					app->Login = addUsername->Text;
					app->Site = addSite->Text;
					auto list = gcnew List<App^>(user->Applications);
					list->Add(app);
					user->Applications = list->ToArray();
					tabControl1_SelectedIndexChanged(sender, e);
				}
			}
			catch (int ex) {}
		}
	}
	private: System::Void EnterManually_Click(System::Object^ sender, System::EventArgs^ e) {
		AddPanel->Height = 161;
		customPanel->Visible = true;
		tabPage5->Controls->Remove(tabPage5->Controls["spacepanel"]);
		Panel^ space = gcnew Panel();
		System::Windows::Forms::SystemInformation::HorizontalScrollBarThumbWidth;
		space->BackColor = Color::Red;
		space->Width = AddPanel->Width;
		space->Height = authpanel_1->Location.Y;
		space->Location = Point(AddPanel->Location.X, AddPanel->Location.Y + AddPanel->Height);
		space->Name = "spacepanel";
		tabPage5->Controls->Add(space);
	}
	private: System::Void settings_Click(System::Object^ sender, System::EventArgs^ e) {
		if (tabControl1->SelectedIndex != 3)
			lastTab = tabControl1->SelectedIndex;
		tabControl1->SelectedIndex = 3;
	}
	private: System::Void source_Click(System::Object^ sender, System::EventArgs^ e) {
		Process::Start("https://github.com/Irval1337/GoogleAuthenticator");
	}
	private: System::Void clearServices_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			if (isAuthed) {
				if (!String::IsNullOrEmpty(user->Id)) {
					auto response = sendRequest(host + "/User/clearServices.php?login=" + user->Username + "&password=" + user->Password);
					if (response != "OK")
						throw 1;
					else {
						auto response = sendRequest(host + "/User/login.php?login=" + login + "&password=" + password);
						try { user = JsonConvert::DeserializeObject<User^>(response); }
						catch (int ex) {}
					}
				}
			} else {
				auto list = gcnew List<App^>(user->Applications);
				list->Clear();
				user->Applications = list->ToArray();
				tabControl1_SelectedIndexChanged(sender, e);
			}
		} catch (int ex) {}
	}
	private: System::Void sync_Click(System::Object^ sender, System::EventArgs^ e) {
		auto utcNow = DateTime::UtcNow;
		SYSTEMTIME systemTime;
		GetSystemTime(&systemTime);
		systemTime.wMinute = utcNow.Minute;
		systemTime.wSecond = utcNow.Second;
		systemTime.wMilliseconds = utcNow.Millisecond;
		SetSystemTime(&systemTime);
	}
	private: System::Void appinfo_Click(System::Object^ sender, System::EventArgs^ e) {
		Process::Start("https://github.com/Irval1337/GoogleAuthenticator/blob/main/LICENSE");
	}
	private: System::Void services_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!isAuthed)
			tabControl1->SelectedIndex = 6;
	}
	private: System::Void import_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!isAuthed)
			tabControl1->SelectedIndex = 7;
	}
	private: System::Void createDB_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
			String^ ReadResFilePlace = nullptr;
			saveFileDialog1->Filter = "JSON Settings (*.json)|*.json|All files (*.*)|*.*";
			saveFileDialog1->FileName = "GoogleAuth_Backup";
			saveFileDialog1->DefaultExt = "json";
			if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				ReadResFilePlace = saveFileDialog1->FileName;
			StreamWriter^ sw = gcnew StreamWriter(ReadResFilePlace);
			sw->WriteLine(dataBox->Text);
			sw->Close();
		} catch (int ex) {}
	}
	private: System::Void loadDB_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog();
			openFileDialog1->Filter = "JSON Settings (*.json)|*.json|All files (*.*)|*.*";
			openFileDialog1->RestoreDirectory = true;

			if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				String^ filename = openFileDialog1->FileName;
				String^ text = File::ReadAllText(filename);
				User^ newData = JsonConvert::DeserializeObject<User^>(text);
				user->Applications = newData->Applications;
				File::WriteAllText(System::Environment::GetFolderPath(System::Environment::SpecialFolder::ApplicationData) + 
					"\\GoogleAuthetificator\\Data.json", JsonConvert::SerializeObject(user));
			}
		} catch (int ex) {}
	}
	private: System::Void security_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			remember = !remember;
			security->Text = security->Text->Replace(remember ? "ВЫКЛ" : "ВКЛ", remember ? "ВКЛ" : "ВЫКЛ");
		} catch (int ex) {}
	}
	};
}

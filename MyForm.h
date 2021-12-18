#pragma once

#include "OMSIPresToolsCLR.h"


namespace OMSIPresToolsCLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	System::Decimal oldFovValue = (System::Decimal)45.0;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TrackBar^ f4FovTrackbar;
	protected:



	protected:








	private: System::Windows::Forms::Label^ label4;

	private: System::Windows::Forms::Label^ f4FovMaxLabel;




	private: System::Windows::Forms::LinkLabel^ labelAboutThanksTo;














	private: System::Windows::Forms::LinkLabel^ labelAboutVersionGithub;




	private: System::Windows::Forms::Label^ labelAboutTitle;
	private: System::Windows::Forms::PictureBox^ pictureAboutIcon;



	private: System::Windows::Forms::Label^ labelWarningGameClosed;
	private: System::Windows::Forms::LinkLabel^ labelYouTube;
	private: System::Windows::Forms::PictureBox^ pictureYouTubeIcon;
	private: System::Windows::Forms::PictureBox^ pictureGitHubIcon;
	private: System::Windows::Forms::LinkLabel^ labelSteamGuide;








	private: System::Windows::Forms::LinkLabel^ labelAboutAuthor;
	private: System::Windows::Forms::LinkLabel^ labelAboutThanksTo2;

	private: System::Windows::Forms::Label^ f4FovStatusLabel;

	private: System::Windows::Forms::CheckBox^ f4FovToggle;
	private: System::Windows::Forms::NumericUpDown^ f4FovNumericUpDown;
	private: System::Windows::Forms::Label^ f4FovTitle;
	private: System::Windows::Forms::Label^ f4FovMinLabel;
	private: System::Windows::Forms::Label^ f4FovRawLabel;
	private: System::Windows::Forms::Label^ f4fovvaluetmp2;
	private: System::Windows::Forms::CheckBox^ pinToTopToggle;








	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->f4FovTrackbar = (gcnew System::Windows::Forms::TrackBar());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->f4FovMaxLabel = (gcnew System::Windows::Forms::Label());
			this->labelAboutThanksTo = (gcnew System::Windows::Forms::LinkLabel());
			this->labelAboutVersionGithub = (gcnew System::Windows::Forms::LinkLabel());
			this->labelAboutTitle = (gcnew System::Windows::Forms::Label());
			this->pictureAboutIcon = (gcnew System::Windows::Forms::PictureBox());
			this->labelWarningGameClosed = (gcnew System::Windows::Forms::Label());
			this->labelYouTube = (gcnew System::Windows::Forms::LinkLabel());
			this->pictureYouTubeIcon = (gcnew System::Windows::Forms::PictureBox());
			this->pictureGitHubIcon = (gcnew System::Windows::Forms::PictureBox());
			this->labelSteamGuide = (gcnew System::Windows::Forms::LinkLabel());
			this->labelAboutAuthor = (gcnew System::Windows::Forms::LinkLabel());
			this->labelAboutThanksTo2 = (gcnew System::Windows::Forms::LinkLabel());
			this->f4FovStatusLabel = (gcnew System::Windows::Forms::Label());
			this->f4FovToggle = (gcnew System::Windows::Forms::CheckBox());
			this->f4FovNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->f4FovTitle = (gcnew System::Windows::Forms::Label());
			this->f4FovMinLabel = (gcnew System::Windows::Forms::Label());
			this->f4FovRawLabel = (gcnew System::Windows::Forms::Label());
			this->f4fovvaluetmp2 = (gcnew System::Windows::Forms::Label());
			this->pinToTopToggle = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f4FovTrackbar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureAboutIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureYouTubeIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureGitHubIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f4FovNumericUpDown))->BeginInit();
			this->SuspendLayout();
			// 
			// f4FovTrackbar
			// 
			this->f4FovTrackbar->AutoSize = false;
			this->f4FovTrackbar->Enabled = false;
			this->f4FovTrackbar->Location = System::Drawing::Point(31, 156);
			this->f4FovTrackbar->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->f4FovTrackbar->Maximum = 1500;
			this->f4FovTrackbar->Minimum = 10;
			this->f4FovTrackbar->Name = L"f4FovTrackbar";
			this->f4FovTrackbar->Size = System::Drawing::Size(513, 55);
			this->f4FovTrackbar->TabIndex = 2;
			this->f4FovTrackbar->TickFrequency = 1500;
			this->f4FovTrackbar->Value = 450;
			this->f4FovTrackbar->Scroll += gcnew System::EventHandler(this, &MyForm::f4FovTrackbar_Scroll);
			// 
			// label4
			// 
			this->label4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label4->Location = System::Drawing::Point(21, 247);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->MaximumSize = System::Drawing::Size(0, 2);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(0, 2);
			this->label4->TabIndex = 9;
			// 
			// f4FovMaxLabel
			// 
			this->f4FovMaxLabel->AutoSize = true;
			this->f4FovMaxLabel->Location = System::Drawing::Point(505, 196);
			this->f4FovMaxLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->f4FovMaxLabel->Name = L"f4FovMaxLabel";
			this->f4FovMaxLabel->Size = System::Drawing::Size(44, 17);
			this->f4FovMaxLabel->TabIndex = 11;
			this->f4FovMaxLabel->Text = L"150.0";
			// 
			// labelAboutThanksTo
			// 
			this->labelAboutThanksTo->AutoSize = true;
			this->labelAboutThanksTo->LinkArea = System::Windows::Forms::LinkArea(11, 9);
			this->labelAboutThanksTo->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->labelAboutThanksTo->Location = System::Drawing::Point(229, 498);
			this->labelAboutThanksTo->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelAboutThanksTo->Name = L"labelAboutThanksTo";
			this->labelAboutThanksTo->Size = System::Drawing::Size(138, 20);
			this->labelAboutThanksTo->TabIndex = 7;
			this->labelAboutThanksTo->TabStop = true;
			this->labelAboutThanksTo->Text = L"Thanks to: rev_eng_e,";
			this->labelAboutThanksTo->UseCompatibleTextRendering = true;
			this->labelAboutThanksTo->VisitedLinkColor = System::Drawing::Color::Blue;
			this->labelAboutThanksTo->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MyForm::labelAboutThanksTo_LinkClicked);
			// 
			// labelAboutVersionGithub
			// 
			this->labelAboutVersionGithub->AutoSize = true;
			this->labelAboutVersionGithub->LinkArea = System::Windows::Forms::LinkArea(15, 6);
			this->labelAboutVersionGithub->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->labelAboutVersionGithub->Location = System::Drawing::Point(229, 441);
			this->labelAboutVersionGithub->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelAboutVersionGithub->Name = L"labelAboutVersionGithub";
			this->labelAboutVersionGithub->Size = System::Drawing::Size(129, 20);
			this->labelAboutVersionGithub->TabIndex = 5;
			this->labelAboutVersionGithub->TabStop = true;
			this->labelAboutVersionGithub->Text = L"v0.1.0 alpha • Github";
			this->labelAboutVersionGithub->UseCompatibleTextRendering = true;
			this->labelAboutVersionGithub->VisitedLinkColor = System::Drawing::Color::Blue;
			this->labelAboutVersionGithub->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MyForm::labelAboutVersionGithub_LinkClicked);
			// 
			// labelAboutTitle
			// 
			this->labelAboutTitle->AutoSize = true;
			this->labelAboutTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelAboutTitle->Location = System::Drawing::Point(225, 402);
			this->labelAboutTitle->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelAboutTitle->Name = L"labelAboutTitle";
			this->labelAboutTitle->Size = System::Drawing::Size(232, 25);
			this->labelAboutTitle->TabIndex = 13;
			this->labelAboutTitle->Text = L"OMSI Presentation Tools";
			// 
			// pictureAboutIcon
			// 
			this->pictureAboutIcon->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureAboutIcon.Image")));
			this->pictureAboutIcon->Location = System::Drawing::Point(49, 402);
			this->pictureAboutIcon->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pictureAboutIcon->Name = L"pictureAboutIcon";
			this->pictureAboutIcon->Size = System::Drawing::Size(135, 111);
			this->pictureAboutIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureAboutIcon->TabIndex = 15;
			this->pictureAboutIcon->TabStop = false;
			// 
			// labelWarningGameClosed
			// 
			this->labelWarningGameClosed->AutoSize = true;
			this->labelWarningGameClosed->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->labelWarningGameClosed->Location = System::Drawing::Point(91, 298);
			this->labelWarningGameClosed->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelWarningGameClosed->Name = L"labelWarningGameClosed";
			this->labelWarningGameClosed->Size = System::Drawing::Size(360, 18);
			this->labelWarningGameClosed->TabIndex = 21;
			this->labelWarningGameClosed->Text = L"Please keep any other games with anti-cheats closed!";
			// 
			// labelYouTube
			// 
			this->labelYouTube->AutoSize = true;
			this->labelYouTube->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelYouTube->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->labelYouTube->Location = System::Drawing::Point(93, 265);
			this->labelYouTube->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelYouTube->Name = L"labelYouTube";
			this->labelYouTube->Size = System::Drawing::Size(245, 18);
			this->labelYouTube->TabIndex = 3;
			this->labelYouTube->TabStop = true;
			this->labelYouTube->Text = L"YouTube tutorial && suggested usage";
			this->labelYouTube->VisitedLinkColor = System::Drawing::Color::Blue;
			this->labelYouTube->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MyForm::labelYouTube_LinkClicked);
			// 
			// pictureYouTubeIcon
			// 
			this->pictureYouTubeIcon->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureYouTubeIcon.Image")));
			this->pictureYouTubeIcon->Location = System::Drawing::Point(60, 261);
			this->pictureYouTubeIcon->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pictureYouTubeIcon->Name = L"pictureYouTubeIcon";
			this->pictureYouTubeIcon->Size = System::Drawing::Size(32, 28);
			this->pictureYouTubeIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureYouTubeIcon->TabIndex = 23;
			this->pictureYouTubeIcon->TabStop = false;
			// 
			// pictureGitHubIcon
			// 
			this->pictureGitHubIcon->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureGitHubIcon.Image")));
			this->pictureGitHubIcon->Location = System::Drawing::Point(380, 258);
			this->pictureGitHubIcon->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pictureGitHubIcon->Name = L"pictureGitHubIcon";
			this->pictureGitHubIcon->Size = System::Drawing::Size(27, 33);
			this->pictureGitHubIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureGitHubIcon->TabIndex = 25;
			this->pictureGitHubIcon->TabStop = false;
			// 
			// labelSteamGuide
			// 
			this->labelSteamGuide->AutoSize = true;
			this->labelSteamGuide->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelSteamGuide->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->labelSteamGuide->Location = System::Drawing::Point(409, 265);
			this->labelSteamGuide->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelSteamGuide->Name = L"labelSteamGuide";
			this->labelSteamGuide->Size = System::Drawing::Size(90, 18);
			this->labelSteamGuide->TabIndex = 4;
			this->labelSteamGuide->TabStop = true;
			this->labelSteamGuide->Text = L"Steam guide";
			this->labelSteamGuide->VisitedLinkColor = System::Drawing::Color::Blue;
			this->labelSteamGuide->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MyForm::labelSteamGuide_LinkClicked);
			// 
			// labelAboutAuthor
			// 
			this->labelAboutAuthor->AutoSize = true;
			this->labelAboutAuthor->LinkArea = System::Windows::Forms::LinkArea(11, 5);
			this->labelAboutAuthor->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->labelAboutAuthor->Location = System::Drawing::Point(229, 470);
			this->labelAboutAuthor->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelAboutAuthor->Name = L"labelAboutAuthor";
			this->labelAboutAuthor->Size = System::Drawing::Size(101, 20);
			this->labelAboutAuthor->TabIndex = 6;
			this->labelAboutAuthor->TabStop = true;
			this->labelAboutAuthor->Text = L"Created by sjain";
			this->labelAboutAuthor->UseCompatibleTextRendering = true;
			this->labelAboutAuthor->VisitedLinkColor = System::Drawing::Color::Blue;
			this->labelAboutAuthor->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MyForm::labelAboutAuthor_LinkClicked);
			// 
			// labelAboutThanksTo2
			// 
			this->labelAboutThanksTo2->AutoSize = true;
			this->labelAboutThanksTo2->LinkArea = System::Windows::Forms::LinkArea(0, 19);
			this->labelAboutThanksTo2->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->labelAboutThanksTo2->Location = System::Drawing::Point(377, 498);
			this->labelAboutThanksTo2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelAboutThanksTo2->Name = L"labelAboutThanksTo2";
			this->labelAboutThanksTo2->Size = System::Drawing::Size(129, 17);
			this->labelAboutThanksTo2->TabIndex = 8;
			this->labelAboutThanksTo2->TabStop = true;
			this->labelAboutThanksTo2->Text = L"win32kbase / wolfie";
			this->labelAboutThanksTo2->VisitedLinkColor = System::Drawing::Color::Blue;
			this->labelAboutThanksTo2->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MyForm::labelAboutThanksTo2_LinkClicked);
			// 
			// f4FovStatusLabel
			// 
			this->f4FovStatusLabel->AutoSize = true;
			this->f4FovStatusLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->f4FovStatusLabel->Location = System::Drawing::Point(105, 329);
			this->f4FovStatusLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->f4FovStatusLabel->Name = L"f4FovStatusLabel";
			this->f4FovStatusLabel->Size = System::Drawing::Size(327, 18);
			this->f4FovStatusLabel->TabIndex = 29;
			this->f4FovStatusLabel->Text = L"Controls will be unavailable until a map is loaded.";
			// 
			// f4FovToggle
			// 
			this->f4FovToggle->AutoSize = true;
			this->f4FovToggle->Location = System::Drawing::Point(144, 90);
			this->f4FovToggle->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->f4FovToggle->Name = L"f4FovToggle";
			this->f4FovToggle->Size = System::Drawing::Size(82, 21);
			this->f4FovToggle->TabIndex = 0;
			this->f4FovToggle->Text = L"Enabled";
			this->f4FovToggle->UseVisualStyleBackColor = true;
			this->f4FovToggle->CheckedChanged += gcnew System::EventHandler(this, &MyForm::f4FovToggle_CheckedChanged);
			// 
			// f4FovNumericUpDown
			// 
			this->f4FovNumericUpDown->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->f4FovNumericUpDown->DecimalPlaces = 1;
			this->f4FovNumericUpDown->Enabled = false;
			this->f4FovNumericUpDown->Location = System::Drawing::Point(341, 86);
			this->f4FovNumericUpDown->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->f4FovNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 150, 0, 0, 0 });
			this->f4FovNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9, 0, 0, 65536 });
			this->f4FovNumericUpDown->Name = L"f4FovNumericUpDown";
			this->f4FovNumericUpDown->Size = System::Drawing::Size(80, 22);
			this->f4FovNumericUpDown->TabIndex = 1;
			this->f4FovNumericUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->f4FovNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 45, 0, 0, 0 });
			this->f4FovNumericUpDown->ValueChanged += gcnew System::EventHandler(this, &MyForm::f4FovNumericUpDown_ValueChanged);
			// 
			// f4FovTitle
			// 
			this->f4FovTitle->AutoSize = true;
			this->f4FovTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->f4FovTitle->Location = System::Drawing::Point(140, 27);
			this->f4FovTitle->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->f4FovTitle->Name = L"f4FovTitle";
			this->f4FovTitle->Size = System::Drawing::Size(257, 18);
			this->f4FovTitle->TabIndex = 7;
			this->f4FovTitle->Text = L"Free Map (F4) Camera FOV Value (°):";
			// 
			// f4FovMinLabel
			// 
			this->f4FovMinLabel->AutoSize = true;
			this->f4FovMinLabel->Location = System::Drawing::Point(35, 196);
			this->f4FovMinLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->f4FovMinLabel->Name = L"f4FovMinLabel";
			this->f4FovMinLabel->Size = System::Drawing::Size(28, 17);
			this->f4FovMinLabel->TabIndex = 10;
			this->f4FovMinLabel->Text = L"1.0";
			// 
			// f4FovRawLabel
			// 
			this->f4FovRawLabel->AutoSize = true;
			this->f4FovRawLabel->Location = System::Drawing::Point(291, 90);
			this->f4FovRawLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->f4FovRawLabel->Name = L"f4FovRawLabel";
			this->f4FovRawLabel->Size = System::Drawing::Size(39, 17);
			this->f4FovRawLabel->TabIndex = 20;
			this->f4FovRawLabel->Text = L"Raw:";
			// 
			// f4fovvaluetmp2
			// 
			this->f4fovvaluetmp2->AutoSize = true;
			this->f4fovvaluetmp2->Location = System::Drawing::Point(444, 91);
			this->f4fovvaluetmp2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->f4fovvaluetmp2->Name = L"f4fovvaluetmp2";
			this->f4fovvaluetmp2->Size = System::Drawing::Size(0, 17);
			this->f4fovvaluetmp2->TabIndex = 28;
			// 
			// pinToTopToggle
			// 
			this->pinToTopToggle->Appearance = System::Windows::Forms::Appearance::Button;
			this->pinToTopToggle->AutoSize = true;
			this->pinToTopToggle->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pinToTopToggle.Image")));
			this->pinToTopToggle->Location = System::Drawing::Point(16, 15);
			this->pinToTopToggle->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pinToTopToggle->Name = L"pinToTopToggle";
			this->pinToTopToggle->Size = System::Drawing::Size(22, 22);
			this->pinToTopToggle->TabIndex = 30;
			this->pinToTopToggle->UseVisualStyleBackColor = true;
			this->pinToTopToggle->CheckedChanged += gcnew System::EventHandler(this, &MyForm::pinToTopToggle_CheckedChanged);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(575, 555);
			this->Controls->Add(this->pinToTopToggle);
			this->Controls->Add(this->f4FovStatusLabel);
			this->Controls->Add(this->f4fovvaluetmp2);
			this->Controls->Add(this->labelAboutThanksTo2);
			this->Controls->Add(this->labelSteamGuide);
			this->Controls->Add(this->pictureGitHubIcon);
			this->Controls->Add(this->pictureYouTubeIcon);
			this->Controls->Add(this->labelYouTube);
			this->Controls->Add(this->labelWarningGameClosed);
			this->Controls->Add(this->f4FovRawLabel);
			this->Controls->Add(this->labelAboutThanksTo);
			this->Controls->Add(this->labelAboutAuthor);
			this->Controls->Add(this->labelAboutVersionGithub);
			this->Controls->Add(this->pictureAboutIcon);
			this->Controls->Add(this->labelAboutTitle);
			this->Controls->Add(this->f4FovMaxLabel);
			this->Controls->Add(this->f4FovMinLabel);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->f4FovTitle);
			this->Controls->Add(this->f4FovNumericUpDown);
			this->Controls->Add(this->f4FovToggle);
			this->Controls->Add(this->f4FovTrackbar);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"MyForm";
			this->Text = L"OMSI Presentation Tools";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f4FovTrackbar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureAboutIcon))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureYouTubeIcon))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureGitHubIcon))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f4FovNumericUpDown))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion




	private: System::Void labelAboutThanksTo2_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {

		System::Diagnostics::Process::Start("https://github.com/win32kbase");
	}
	private: System::Void labelAboutThanksTo_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {

		System::Diagnostics::Process::Start("https://github.com/rev-eng-e");

	}
	private: System::Void labelAboutAuthor_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {

		System::Diagnostics::Process::Start("https://github.com/sjain882");
	}
	private: System::Void labelAboutVersionGithub_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {

		System::Diagnostics::Process::Start("https://github.com/sjain882/OMSI-Presentation-Tools");
	}
	private: System::Void labelSteamGuide_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {

		System::Diagnostics::Process::Start("https://steamcommunity.com/sharedfiles/filedetails/?id=2569510456");

	}

	private: System::Void labelYouTube_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {
		System::Diagnostics::Process::Start("https://www.youtube.com/watch?v=pvU8gO66mTs");
	}



	private: System::Void f4FovToggle_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

		toggleF4FovEnabled();
		this->f4FovTrackbar->Enabled = !this->f4FovTrackbar->Enabled;
		this->f4FovNumericUpDown->Enabled = !this->f4FovNumericUpDown->Enabled;

		if ((this->f4FovTrackbar->Enabled == false) && (this->f4FovNumericUpDown->Enabled == false)) {
			// Just disabled FOV application
			justEnabledFOVApplication = false;
			this->f4FovTrackbar->Value = 450;
			this->f4FovNumericUpDown->Value = (System::Decimal)45.0;
			f4FovHoldValue = f4FovActValue;
			f4FovActValue = 45.0;
			//MessageBox::Show("1");
		} else {
			// Just enabled FOV application
			justEnabledFOVApplication = true;
			this->f4FovTrackbar->Value = (int)f4FovHoldValue * 10.0;
			this->f4FovNumericUpDown->Value = (System::Decimal)f4FovHoldValue;
			f4FovActValue = f4FovHoldValue;
			//MessageBox::Show("2");

		}
	}

	private: System::Void f4FovTrackbar_Scroll(System::Object^ sender, System::EventArgs^ e) {
		justScrolled = true;
		f4FovActValue = (float)this->f4FovTrackbar->Value / 10.0;
		//this->f4fovvaluetmp2->Text = f4FovActValue.ToString();
		this->f4FovNumericUpDown->Value = (System::Decimal)this->f4FovTrackbar->Value / (System::Decimal)10.0;
		//this->f4fovvaluetmp2->Text = this->f4FovTrackbar->Value.ToString();
		justScrolled = false;
	}


	private: System::Void f4FovNumericUpDown_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		if (justEnabledFOVApplication) {
			if (!justScrolled) {

				System::Decimal newFovValue = f4FovNumericUpDown->Value;

				if (oldFovValue < newFovValue) {

					f4FovActValue = (float)this->f4FovNumericUpDown->Value;
					//this->f4fovvaluetmp2->Text = f4FovActValue.ToString();
					this->f4FovTrackbar->Value = (int)this->f4FovNumericUpDown->Value * 10.0;
					//this->f4fovvaluetmp2->Text = this->f4FovTrackbar->Value.ToString();
				}
				else if (oldFovValue > newFovValue) {

					if (newFovValue < (System::Decimal(2.1))) {
						f4FovActValue = (float)1.0;
						this->f4FovNumericUpDown->Value = (System::Decimal)1.0;
						this->f4FovTrackbar->Value = 10;
						//this->f4fovvaluetmp2->Text = this->f4FovTrackbar->Value.ToString();
					}
					else {
						f4FovActValue = (float)this->f4FovNumericUpDown->Value;
						//this->f4fovvaluetmp2->Text = f4FovActValue.ToString();
						this->f4FovTrackbar->Value = (int)this->f4FovNumericUpDown->Value * 10.0;
						//this->f4fovvaluetmp2->Text = this->f4FovTrackbar->Value.ToString();
					}
				}

				oldFovValue = newFovValue;
			}
		}
	}

	private: System::Void MyForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		if (MessageBox::Show("Are you sure you want to quit?\nOMSI 2 will remain running and the F4 FOV will be reset to default.\nYou will not be able to relaunch OPT until you next launch OMSI.", "OMSI Presentation Tools", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {

			f4FovActValue = (float)45.0;

			// Reset FOV to 45
			// Detach from process

		}
		else {
			e->Cancel = true;	// Cancel the close event
		}
	}

private: System::Void pinToTopToggle_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	TopMost = !TopMost;
}
};
}

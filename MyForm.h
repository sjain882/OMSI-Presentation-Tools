#pragma once

namespace OMSIPresToolsCLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

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

	private: System::Windows::Forms::CheckBox^ f4FovToggle;
	private: System::Windows::Forms::NumericUpDown^ f4FovNumericUpDown;
	protected:




	private: System::Windows::Forms::Label^ f4FovTitle;



	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ f4FovMinLabel;
	private: System::Windows::Forms::Label^ f4FovMaxLabel;



	private: System::Windows::Forms::Label^ f4FovRawLabel;
	private: System::Windows::Forms::LinkLabel^ labelAboutThanksTo;














	private: System::Windows::Forms::LinkLabel^ labelAboutVersionGithub;




	private: System::Windows::Forms::Label^ labelAboutTitle;
	private: System::Windows::Forms::PictureBox^ pictureAboutIcon;



	private: System::Windows::Forms::Label^ labelWarningGameClosed;
	private: System::Windows::Forms::LinkLabel^ labelYouTube;
	private: System::Windows::Forms::PictureBox^ pictureYouTubeIcon;
	private: System::Windows::Forms::PictureBox^ pictureGitHubIcon;






	private: System::Windows::Forms::LinkLabel^ labelGitHubReadme;

	private: System::Windows::Forms::LinkLabel^ labelAboutAuthor;





	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->f4FovTrackbar = (gcnew System::Windows::Forms::TrackBar());
			this->f4FovToggle = (gcnew System::Windows::Forms::CheckBox());
			this->f4FovNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->f4FovTitle = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->f4FovMinLabel = (gcnew System::Windows::Forms::Label());
			this->f4FovMaxLabel = (gcnew System::Windows::Forms::Label());
			this->f4FovRawLabel = (gcnew System::Windows::Forms::Label());
			this->labelAboutThanksTo = (gcnew System::Windows::Forms::LinkLabel());
			this->labelAboutVersionGithub = (gcnew System::Windows::Forms::LinkLabel());
			this->labelAboutTitle = (gcnew System::Windows::Forms::Label());
			this->pictureAboutIcon = (gcnew System::Windows::Forms::PictureBox());
			this->labelWarningGameClosed = (gcnew System::Windows::Forms::Label());
			this->labelYouTube = (gcnew System::Windows::Forms::LinkLabel());
			this->pictureYouTubeIcon = (gcnew System::Windows::Forms::PictureBox());
			this->pictureGitHubIcon = (gcnew System::Windows::Forms::PictureBox());
			this->labelGitHubReadme = (gcnew System::Windows::Forms::LinkLabel());
			this->labelAboutAuthor = (gcnew System::Windows::Forms::LinkLabel());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f4FovTrackbar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f4FovNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureAboutIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureYouTubeIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureGitHubIcon))->BeginInit();
			this->SuspendLayout();
			// 
			// f4FovTrackbar
			// 
			this->f4FovTrackbar->Location = System::Drawing::Point(23, 127);
			this->f4FovTrackbar->Maximum = 50;
			this->f4FovTrackbar->Name = L"f4FovTrackbar";
			this->f4FovTrackbar->Size = System::Drawing::Size(385, 45);
			this->f4FovTrackbar->TabIndex = 0;
			// 
			// f4FovToggle
			// 
			this->f4FovToggle->AutoSize = true;
			this->f4FovToggle->Location = System::Drawing::Point(108, 73);
			this->f4FovToggle->Name = L"f4FovToggle";
			this->f4FovToggle->Size = System::Drawing::Size(65, 17);
			this->f4FovToggle->TabIndex = 1;
			this->f4FovToggle->Text = L"Enabled";
			this->f4FovToggle->UseVisualStyleBackColor = true;
			// 
			// f4FovNumericUpDown
			// 
			this->f4FovNumericUpDown->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->f4FovNumericUpDown->DecimalPlaces = 1;
			this->f4FovNumericUpDown->Location = System::Drawing::Point(256, 70);
			this->f4FovNumericUpDown->Name = L"f4FovNumericUpDown";
			this->f4FovNumericUpDown->Size = System::Drawing::Size(60, 20);
			this->f4FovNumericUpDown->TabIndex = 5;
			this->f4FovNumericUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->f4FovNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4500, 0, 0, 131072 });
			// 
			// f4FovTitle
			// 
			this->f4FovTitle->AutoSize = true;
			this->f4FovTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->f4FovTitle->Location = System::Drawing::Point(105, 22);
			this->f4FovTitle->Name = L"f4FovTitle";
			this->f4FovTitle->Size = System::Drawing::Size(211, 15);
			this->f4FovTitle->TabIndex = 7;
			this->f4FovTitle->Text = L"Free Map (F4) Camera FOV Value (�):";
			// 
			// label4
			// 
			this->label4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label4->Location = System::Drawing::Point(16, 201);
			this->label4->MaximumSize = System::Drawing::Size(0, 2);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(0, 2);
			this->label4->TabIndex = 9;
			// 
			// f4FovMinLabel
			// 
			this->f4FovMinLabel->AutoSize = true;
			this->f4FovMinLabel->Location = System::Drawing::Point(26, 159);
			//this->f4FovMinLabel->Location = this->f4FovTrackbar->Location.Subtract(System::Drawing::Point(26, 159),System::Drawing::Size(1,1));
			this->f4FovMinLabel->Name = L"f4FovMinLabel";
			this->f4FovMinLabel->Size = System::Drawing::Size(22, 13);
			this->f4FovMinLabel->TabIndex = 10;
			this->f4FovMinLabel->Text = L"1.0";
			// 
			// f4FovMaxLabel
			// 
			this->f4FovMaxLabel->AutoSize = true;
			this->f4FovMaxLabel->Location = System::Drawing::Point(379, 159);
			this->f4FovMaxLabel->Name = L"f4FovMaxLabel";
			this->f4FovMaxLabel->Size = System::Drawing::Size(34, 13);
			this->f4FovMaxLabel->TabIndex = 11;
			this->f4FovMaxLabel->Text = L"150.0";
			// 
			// f4FovRawLabel
			// 
			this->f4FovRawLabel->AutoSize = true;
			this->f4FovRawLabel->Location = System::Drawing::Point(218, 73);
			this->f4FovRawLabel->Name = L"f4FovRawLabel";
			this->f4FovRawLabel->Size = System::Drawing::Size(32, 13);
			this->f4FovRawLabel->TabIndex = 20;
			this->f4FovRawLabel->Text = L"Raw:";
			// 
			// labelAboutThanksTo
			// 
			this->labelAboutThanksTo->AutoSize = true;
			this->labelAboutThanksTo->LinkArea = System::Windows::Forms::LinkArea(11, 30);
			this->labelAboutThanksTo->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->labelAboutThanksTo->Location = System::Drawing::Point(172, 381);
			this->labelAboutThanksTo->Name = L"labelAboutThanksTo";
			this->labelAboutThanksTo->Size = System::Drawing::Size(218, 17);
			this->labelAboutThanksTo->TabIndex = 19;
			this->labelAboutThanksTo->TabStop = true;
			this->labelAboutThanksTo->Text = L"Thanks to: rev_eng_e, win32kbase / wolfie";
			this->labelAboutThanksTo->UseCompatibleTextRendering = true;
			this->labelAboutThanksTo->VisitedLinkColor = System::Drawing::Color::Blue;
			// 
			// labelAboutVersionGithub
			// 
			this->labelAboutVersionGithub->AutoSize = true;
			this->labelAboutVersionGithub->LinkArea = System::Windows::Forms::LinkArea(15, 6);
			this->labelAboutVersionGithub->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->labelAboutVersionGithub->Location = System::Drawing::Point(172, 334);
			this->labelAboutVersionGithub->Name = L"labelAboutVersionGithub";
			this->labelAboutVersionGithub->Size = System::Drawing::Size(109, 17);
			this->labelAboutVersionGithub->TabIndex = 12;
			this->labelAboutVersionGithub->TabStop = true;
			this->labelAboutVersionGithub->Text = L"v0.1.0 alpha � Github";
			this->labelAboutVersionGithub->UseCompatibleTextRendering = true;
			this->labelAboutVersionGithub->VisitedLinkColor = System::Drawing::Color::Blue;
			// 
			// labelAboutTitle
			// 
			this->labelAboutTitle->AutoSize = true;
			this->labelAboutTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelAboutTitle->Location = System::Drawing::Point(169, 303);
			this->labelAboutTitle->Name = L"labelAboutTitle";
			this->labelAboutTitle->Size = System::Drawing::Size(186, 20);
			this->labelAboutTitle->TabIndex = 13;
			this->labelAboutTitle->Text = L"OMSI Presentation Tools";
			// 
			// pictureAboutIcon
			// 
			this->pictureAboutIcon->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureAboutIcon.Image")));
			this->pictureAboutIcon->Location = System::Drawing::Point(37, 303);
			this->pictureAboutIcon->Name = L"pictureAboutIcon";
			this->pictureAboutIcon->Size = System::Drawing::Size(101, 90);
			this->pictureAboutIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureAboutIcon->TabIndex = 15;
			this->pictureAboutIcon->TabStop = false;
			// 
			// labelWarningGameClosed
			// 
			this->labelWarningGameClosed->AutoSize = true;
			this->labelWarningGameClosed->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->labelWarningGameClosed->Location = System::Drawing::Point(30, 239);
			this->labelWarningGameClosed->Name = L"labelWarningGameClosed";
			this->labelWarningGameClosed->Size = System::Drawing::Size(369, 15);
			this->labelWarningGameClosed->TabIndex = 21;
			this->labelWarningGameClosed->Text = L"Please keep other games closed while OMSI 2 && OPT are running!";
			// 
			// labelYouTube
			// 
			this->labelYouTube->AutoSize = true;
			this->labelYouTube->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelYouTube->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->labelYouTube->Location = System::Drawing::Point(56, 211);
			this->labelYouTube->Name = L"labelYouTube";
			this->labelYouTube->Size = System::Drawing::Size(204, 15);
			this->labelYouTube->TabIndex = 22;
			this->labelYouTube->TabStop = true;
			this->labelYouTube->Text = L"YouTube tutorial && suggested usage";
			this->labelYouTube->VisitedLinkColor = System::Drawing::Color::Blue;
			// 
			// pictureYouTubeIcon
			// 
			this->pictureYouTubeIcon->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureYouTubeIcon.Image")));
			this->pictureYouTubeIcon->Location = System::Drawing::Point(31, 208);
			this->pictureYouTubeIcon->Name = L"pictureYouTubeIcon";
			this->pictureYouTubeIcon->Size = System::Drawing::Size(24, 23);
			this->pictureYouTubeIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureYouTubeIcon->TabIndex = 23;
			this->pictureYouTubeIcon->TabStop = false;
			// 
			// pictureGitHubIcon
			// 
			this->pictureGitHubIcon->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureGitHubIcon.Image")));
			this->pictureGitHubIcon->Location = System::Drawing::Point(281, 210);
			this->pictureGitHubIcon->Name = L"pictureGitHubIcon";
			this->pictureGitHubIcon->Size = System::Drawing::Size(20, 18);
			this->pictureGitHubIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureGitHubIcon->TabIndex = 25;
			this->pictureGitHubIcon->TabStop = false;
			// 
			// labelGitHubReadme
			// 
			this->labelGitHubReadme->AutoSize = true;
			this->labelGitHubReadme->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelGitHubReadme->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->labelGitHubReadme->Location = System::Drawing::Point(302, 211);
			this->labelGitHubReadme->Name = L"labelGitHubReadme";
			this->labelGitHubReadme->Size = System::Drawing::Size(94, 15);
			this->labelGitHubReadme->TabIndex = 26;
			this->labelGitHubReadme->TabStop = true;
			this->labelGitHubReadme->Text = L"Github Readme";
			this->labelGitHubReadme->VisitedLinkColor = System::Drawing::Color::Blue;
			// 
			// labelAboutAuthor
			// 
			this->labelAboutAuthor->AutoSize = true;
			this->labelAboutAuthor->LinkArea = System::Windows::Forms::LinkArea(11, 5);
			this->labelAboutAuthor->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->labelAboutAuthor->Location = System::Drawing::Point(172, 358);
			this->labelAboutAuthor->Name = L"labelAboutAuthor";
			this->labelAboutAuthor->Size = System::Drawing::Size(86, 17);
			this->labelAboutAuthor->TabIndex = 17;
			this->labelAboutAuthor->TabStop = true;
			this->labelAboutAuthor->Text = L"Created by sjain";
			this->labelAboutAuthor->UseCompatibleTextRendering = true;
			this->labelAboutAuthor->VisitedLinkColor = System::Drawing::Color::Blue;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(431, 426);
			this->Controls->Add(this->labelGitHubReadme);
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
			this->Name = L"MyForm";
			this->Text = L"OMSI Presentation Tools";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f4FovTrackbar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f4FovNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureAboutIcon))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureYouTubeIcon))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureGitHubIcon))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
};
}
